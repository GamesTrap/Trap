#include "TRAPPCH.h"
#include "Input/Input.h"

#ifdef TRAP_PLATFORM_WINDOWS

#include "Application.h"
#include "Event/ControllerEvent.h"
#include "Utils/ControllerMappings.h"

std::array<uint32_t, 4> TRAP::Input::s_lastXInputUpdate{};
IDirectInput8W* TRAP::Input::API = nullptr;

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::Input::InitController()
{
	if (s_controllerAPI == ControllerAPI::DirectInput)
	{
		for (int32_t i = 0; Embed::ControllerMappings[i]; i++)
			UpdateControllerMappings(Embed::ControllerMappings[i]);

		if (FAILED(DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8W, reinterpret_cast<void**>(&API), nullptr)))
		{
			TP_ERROR("[Input][Controller][DirectInput] Failed to create interface!");
			return false;
		}

		if (API)
			if (FAILED(IDirectInput8_EnumDevices(API, DI8DEVCLASS_GAMECTRL, DeviceCallback, nullptr, DIEDFL_ALLDEVICES)))
				TP_ERROR("[Input][Controller][DirectInput] Failed to enumerate devices!");
	}

	UpdateControllerConnectionWindows();

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Input::ShutdownController()
{
	if (s_controllerAPI == ControllerAPI::XInput)
	{
		for (uint32_t i = 0; i <= static_cast<uint32_t>(Controller::Four); i++)
		{
			if (s_controllerStatuses[i].Connected)
			{
				ControllerDisconnectEvent event(static_cast<Controller>(i));
				s_eventCallback(event);
			}
		}
	}
	else if (s_controllerAPI == ControllerAPI::DirectInput)
	{
		for (uint32_t jID = 0; jID <= static_cast<uint32_t>(Controller::Four); jID++)
			if (s_controllerStatuses[jID].Connected)
				CloseController(static_cast<Controller>(jID));

		if (API)
			IDirectInput8_Release(API);
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Input::UpdateControllerConnectionWindows()
{
	for (uint32_t i = 0; i < s_controllerStatuses.size(); i++)
	{
		if (!s_controllerStatuses[i].Connected)
		{
			if (s_controllerAPI == ControllerAPI::XInput)
			{
				XINPUT_STATE state{};
				const uint32_t result = XInputGetState(static_cast<uint32_t>(static_cast<Controller>(i)), &state);
				if (result == ERROR_SUCCESS)
				{
					if (state.dwPacketNumber == s_lastXInputUpdate[static_cast<uint32_t>(static_cast<Controller>(i))]) //If true nothing changed
						return;
					s_lastXInputUpdate[static_cast<uint32_t>(static_cast<Controller>(i))] = state.dwPacketNumber;

					UpdateControllerBatteryAndConnectionTypeXInput(static_cast<Controller>(i));

					ControllerConnectEvent event(static_cast<Controller>(i));
					s_eventCallback(event);

					return;
				}
				if (result != ERROR_NOT_CONNECTED && result != ERROR_DEVICE_NOT_CONNECTED)
					TP_ERROR("[Input][Controller][XInput] ID: ", static_cast<uint32_t>(static_cast<Controller>(i)), " Error: ", result, "!");
			}
			else if (s_controllerAPI == ControllerAPI::DirectInput)
			{
				if (API)
					if (FAILED(IDirectInput8_EnumDevices(API, DI8DEVCLASS_GAMECTRL, DeviceCallback, nullptr, DIEDFL_ALLDEVICES)))
						TP_ERROR("[Input][Controller][DirectInput] Failed to enumerate DirectInput devices!");
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Input::DetectControllerConnection()
{
	for (uint32_t jID = 0; jID <= static_cast<uint32_t>(Controller::Four); jID++)
		if (s_controllerStatuses[jID].Connected)
			PollController(static_cast<Controller>(jID), 0);
}

//-------------------------------------------------------------------------------------------------------------------//

std::string TRAP::Input::GetControllerNameInternal(Controller controller)
{
	if (s_controllerAPI == ControllerAPI::XInput)
	{
		XINPUT_CAPABILITIES caps{};
		const uint32_t result = XInputGetCapabilities(static_cast<uint32_t>(controller), 0, &caps);
		if (result == ERROR_SUCCESS)
		{
			switch (caps.SubType)
			{
			case XINPUT_DEVSUBTYPE_WHEEL:
				return "XInput Wheel";

			case XINPUT_DEVSUBTYPE_ARCADE_STICK:
				return "XInput Arcade Stick";

			case XINPUT_DEVSUBTYPE_FLIGHT_STICK:
				return "XInput Flight Stick";

			case XINPUT_DEVSUBTYPE_DANCE_PAD:
				return "XInput Dance Pad";

			case XINPUT_DEVSUBTYPE_GUITAR:
				return "XInput Guitar";

			case XINPUT_DEVSUBTYPE_DRUM_KIT:
				return "XInput Drum Kit";

			case XINPUT_DEVSUBTYPE_GAMEPAD:
				return "XInput Gamepad";

			default:
				return "Unknown XInput Device";
			}
		}

		TP_ERROR("[Input][Controller][XInput] ID: ", static_cast<uint32_t>(controller), " Error: ", result, " while getting controller name!");
		return "Unknown XInput Device";
	}
	if (s_controllerAPI == ControllerAPI::DirectInput)
	{
		if (!PollController(controller, 0))
			return "";

		if (IsControllerGamepad(controller))
			return std::string(s_controllerInternal[static_cast<int32_t>(controller)].mapping->Name.data());

		return s_controllerInternal[static_cast<int32_t>(controller)].Name;
	}

	return {};
}

//-------------------------------------------------------------------------------------------------------------------//

std::vector<TRAP::Input::ControllerDPad> TRAP::Input::GetAllControllerDPadsInternal(Controller controller)
{
	if (s_controllerAPI == ControllerAPI::XInput)
		return { GetControllerDPadXInput(controller, 0) };
	if (s_controllerAPI == ControllerAPI::DirectInput)
	{
		if (!PollController(controller, 3))
			return {};

		return s_controllerInternal[static_cast<int32_t>(controller)].DPads;
	}

	return {};
}

//-------------------------------------------------------------------------------------------------------------------//

std::vector<float> TRAP::Input::GetAllControllerAxesInternal(Controller controller)
{
	if (s_controllerAPI == ControllerAPI::XInput)
	{
		XINPUT_STATE state{};
		const uint32_t result = XInputGetState(static_cast<uint32_t>(controller), &state);
		if (result == ERROR_SUCCESS)
		{
			std::vector<float> axes(6, 0.0f);
			axes[0] = (static_cast<float>(state.Gamepad.sThumbLX) + 0.5f) / 32767.5f;
			axes[1] = -(static_cast<float>(state.Gamepad.sThumbLY) + 0.5f) / 32767.5f;
			axes[2] = (static_cast<float>(state.Gamepad.sThumbRX) + 0.5f) / 32767.5f;
			axes[3] = -(static_cast<float>(state.Gamepad.sThumbRY) + 0.5f) / 32767.5f;
			axes[4] = static_cast<float>(state.Gamepad.bLeftTrigger) / 127.5f - 1.0f;
			axes[5] = static_cast<float>(state.Gamepad.bRightTrigger) / 127.5f - 1.0f;

			return axes;
		}

		TP_ERROR("[Input][Controller][XInput] ID: ", static_cast<uint32_t>(controller), " Error: ", result, " while getting axes states!");
		return std::vector<float>(6, 0.0f);
	}
	if (s_controllerAPI == ControllerAPI::DirectInput)
	{
		if (!PollController(controller, 1))
			return {};

		return s_controllerInternal[static_cast<int32_t>(controller)].Axes;
	}

	return {};
}

//-------------------------------------------------------------------------------------------------------------------//

std::vector<bool> TRAP::Input::GetAllControllerButtonsInternal(Controller controller)
{
	if (s_controllerAPI == ControllerAPI::XInput)
	{
		XINPUT_STATE state{};
		const uint32_t result = XInputGetState(static_cast<uint32_t>(controller), &state);
		if (result == ERROR_SUCCESS)
		{
			std::vector<bool> buttons(15, false);
			buttons[0] = (state.Gamepad.wButtons & ControllerButtonToXInput(ControllerButton::A)) != 0;
			buttons[1] = (state.Gamepad.wButtons & ControllerButtonToXInput(ControllerButton::B)) != 0;
			buttons[2] = (state.Gamepad.wButtons & ControllerButtonToXInput(ControllerButton::X)) != 0;
			buttons[3] = (state.Gamepad.wButtons & ControllerButtonToXInput(ControllerButton::Y)) != 0;
			buttons[4] = (state.Gamepad.wButtons & ControllerButtonToXInput(ControllerButton::Left_Bumper)) != 0;
			buttons[5] = (state.Gamepad.wButtons & ControllerButtonToXInput(ControllerButton::Right_Bumper)) != 0;
			buttons[6] = (state.Gamepad.wButtons & ControllerButtonToXInput(ControllerButton::Back)) != 0;
			buttons[7] = (state.Gamepad.wButtons & ControllerButtonToXInput(ControllerButton::Start)) != 0;
			buttons[8] = (state.Gamepad.wButtons & ControllerButtonToXInput(ControllerButton::Guide)) != 0;
			buttons[9] = (state.Gamepad.wButtons & ControllerButtonToXInput(ControllerButton::Left_Thumb)) != 0;
			buttons[10] = (state.Gamepad.wButtons & ControllerButtonToXInput(ControllerButton::Right_Thumb)) != 0;
			buttons[11] = (state.Gamepad.wButtons & ControllerButtonToXInput(ControllerButton::DPad_Up)) != 0;
			buttons[12] = (state.Gamepad.wButtons & ControllerButtonToXInput(ControllerButton::DPad_Right)) != 0;
			buttons[13] = (state.Gamepad.wButtons & ControllerButtonToXInput(ControllerButton::DPad_Down)) != 0;
			buttons[14] = (state.Gamepad.wButtons & ControllerButtonToXInput(ControllerButton::DPad_Left)) != 0;

			return buttons;
		}

		TP_ERROR("[Input][Controller][XInput] ID: ", static_cast<uint32_t>(controller), " Error: ", result, " while getting button states!");
		return std::vector<bool>(15, false);
	}
	if (s_controllerAPI == ControllerAPI::DirectInput)
	{
		if (!PollController(controller, 2))
			return {};

		return s_controllerInternal[static_cast<int32_t>(controller)].Buttons;
	}

	return {};
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Input::SetControllerVibrationInternal(Controller controller, const float leftMotor, const float rightMotor)
{
	if (s_controllerAPI == ControllerAPI::XInput)
	{
		const uint16_t left = static_cast<uint16_t>(static_cast<float>(65535)* leftMotor);
		const uint16_t right = static_cast<uint16_t>(static_cast<float>(65535)* rightMotor);
		XINPUT_VIBRATION vibration{ left, right };
		const uint32_t result = XInputSetState(static_cast<uint32_t>(controller), &vibration);
		if (result != ERROR_SUCCESS)
			TP_ERROR("[Input][Controller][XInput] ID: ", static_cast<uint32_t>(controller), " Error: ", result, " while setting vibration!");
	}
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::Input::PollController(Controller controller, const int32_t mode)
{
	if(s_controllerAPI == ControllerAPI::XInput)
	{
		XINPUT_STATE state{};
		const DWORD result = XInputGetState(static_cast<uint32_t>(controller), &state);
		if (result != ERROR_SUCCESS)
		{
			if (result == ERROR_DEVICE_NOT_CONNECTED && s_controllerStatuses[static_cast<uint32_t>(controller)].Connected)
			{			
				ControllerDisconnectEvent event(controller);
				s_eventCallback(event);
				return false;
			}
		}
	}	
	if(s_controllerAPI == ControllerAPI::DirectInput)
	{
		ControllerInternal* js = &s_controllerInternal[static_cast<uint32_t>(controller)];
		if (js->wsjs.Device)
		{
			int i = 0, ai = 0, bi = 0, pi = 0;
			HRESULT result{};
			DIJOYSTATE state{};

			IDirectInputDevice8_Poll(js->wsjs.Device);
			result = IDirectInputDevice8_GetDeviceState(js->wsjs.Device, sizeof(state), &state);

			if (result == DIERR_NOTACQUIRED || result == DIERR_INPUTLOST)
			{
				IDirectInputDevice8_Acquire(js->wsjs.Device);
				IDirectInputDevice8_Poll(js->wsjs.Device);
				result = IDirectInputDevice8_GetDeviceState(js->wsjs.Device, sizeof(state), &state);
			}

			if (FAILED(result))
			{
				CloseController(controller);
				return false;
			}

			if (mode == 0)
				return true;

			for (i = 0; i < js->wsjs.ObjectCount; i++)
			{
				void* data = reinterpret_cast<char*>(&state) + js->wsjs.Objects[i].Offset;

				switch (js->wsjs.Objects[i].Type)
				{
				case 0:
				case 1:
					{
						const float value = (*static_cast<LONG*>(data) + 0.5f) / 32767.5f;
						InternalInputControllerAxis(js, ai, value);
						ai++;
						break;
					}

				case 2:
					{
						const char value = (*static_cast<BYTE*>(data) & 0x80) != 0;
						InternalInputControllerButton(js, bi, value);
						bi++;
						break;
					}

				case 3:
					{
						const std::array<int, 9> states =
						{
							static_cast<int32_t>(ControllerDPad::Up),
							static_cast<int32_t>(ControllerDPad::Right_Up),
							static_cast<int32_t>(ControllerDPad::Right),
							static_cast<int32_t>(ControllerDPad::Right_Down),
							static_cast<int32_t>(ControllerDPad::Down),
							static_cast<int32_t>(ControllerDPad::Left_Down),
							static_cast<int32_t>(ControllerDPad::Left),
							static_cast<int32_t>(ControllerDPad::Left_Up),
							static_cast<int32_t>(ControllerDPad::Centered)
						};

						//Screams of horror are appropriate at this point
						int32_t state = LOWORD(*static_cast<DWORD*>(data)) / (45 * DI_DEGREES);
						if (state < 0 || state > 8)
							state = 8;

						InternalInputControllerDPad(js, pi, states[state]);
						pi++;
						break;
					}

				default:
					break;
				}
			}
		}

		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Input::UpdateControllerBatteryAndConnectionTypeXInput(Controller controller)
{
	XINPUT_BATTERY_INFORMATION battery{};
	const uint32_t result = XInputGetBatteryInformation(static_cast<uint32_t>(controller), BATTERY_DEVTYPE_GAMEPAD, &battery);
	if (result == ERROR_SUCCESS)
	{
		switch (battery.BatteryType)
		{
		case BATTERY_TYPE_WIRED:
			s_controllerStatuses[static_cast<uint32_t>(controller)].ConnectionType = ControllerConnectionType::Wired;
			break;

		case BATTERY_TYPE_ALKALINE:
		case BATTERY_TYPE_NIMH:
		case BATTERY_TYPE_UNKNOWN:
			s_controllerStatuses[static_cast<uint32_t>(controller)].ConnectionType = ControllerConnectionType::Wireless;
			break;

		default:
			TP_ERROR("[Input][Controller][XInput] ID: ", static_cast<uint32_t>(controller), " Error: ", result, " while checking battery information!");
			s_controllerStatuses[static_cast<uint32_t>(controller)].ConnectionType = ControllerConnectionType::Unknown;
			break;
		}

		if (s_controllerStatuses[static_cast<uint32_t>(controller)].ConnectionType == ControllerConnectionType::Wireless)
		{
			switch (battery.BatteryLevel)
			{
			case BATTERY_LEVEL_EMPTY:
				s_controllerStatuses[static_cast<uint32_t>(controller)].BatteryStatus = ControllerBattery::Empty;
				break;

			case BATTERY_LEVEL_LOW:
				s_controllerStatuses[static_cast<uint32_t>(controller)].BatteryStatus = ControllerBattery::Low;
				break;

			case BATTERY_LEVEL_MEDIUM:
				s_controllerStatuses[static_cast<uint32_t>(controller)].BatteryStatus = ControllerBattery::Medium;
				break;

			case BATTERY_LEVEL_FULL:
				s_controllerStatuses[static_cast<uint32_t>(controller)].BatteryStatus = ControllerBattery::Full;
				break;

			default:
				TP_ERROR("[Input][Controller][XInput] ID: ", static_cast<uint32_t>(controller), " Error: ", result, " while checking battery status!");
				s_controllerStatuses[static_cast<uint32_t>(controller)].BatteryStatus = ControllerBattery::Unknown;
				break;
			}
		}

		return;
	}
	TP_ERROR("[Input][Controller][XInput] ID: ", static_cast<uint32_t>(controller), " Error: ", result, "!");
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::Input::IsGamepadButtonPressedXInput(Controller controller, const ControllerButton button)
{
	const int32_t buttonXInput = ControllerButtonToXInput(button);
	if (buttonXInput == -1)
		return false;
	if (buttonXInput == 0)
	{
		TP_ERROR("[Input][Controller][XInput] Could not get button state!");
		TP_ERROR("[Input][Controller][XInput] Invalid Button!");
		return false;
	}

	XINPUT_STATE state{};
	const uint32_t result = XInputGetState(static_cast<uint32_t>(controller), &state);
	if (result == ERROR_SUCCESS)
		return (state.Gamepad.wButtons & buttonXInput) != 0;

	TP_ERROR("[Input][Controller][XInput] ID: ", static_cast<uint32_t>(controller), " Error: ", result, " while getting button status!");
	return false;
}

//-------------------------------------------------------------------------------------------------------------------//

float TRAP::Input::GetControllerAxisXInput(Controller controller, const ControllerAxis axis)
{
	XINPUT_STATE state{};
	const uint32_t result = XInputGetState(static_cast<uint32_t>(controller), &state);
	if (result == ERROR_SUCCESS)
	{
		switch (axis)
		{
		case ControllerAxis::Left_X:
			return (static_cast<float>(state.Gamepad.sThumbLX) + 0.5f) / 32767.5f;

		case ControllerAxis::Left_Y:
			return -(static_cast<float>(state.Gamepad.sThumbLY) + 0.5f) / 32767.5f;

		case ControllerAxis::Right_X:
			return (static_cast<float>(state.Gamepad.sThumbRX) + 0.5f) / 32767.5f;

		case ControllerAxis::Right_Y:
			return -(static_cast<float>(state.Gamepad.sThumbRY) + 0.5f) / 32767.5f;

		case ControllerAxis::Left_Trigger:
			return static_cast<float>(state.Gamepad.bLeftTrigger) / 127.5f - 1.0f;

		case ControllerAxis::Right_Trigger:
			return static_cast<float>(state.Gamepad.bRightTrigger) / 127.5f - 1.0f;

		default:
			TP_ERROR("[Input][Controller][XInput] Could not get axis state!");
			return 0.0f;
		}
	}

	TP_ERROR("[Input][Controller][XInput] ID: ", static_cast<uint32_t>(controller), " Error: ", result, " while getting axis state!");
	return 0.0f;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Input::ControllerDPad TRAP::Input::GetControllerDPadXInput(const Controller controller, const uint32_t dpad)
{
	if (dpad == 0)
	{
		std::vector<bool> buttons = GetAllControllerButtonsInternal(controller);
		const bool up = buttons[11];
		const bool right = buttons[12];
		const bool down = buttons[13];
		const bool left = buttons[14];

		if (right && up)
			return ControllerDPad::Right_Up;
		if (right && down)
			return ControllerDPad::Right_Down;
		if (left && up)
			return ControllerDPad::Left_Up;
		if (left && down)
			return ControllerDPad::Left_Down;
		if (up)
			return ControllerDPad::Up;
		if (right)
			return ControllerDPad::Right;
		if (down)
			return ControllerDPad::Down;
		if (left)
			return ControllerDPad::Left;
	}

	return ControllerDPad::Centered;
}

//-------------------------------------------------------------------------------------------------------------------//

int32_t TRAP::Input::ControllerButtonToXInput(const ControllerButton button)
{
	switch (button)
	{
	case ControllerButton::A:
		//case ControllerButton::Cross:
		return 0x1000;

	case ControllerButton::B:
		//case ControllerButton::Circle:
		return 0x2000;

	case ControllerButton::X:
		//case ControllerButton::Square:
		return 0x4000;

	case ControllerButton::Y:
		//case ControllerButton::Triangle:
		return 0x8000;

	case ControllerButton::Left_Bumper:
		return 0x0100;

	case ControllerButton::Right_Bumper:
		return 0x0200;

	case ControllerButton::Back:
		return 0x0020;

	case ControllerButton::Start:
		return 0x0010;

	case ControllerButton::Guide:
		return -1;

	case ControllerButton::Left_Thumb:
		return 0x0040;

	case ControllerButton::Right_Thumb:
		return 0x080;

	case ControllerButton::DPad_Up:
		return 0x0001;

	case ControllerButton::DPad_Right:
		return 0x0008;

	case ControllerButton::DPad_Down:
		return 0x0002;

	case ControllerButton::DPad_Left:
		return 0x0004;

	default:
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Input::CloseController(Controller controller)
{
	if (s_controllerInternal[static_cast<uint32_t>(controller)].wsjs.Device)
	{
		IDirectInputDevice8_Unacquire(s_controllerInternal[static_cast<uint32_t>(controller)].wsjs.Device);
		IDirectInputDevice8_Release(s_controllerInternal[static_cast<uint32_t>(controller)].wsjs.Device);
	}

	ControllerDisconnectEvent event(controller);
	s_eventCallback(event);
}

//-------------------------------------------------------------------------------------------------------------------//

//DirectInput device object enumeration callback
BOOL CALLBACK TRAP::Input::DeviceObjectCallback(const DIDEVICEOBJECTINSTANCEW* doi, void* user)
{
	ObjectEnum* data = static_cast<ObjectEnum*>(user);
	Object* object = &data->Objects[data->ObjectCount];

	if (DIDFT_GETTYPE(doi->dwType) & DIDFT_AXIS)
	{
		DIPROPRANGE dipr;

		if (std::memcmp(&doi->guidType, &GUID_Slider, sizeof(GUID)) == 0)
			object->Offset = DIJOFS_SLIDER(data->SliderCount);
		else if (std::memcmp(&doi->guidType, &GUID_XAxis, sizeof(GUID)) == 0)
			object->Offset = DIJOFS_X;
		else if (std::memcmp(&doi->guidType, &GUID_YAxis, sizeof(GUID)) == 0)
			object->Offset = DIJOFS_Y;
		else if (std::memcmp(&doi->guidType, &GUID_ZAxis, sizeof(GUID)) == 0)
			object->Offset = DIJOFS_Z;
		else if (std::memcmp(&doi->guidType, &GUID_RxAxis, sizeof(GUID)) == 0)
			object->Offset = DIJOFS_RX;
		else if (std::memcmp(&doi->guidType, &GUID_RyAxis, sizeof(GUID)) == 0)
			object->Offset = DIJOFS_RY;
		else if (std::memcmp(&doi->guidType, &GUID_RzAxis, sizeof(GUID)) == 0)
			object->Offset = DIJOFS_RZ;
		else
			return DIENUM_CONTINUE;

		dipr.diph.dwSize = sizeof(dipr);
		dipr.diph.dwHeaderSize = sizeof(dipr.diph);
		dipr.diph.dwObj = doi->dwType;
		dipr.diph.dwHow = DIPH_BYID;
		dipr.lMin = -32768;
		dipr.lMax = 32767;

		if (FAILED(IDirectInputDevice8_SetProperty(data->Device, DIPROP_RANGE, &dipr.diph)))
			return DIENUM_CONTINUE;

		if (std::memcmp(&doi->guidType, &GUID_Slider, sizeof(GUID)) == 0)
		{
			object->Type = 1;
			data->SliderCount++;
		}
		else
		{
			object->Type = 0;
			data->AxisCount++;
		}
	}
	else if (DIDFT_GETTYPE(doi->dwType) & DIDFT_BUTTON)
	{
		object->Offset = DIJOFS_BUTTON(data->ButtonCount);
		object->Type = 2;
		data->ButtonCount++;
	}
	else if (DIDFT_GETTYPE(doi->dwType) & DIDFT_POV)
	{
		object->Offset = DIJOFS_POV(data->PoVCount);
		object->Type = 3;
		data->PoVCount++;
	}

	data->ObjectCount++;
	return DIENUM_CONTINUE;
}

//-------------------------------------------------------------------------------------------------------------------//

//Checks whether the specified device supports XInput
bool TRAP::Input::SupportsXInput(const GUID* guid)
{
	uint32_t count = 0;
	std::vector<RAWINPUTDEVICELIST> ridl{};
	bool result = false;

	if (GetRawInputDeviceList(nullptr, &count, sizeof(RAWINPUTDEVICELIST)) != 0)
		return false;

	ridl.resize(count);

	if (GetRawInputDeviceList(ridl.data(), &count, sizeof(RAWINPUTDEVICELIST)) == static_cast<uint32_t>(-1))
		return false;

	for (uint32_t i = 0; i < count; i++)
	{
		RID_DEVICE_INFO rdi;
		std::array<char, 256> name{};
		uint32_t size;

		if (ridl[i].dwType != RIM_TYPEHID)
			continue;

		rdi.cbSize = sizeof(rdi);
		size = sizeof(rdi);

		if (static_cast<int32_t>(GetRawInputDeviceInfoA(ridl[i].hDevice,
			RIDI_DEVICEINFO, &rdi, &size)) == -1)
			continue;

		if (MAKELONG(rdi.hid.dwVendorId, rdi.hid.dwProductId) != static_cast<int64_t>(guid->Data1))
			continue;

		size = static_cast<uint32_t>(name.size());

		if (static_cast<int32_t>(GetRawInputDeviceInfoA(ridl[i].hDevice,
			RIDI_DEVICENAME,
			name.data(),
			&size)) == -1)
			break;

		name[name.size() - 1] = '\0';
		if (strstr(name.data(), "IG_"))
		{
			result = true;
			break;
		}
	}

	return result;
}

//-------------------------------------------------------------------------------------------------------------------//

//Lexically compare device objects
int TRAP::Input::CompareControllerObjects(const void* first, const void* second)
{
	const Object* fo = static_cast<const Object*>(first);
	const Object* so = static_cast<const Object*>(second);

	if (fo->Type != so->Type)
		return fo->Type - so->Type;

	return fo->Offset - so->Offset;
}

//-------------------------------------------------------------------------------------------------------------------//

//DirectInput device enumeration callback
BOOL CALLBACK TRAP::Input::DeviceCallback(const DIDEVICEINSTANCE* deviceInstance, void* user)
{
	DIDEVCAPS dc{};
	DIPROPDWORD dipd{};
	IDirectInputDevice8* device = nullptr;
	ControllerInternal* controller;
	ObjectEnum data{};
	std::array<char, 33> guid{};
	std::array<char, 256> Name{};

	for (uint32_t jID = 0; jID <= static_cast<uint32_t>(Controller::Four); jID++)
	{
		controller = &s_controllerInternal[jID];
		if (s_controllerStatuses[jID].Connected)
		{
			if (std::memcmp(&controller->wsjs.guid, &deviceInstance->guidInstance, sizeof(GUID)) == 0)
				return DIENUM_CONTINUE;
		}
	}

	if (SupportsXInput(&deviceInstance->guidProduct))
		return DIENUM_CONTINUE;

	if (FAILED(IDirectInput8_CreateDevice(API, deviceInstance->guidInstance, &device, nullptr)))
	{
		TP_ERROR("[Input][Controller][DirectInput] Failed to create device!");
		return DIENUM_CONTINUE;
	}

	if (FAILED(IDirectInputDevice8_SetDataFormat(device, &c_dfDIJoystick)))
	{
		TP_ERROR("[Input][Controller][DirectInput] Failed to set device data format!");
		IDirectInputDevice8_Release(device);
		return DIENUM_CONTINUE;
	}

	dc.dwSize = sizeof(dc);

	if (FAILED(IDirectInputDevice8_GetCapabilities(device, &dc)))
	{
		TP_ERROR("[Input][Controller][DirectInput] Failed to query device capabilities!");
		IDirectInputDevice8_Release(device);
		return DIENUM_CONTINUE;
	}

	dipd.diph.dwSize = sizeof(dipd);
	dipd.diph.dwHeaderSize = sizeof(dipd.diph);
	dipd.diph.dwHow = DIPH_DEVICE;
	dipd.dwData = DIPROPAXISMODE_ABS;

	if (FAILED(IDirectInputDevice8_SetProperty(device, DIPROP_AXISMODE, &dipd.diph)))
	{
		TP_ERROR("[Input][Controller][DirectInput] Failed to set device axis mode!");
		IDirectInputDevice8_Release(device);
		return DIENUM_CONTINUE;
	}

	data.Device = device;
	data.Objects.resize(dc.dwAxes + dc.dwButtons + dc.dwPOVs);

	if (FAILED(IDirectInputDevice8_EnumObjects(device, DeviceObjectCallback, &data, DIDFT_AXIS | DIDFT_BUTTON | DIDFT_POV)))
	{
		TP_ERROR("[Input][Controller][DirectInput] Failed to enumerate device objects!");
		IDirectInputDevice8_Release(device);
		return DIENUM_CONTINUE;
	}

	std::qsort(data.Objects.data(), data.ObjectCount, sizeof(Object), CompareControllerObjects);

	if (!WideCharToMultiByte(CP_UTF8, 0, deviceInstance->tszInstanceName, -1, Name.data(), static_cast<int32_t>(Name.size()), nullptr, nullptr))
	{
		TP_ERROR("[Input][Controller][DirectInput] Failed to convert Controller name to UTF-8");
		IDirectInputDevice8_Release(device);
		return DIENUM_STOP;
	}

	//Generate a Controller GUID that matches the SDL 2.0.5+ one
	if (std::memcmp(&deviceInstance->guidProduct.Data4[2], "PIDVID", 6) == 0)
	{
		sprintf_s(guid.data(), guid.size(), "03000000%02x%02x0000%02x%02x000000000000",
			static_cast<uint8_t>(deviceInstance->guidProduct.Data1),
			static_cast<uint8_t>(deviceInstance->guidProduct.Data1 >> 8),
			static_cast<uint8_t>(deviceInstance->guidProduct.Data1 >> 16),
			static_cast<uint8_t>(deviceInstance->guidProduct.Data1 >> 24)
		);
	}
	else
	{
		sprintf_s(guid.data(), guid.size(), "05000000%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x00",
			Name[0], Name[1], Name[2], Name[3],
			Name[4], Name[5], Name[6], Name[7],
			Name[8], Name[9], Name[10]
		);
	}

	controller = AddInternalController(Name.data(), guid.data(), data.AxisCount + data.SliderCount, data.ButtonCount, data.PoVCount);

	if (!controller)
	{
		IDirectInputDevice8_Release(device);
		return DIENUM_STOP;
	}

	controller->wsjs.Device = device;
	controller->wsjs.guid = deviceInstance->guidInstance;
	controller->wsjs.Objects = data.Objects;
	controller->wsjs.ObjectCount = data.ObjectCount;

	uint32_t jID = 0;
	for (jID = 0; jID <= static_cast<uint32_t>(Controller::Four); jID++)
		if (!s_controllerStatuses[jID].Connected)
			break;

	ControllerConnectEvent event(static_cast<Controller>(jID));
	s_eventCallback(event);

	return DIENUM_CONTINUE;
}

#endif