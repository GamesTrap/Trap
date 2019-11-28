#include "TRAPPCH.h"
#include "Input/Input.h"

#ifdef TRAP_PLATFORM_LINUX

#include "Event/ControllerEvent.h"
#include "Utils/ControllerMappings.h"

TRAP::Input::ControllerLinuxLibrary TRAP::Input::s_linuxController{};

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::Input::InitController()
{
	for (int32_t i = 0; TRAP::Embed::ControllerMappings[i]; i++)
		UpdateControllerMappings(TRAP::Embed::ControllerMappings[i]);

	const char* dirName = "/dev/input";

	s_linuxController.INotify = inotify_init1(IN_NONBLOCK | IN_CLOEXEC);
	if(s_linuxController.INotify > 0)
	{
		//HACK: Register for IN_ATTRIB to get notified when udev is done
		//This works well in practice but the true way is libudev
		s_linuxController.Watch = inotify_add_watch(s_linuxController.INotify, dirName, IN_CREATE | IN_ATTRIB | IN_DELETE);
	}

	//Continue without device connection notifications if inotify fails
	if(regcomp(&s_linuxController.Regex, "^event[0-9]\\+$", 0) != 0)
	{
		TP_ERROR("[Input][Controller][Linux] Could not compile regex!");
		return false;
	}

	int32_t count = 0;

	DIR* dir = opendir(dirName);
	if(dir)
	{
		struct dirent* entry;

		while((entry = readdir(dir)))
		{
			regmatch_t match;

			if (regexec(&s_linuxController.Regex, entry->d_name, 1, &match, 0) != 0)
				continue;

			std::array<char, PATH_MAX> path;
			snprintf(path.data(), path.size(), "%s/%s", dirName, entry->d_name);

			if (OpenControllerDeviceLinux(path.data()))
				count++;
		}

		closedir(dir);
	}

	//Continue with no controllers if enumeration fails
	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Input::ShutdownController()
{
	for(int32_t jID = 0; jID <= static_cast<int32_t>(Controller::Four); jID++)
	{
		if(s_controllerInternal[jID].linjs.CurrentVibration != -1)
			SetControllerVibration(static_cast<Controller>(jID), 0.0f, 0.0f);
		if (s_controllerStatuses[jID].Connected)
			CloseController(static_cast<Controller>(jID));
	}
	
	s_controllerStatuses = {};

	regfree(&s_linuxController.Regex);

	if(s_linuxController.INotify > 0)
	{
		if (s_linuxController.Watch > 0)
			inotify_rm_watch(s_linuxController.INotify, s_linuxController.Watch);

		close(s_linuxController.INotify);
	}
}

//-------------------------------------------------------------------------------------------------------------------//

std::string TRAP::Input::GetControllerNameInternal(Controller controller)
{
	if (!PollController(controller, 0))
		return "";

	if (s_controllerInternal[static_cast<int32_t>(controller)].mapping)
		return std::string(s_controllerInternal[static_cast<int32_t>(controller)].mapping->Name.data());
	
	return s_controllerInternal[static_cast<int32_t>(controller)].Name;
}

//-------------------------------------------------------------------------------------------------------------------//

std::vector<float> TRAP::Input::GetAllControllerAxesInternal(Controller controller)
{
	if (!PollController(controller, 0))
		return {};

	return s_controllerInternal[static_cast<int32_t>(controller)].Axes;
}

//-------------------------------------------------------------------------------------------------------------------//

std::vector<bool> TRAP::Input::GetAllControllerButtonsInternal(Controller controller)
{
	if (!PollController(controller, 0))
		return {};

	return s_controllerInternal[static_cast<int32_t>(controller)].Buttons;
}

//-------------------------------------------------------------------------------------------------------------------//

std::vector<TRAP::Input::ControllerDPad> TRAP::Input::GetAllControllerDPadsInternal(Controller controller)
{
	if (!PollController(controller, 0))
		return {};

	return s_controllerInternal[static_cast<int32_t>(controller)].DPads;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Input::SetControllerVibrationInternal(Controller controller, float leftMotor, float rightMotor)
{
	if(!PollController(controller, 0))
		return;
		
	ControllerInternal* js = &s_controllerInternal[static_cast<uint32_t>(controller)];
	if(js->linjs.VibrationSupported)
	{
		struct input_event play;
		//Delete any existing effect
		if(js->linjs.CurrentVibration != -1)
		{
			//Stop the effect
			play.type = EV_FF;
			play.code = js->linjs.CurrentVibration;
			play.value = 0;
		
			write(js->linjs.FD, (const void*)&play, sizeof(play));
		
			//Delete the effect
			ioctl(js->linjs.FD, EVIOCRMFF, js->linjs.CurrentVibration);
		}
	
		//If VibrationSupported is true, start the new effect
		if(leftMotor != 0.0f || rightMotor != 0.0f)
		{
			struct ff_effect ff;
		
			//Define an effect for this vibration setting
			ff.type = FF_RUMBLE;
			ff.id = -1;
			ff.u.rumble.strong_magnitude = static_cast<uint16_t>(leftMotor * 65535);
			ff.u.rumble.weak_magnitude = static_cast<uint16_t>(rightMotor * 65535);
			ff.replay.length = 65535;
			ff.replay.delay = 0;
		
			//Upload the effect
			if(ioctl(js->linjs.FD, EVIOCSFF, &ff) != -1)
				js->linjs.CurrentVibration = ff.id;
			
			//Play the effect
			play.type = EV_FF;
			play.code = js->linjs.CurrentVibration;
			play.value = 1;
		
			write(js->linjs.FD, (const void*)&play, sizeof(play));
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------//

//Attempt to open the specified controller device
bool TRAP::Input::OpenControllerDeviceLinux(const char* path)
{
	for(int32_t jID = 0; jID <= static_cast<int32_t>(Controller::Four); jID++)
	{
		if (!s_controllerStatuses[jID].Connected)
			continue;
		if (std::strcmp(s_controllerInternal[jID].linjs.Path.data(), path) == 0)
			return false;
	}

	ControllerLinux linjs = {};
	linjs.FD = open(path, O_RDWR | O_NONBLOCK); //O_RDWR is needed for vibrations
	if(linjs.FD != -1)
		linjs.VibrationSupported = true;
		
	if(errno == EACCES)
		linjs.FD = open(path, O_RDONLY | O_NONBLOCK);
	
	if (linjs.FD == -1)
		return false;

	std::array<char, (EV_CNT + 7) / 8> EVBits{};
	std::array<char, (KEY_CNT + 7) / 8> keyBits{};
	std::array<char, (ABS_CNT + 7) / 8> ABSBits{};
	struct input_id ID;

	if (ioctl(linjs.FD, EVIOCGBIT(0, EVBits.size()), EVBits.data()) < 0 ||
		ioctl(linjs.FD, EVIOCGBIT(EV_KEY, keyBits.size()), keyBits.data()) < 0 ||
		ioctl(linjs.FD, EVIOCGBIT(EV_ABS, ABSBits.size()), ABSBits.data()) < 0 ||
		ioctl(linjs.FD, EVIOCGID, &ID) < 0)
	{
		TP_ERROR("[Input][Controller][Linux] Could not query input device: ", strerror(errno), "!");
		close(linjs.FD);
		return false;
	}

	//Ensure this device supports the events expected of a controller
	if(!(EVBits[EV_KEY / 8] & (1 << (EV_KEY % 8))) || !(EVBits[EV_ABS / 8] & (1 << (EV_ABS % 8))))
	{
		close(linjs.FD);
		return false;
	}

	std::array<char, 256> name{};
	if (ioctl(linjs.FD, EVIOCGNAME(name.size()), name.data()) < 0)
		std::strncpy(name.data(), "Unknown", name.size());

	std::array<char, 33> guid{};
	//Generate a controller GUID that matches the SDL 2.0.5+ one
	if(ID.vendor && ID.product && ID.version)
	{
		sprintf(guid.data(), "%02x%02x0000%02x%02x0000%02x%02x0000%02x%02x0000",
			ID.bustype & 0xFF, ID.bustype >> 8,
			ID.vendor & 0xFF, ID.vendor >> 8,
			ID.product & 0xFF, ID.product >> 8,
			ID.version & 0xFF, ID.version >> 8);
	}
	else
	{
		sprintf(guid.data(), "%02x%02x0000%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x00",
			ID.bustype & 0xFF, ID.bustype >> 8,
			name[0], name[1], name[2], name[3],
			name[4], name[5], name[6], name[7],
			name[8], name[9], name[10]);
	}

	int axisCount = 0, buttonCount = 0, dpadCount = 0;
	for(int32_t code = BTN_MISC; code < KEY_CNT; code++)
	{
		if(!(keyBits[code / 8] & (1 << (code % 8))))
			continue;

		linjs.KeyMap[code - BTN_MISC] = buttonCount;
		buttonCount++;
	}

	for(int32_t code = 0; code < ABS_CNT; code++)
	{
		linjs.ABSMap[code] = -1;
		if(!(ABSBits[code / 8] & (1 << (code % 8))))
			continue;

		if(code >= ABS_HAT0X && code <= ABS_HAT3Y)
		{
			linjs.ABSMap[code] = dpadCount;
			dpadCount++;
			//Skip the Y axis
			code++;
		}
		else
		{
			if (ioctl(linjs.FD, EVIOCGABS(code), &linjs.ABSInfo[code]) < 0)
				continue;

			linjs.ABSMap[code] = axisCount;
			axisCount++;
		}
	}

	ControllerInternal* js = AddInternalController(name.data(), guid.data(), axisCount, buttonCount, dpadCount);
	if(!js)
	{
		close(linjs.FD);
		return false;
	}

	std::strncpy(linjs.Path.data(), path, linjs.Path.size() - 1);
	std::memcpy(&js->linjs, &linjs, sizeof(linjs));

	PollABSStateLinux(js);

	int32_t jID;
	for (jID = 0; jID <= static_cast<int32_t>(Controller::Four); jID++)
		if (!s_controllerStatuses[jID].Connected)
			break;
	
	ControllerConnectEvent event(static_cast<Controller>(jID));
	s_eventCallback(event);
	
	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

//Frees all resources associated with the specified controller
void TRAP::Input::CloseController(Controller controller)
{
	ControllerInternal* con = &s_controllerInternal[static_cast<int32_t>(controller)];
	
	close(con->linjs.FD);
	*con = {};

	ControllerDisconnectEvent event(static_cast<Controller>(controller));
	s_eventCallback(event);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Input::DetectControllerConnection()
{
	if (s_linuxController.INotify <= 0)
		return;

	ssize_t offset = 0;
	std::array<char, 16384> buffer{};
	const ssize_t size = read(s_linuxController.INotify, buffer.data(), buffer.size());

	while(size > offset)
	{
		regmatch_t match;
		const struct inotify_event* e = (struct inotify_event*)(&buffer[offset]);

		offset += sizeof(struct inotify_event) + e->len;

		if (regexec(&s_linuxController.Regex, e->name, 1, &match, 0) != 0)
			continue;

		std::array<char, PATH_MAX> path{};
		snprintf(path.data(), path.size(), "/dev/input/%s", e->name);

		if (e->mask & (IN_CREATE | IN_ATTRIB))
			OpenControllerDeviceLinux(path.data());
		else if(e->mask & IN_DELETE)
		{
			for(int32_t jID = 0; jID <= static_cast<int32_t>(Controller::Four); jID++)
			{
				if(std::strcmp(s_controllerInternal[jID].linjs.Path.data(), path.data()) == 0)
				{
					CloseController(static_cast<Controller>(jID));
					break;
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::Input::PollController(Controller controller, int32_t mode)
{
	if(s_controllerStatuses[static_cast<int32_t>(controller)].Connected)
	{
		ControllerInternal* js = &s_controllerInternal[static_cast<int32_t>(controller)];
	
		//Read all queued events (non-blocking)
		for(;;)
		{
			struct input_event e;

			errno = 0;
			if(read(js->linjs.FD, &e, sizeof(e)) < 0)
			{
				//Reset the controller slot if the device was disconnected
				if (errno == ENODEV)
					CloseController(controller);

				break;
			}

			if(e.type == EV_SYN)
			{
				if (e.code == SYN_DROPPED)
					s_linuxController.Dropped = true;
				else if(e.code == SYN_REPORT)
				{
					s_linuxController.Dropped = false;
					PollABSStateLinux(js);
				}
			}

			if (s_linuxController.Dropped)
				continue;

			if (e.type == EV_KEY)
				HandleKeyEventLinux(js, e.code, e.value);
			else if (e.type == EV_ABS)
				HandleABSEventLinux(js, e.code, e.value);
		}
	}

	return s_controllerStatuses[static_cast<int32_t>(controller)].Connected;
}

//-------------------------------------------------------------------------------------------------------------------//

//Poll state of absolute axes
void TRAP::Input::PollABSStateLinux(ControllerInternal* js)
{
	for (int32_t code = 0; code < ABS_CNT; code++)
	{
		if (js->linjs.ABSMap[code] < 0)
			continue;

		struct input_absinfo* info = &js->linjs.ABSInfo[code];

		if (ioctl(js->linjs.FD, EVIOCGABS(code), info) < 0)
			continue;

		HandleABSEventLinux(js, code, info->value);
	}
}

//-------------------------------------------------------------------------------------------------------------------//

//Apply an EV_ABS event to the specified controller
void TRAP::Input::HandleABSEventLinux(ControllerInternal* js, int32_t code, int32_t value)
{
	const int32_t index = js->linjs.ABSMap[code];

	if (code >= ABS_HAT0X && code <= ABS_HAT3Y)
	{
		static const std::array<std::array<char, 3>, 3> stateMap =
		{
			{
				{
					static_cast<char>(ControllerDPad::Centered),
					static_cast<char>(ControllerDPad::Up),
					static_cast<char>(ControllerDPad::Down)
				},
				{
					static_cast<char>(ControllerDPad::Left),
					static_cast<char>(ControllerDPad::Left_Up),
					static_cast<char>(ControllerDPad::Left_Down)
				},
				{
					static_cast<char>(ControllerDPad::Right),
					static_cast<char>(ControllerDPad::Right_Up),
					static_cast<char>(ControllerDPad::Right_Down)
				}
			}
		};

		const int32_t dpad = (code - ABS_HAT0X) / 2;
		const int32_t axis = (code - ABS_HAT0X) % 2;
		int32_t* state = js->linjs.DPads[dpad].data();

		//NOTE: Looking at several input drivers, it seems all DPad events use
		//-1 for left / up, 0 for centered and 1 for right / down
		if (value == 0)
			state[axis] = 0;
		else if (value < 0)
			state[axis] = 1;
		else if (value > 0)
			state[axis] = 2;

		InternalInputControllerDPad(js, index, stateMap[state[0]][state[1]]);
	}
	else
	{
		const struct input_absinfo* info = &js->linjs.ABSInfo[code];
		float normalized = value;

		const int range = info->maximum - info->minimum;
		if (range)
		{
			//Normalize to 0.0f -> 1.0f
			normalized = (normalized - info->minimum) / range;
			//Normalize to -1.0f -> 1.0f
			normalized = normalized * 2.0f - 1.0f;
		}

		InternalInputControllerAxis(js, index, normalized);
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Input::HandleKeyEventLinux(ControllerInternal* js, int32_t code, int32_t value)
{
	if(code - BTN_MISC >= 0)
		InternalInputControllerButton(js, js->linjs.KeyMap[code - BTN_MISC], value ? true : false);
}

#endif