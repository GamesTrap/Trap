#ifndef _TRAP_INPUT_H_
#define _TRAP_INPUT_H_

#include "Utils/Singleton.h"
#include "Maths/Math.h"
#include "Event/Event.h"

namespace TRAP
{
	class ControllerDisconnectEvent;
	class ControllerConnectEvent;

	class Input final : public Singleton
	{
	public:
		enum class Key
		{
			Space          = 32,
			Apostrophe     = 39,
			Comma          = 44,
			Minus          = 45,
			Period         = 46,
			Slash          = 47,
			Zero           = 48,
			One            = 49,
			Two            = 50,
			Three          = 51,
			Four           = 52,
			Five           = 53,
			Six            = 54,
			Seven          = 55,
			Eight          = 56,
			Nine           = 57,
			Semicolon      = 59,
			Equal          = 61,
			A              = 65,
			B              = 66,
			C              = 67,
			D              = 68,
			E              = 69,
			F              = 70,
			G              = 71,
			H              = 72,
			I              = 73,
			J              = 74,
			K              = 75,
			L              = 76,
			M              = 77,
			N              = 78,
			O              = 79,
			P              = 80,
			Q              = 81,
			R              = 82,
			S              = 83,
			T              = 84,
			U              = 85,
			V              = 86,
			W              = 87,
			X              = 88,
			Y              = 89,
			Z              = 90,
			Left_Bracket   = 91,
			Backslash      = 92,
			Right_Bracket  = 93,
			Grave_Accent   = 96,
			World_1        = 161,
			World_2        = 162,

			/* Function keys */
			Escape         = 256,
			Enter          = 257,
			Tab            = 258,
			Backspace      = 259,
			Insert         = 260,
			Delete         = 261,
			Right          = 262,
			Left           = 263,
			Down           = 264,
			Up             = 265,
			Page_Up        = 266,
			Page_Down      = 267,
			Home           = 268,
			End            = 269,
			Caps_Lock      = 280,
			Scroll_Lock    = 281,
			NUM_Lock       = 282,
			Print_Screen   = 283,
			Pause          = 284,
			F1             = 290,
			F2             = 291,
			F3             = 292,
			F4             = 293,
			F5             = 294,
			F6             = 295,
			F7             = 296,
			F8             = 297,
			F9             = 298,
			F10            = 299,
			F11            = 300,
			F12            = 301,
			F13            = 302,
			F14            = 303,
			F15            = 304,
			F16            = 305,
			F17            = 306,
			F18            = 307,
			F19            = 308,
			F20            = 309,
			F21            = 310,
			F22            = 311,
			F23            = 312,
			F24            = 313,
			F25            = 314,
			KP_0           = 320,
			KP_1           = 321,
			KP_2           = 322,
			KP_3           = 323,
			KP_4           = 324,
			KP_5           = 325,
			KP_6           = 326,
			KP_7           = 327,
			KP_8           = 328,
			KP_9           = 329,
			KP_Decimal     = 330,
			KP_Divide      = 331,
			KP_Multiply    = 332,
			KP_Subtract    = 333,
			KP_Add         = 334,
			KP_Enter       = 335,
			KP_Equal       = 336,
			Left_Shift     = 340,
			Left_Control   = 341,
			Left_ALT       = 342,
			Left_Super     = 343,
			Right_Shift    = 344,
			Right_Control  = 345,
			Right_ALT      = 346,
			Right_Super    = 347,
			Menu           = 348
		};
		
		enum class MouseButton
		{
			One    = 0,
			Two    = 1,
			Three  = 2,
			Four   = 3,
			Five   = 4,
			Six    = 5,
			Seven  = 6,
			Eight  = 7,
			Left   = One,
			Right  = Two,
			Middle = Three
		};

		//This is Microsoft's fault btw :C
		//XInput only supports 4 controllers at a time
		enum class Controller
		{
			One   = 0,
			Two   = 1,
			Three = 2,
			Four  = 3
		};

		enum class ControllerAxis
		{
			Left_X        = 0,
			Left_Y        = 1,
			Right_X       = 2,
			Right_Y       = 3,
			Left_Trigger  = 4,
			Right_Trigger = 5
		};
		
		enum class ControllerButton
		{
			A            = 0,
			B            = 1,
			X            = 2,
			Y            = 3,
			Left_Bumper  = 4,
			Right_Bumper = 5,
			Back         = 6,
			Start        = 7,
			Guide        = 8,
			Left_Thumb   = 9,
			Right_Thumb  = 10,
			DPad_Up      = 11,
			DPad_Right   = 12,
			DPad_Down    = 13,
			DPad_Left    = 14,
			Cross        = A,
			Circle       = B,
			Square       = X,
			Triangle     = Y
		};

		enum class ControllerDPad
		{
			Centered   = 0,
			Up         = 1,
			Right      = 2,
			Down       = 4,
			Left       = 8,
			Right_Up   = Right | Up,
			Right_Down = Right | Down,
			Left_Up    = Left | Up,
			Left_Down  = Left | Down
		};

		enum class ControllerBattery
		{
			Unknown,
			Empty,
			Low,
			Medium,
			Full
		};

		enum class ControllerConnectionType
		{
			Unknown,
			Wired,
			Wireless
		};

		struct ControllerStatus
		{
			bool Connected = false;
			ControllerConnectionType ConnectionType = ControllerConnectionType::Unknown;
			ControllerBattery BatteryStatus = ControllerBattery::Unknown;
		};

		//Used to determine which API to use(XInput or DirectInput)
		//This is only used for windows
		enum class ControllerAPI
		{
			Unknown,
			
			XInput,
			DirectInput,
			Linux
		};
		
		static void Init(ControllerAPI controllerAPI);
		static void Shutdown();

		static ControllerAPI GetControllerAPI();
		static void SetControllerAPI(ControllerAPI controllerAPI);
		
		static bool IsKeyPressed(Key key);
		static bool IsMouseButtonPressed(MouseButton button);
		static bool IsGamepadButtonPressed(Controller controller, ControllerButton button);
		static bool IsRawMouseInputSupported();
		static bool IsControllerConnected(Controller controller);
		static bool IsControllerGamepad(Controller controller);

		static Math::Vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
		static std::string GetKeyName(Key key);
		static float GetControllerAxis(Controller controller, ControllerAxis axis);
		static ControllerDPad GetControllerDPad(Controller controller, uint32_t dpad);
		static std::string GetControllerName(Controller controller);
		static const ControllerStatus& GetControllerStatus(Controller controller);
		static ControllerBattery GetControllerBatteryStatus(Controller controller);
		static ControllerConnectionType GetControllerConnectionType(Controller controller);
		static std::vector<float> GetAllControllerAxes(Controller controller);
		static std::vector<bool> GetAllControllerButtons(Controller controller);
		static std::vector<ControllerDPad> GetAllControllerDPads(Controller controller);
		static const std::array<ControllerStatus, 4>& GetAllControllerStatuses();

		static void SetControllerVibration(Controller controller, float leftMotor, float rightMotor);
		
		using EventCallbackFn = std::function<void(Event&)>;
		static void SetEventCallback(const EventCallbackFn& callback);
		
		static void UpdateControllerMappings(const std::string& map);

		void OnEvent(Event& e);
		
	private:
		//Universal API Methods
		static bool InitController();
		static void ShutdownController();
		static std::string GetControllerNameInternal(Controller controller);
		static std::vector<float> GetAllControllerAxesInternal(Controller controller);
		static std::vector<bool> GetAllControllerButtonsInternal(Controller controller);
		static std::vector<ControllerDPad> GetAllControllerDPadsInternal(Controller controller);
		static void SetControllerVibrationInternal(Controller controller, float leftMotor, float rightMotor);
		static bool PollController(Controller controller, int32_t mode);
		static void DetectControllerConnection(); //TODO call inside window events & This needs to be called in X11 windows when polling for events!
		static void CloseController(Controller controller);
		
#ifdef TRAP_PLATFORM_WINDOWS
		static constexpr const char* MappingName = "Windows";
		static void UpdateControllerConnectionWindows(); //TODO call inside window events
		static void UpdateControllerGUIDWindows(std::string& guid);
		//////////
		//XInput//
		//////////
		static void UpdateControllerBatteryAndConnectionTypeXInput(Controller controller);	
		static int32_t ControllerButtonToXInput(ControllerButton button);		
		static std::array<uint32_t, 4> s_lastXInputUpdate;
		///////////////
		//DirectInput//
		///////////////
		static BOOL CALLBACK DeviceObjectCallback(const DIDEVICEOBJECTINSTANCEW* doi, void* user);
		static bool SupportsXInput(const GUID* guid);
		static int CompareControllerObjects(const void* first, const void* second);
		static BOOL CALLBACK DeviceCallback(const DIDEVICEINSTANCE* deviceInstance, void* user);		
		static IDirectInput8W* API;		
		struct Object
		{
			int32_t Offset = 0;
			int32_t Type = 0;
		};
		struct ControllerWindows
		{
			std::vector<Object> Objects{};
			int32_t ObjectCount = 0;
			IDirectInputDevice8W* Device = nullptr;
			DWORD Index = 0;
			GUID guid{};
		};
		struct ObjectEnum
		{
			IDirectInputDevice8W* Device = nullptr;
			std::vector<Object> Objects;
			int32_t ObjectCount = 0;
			int32_t AxisCount = 0;
			int32_t SliderCount = 0;
			int32_t ButtonCount = 0;
			int32_t PoVCount = 0;
		};
#elif defined(TRAP_PLATFORM_LINUX)
		static constexpr const char* MappingName = "Linux";
		struct ControllerInternal;
		static bool OpenControllerDeviceLinux(const std::string& path);
		static void PollABSStateLinux(ControllerInternal* js);
		static void HandleABSEventLinux(ControllerInternal* js, int32_t code, int32_t value);
		static void HandleKeyEventLinux(ControllerInternal* js, int32_t code, int32_t value);		
		struct ControllerLinuxLibrary
		{
			int32_t INotify = 0;
			int32_t Watch = 0;
			regex_t Regex{};
			bool Dropped = false;
		};
		static ControllerLinuxLibrary s_linuxController;
		struct ControllerLinux
		{
			int32_t FD = 0;
			bool VibrationSupported = false;
			int16_t CurrentVibration = -1;
			std::string Path{};
			std::array<int32_t, KEY_CNT - BTN_MISC> KeyMap{};
			std::array<int32_t, ABS_CNT> ABSMap{};
			std::array<struct input_absinfo, ABS_CNT> ABSInfo{};
			std::array<std::array<int32_t, 4>, 2> DPads{};
		};
#endif

		bool OnControllerConnectEvent(ControllerConnectEvent& e);
		bool OnControllerDisconnectEvent(ControllerDisconnectEvent& e);
		
		static std::array<ControllerStatus, 4> s_controllerStatuses;
		static EventCallbackFn s_eventCallback;
		static ControllerAPI s_controllerAPI;

		//Controller mapping element
		struct MapElement
		{
			uint8_t Type = 0;
			uint8_t Index = 0;
			int8_t AxisScale = 0;
			int8_t AxisOffset = 0;
		};
		//Controller mapping
		struct Mapping
		{
			std::string Name{};
			std::string guid{};
			std::array<MapElement, 15> Buttons{};
			std::array<MapElement, 6> Axes{};
		};

		struct ControllerInternal
		{
			std::vector<float> Axes{};
			std::vector<bool> Buttons{};
			int32_t ButtonCount = 0;
			std::vector<ControllerDPad> DPads{};
			std::string Name{};
			void* UserPointer = nullptr;
			std::string guid{};
			Mapping* mapping = nullptr;
			
#ifdef TRAP_PLATFORM_WINDOWS
			ControllerWindows wsjs;
#elif defined(TRAP_PLATFORM_LINUX)
			ControllerLinux linjs;
#endif
		};
		static std::array<ControllerInternal, 4> s_controllerInternal;
		static ControllerInternal* AddInternalController(const std::string& name, const std::string& guid, int32_t axisCount, int32_t buttonCount, int32_t dpadCount);
		static void InternalInputControllerDPad(ControllerInternal* js, int32_t dpad, uint8_t value);
		static void InternalInputControllerAxis(ControllerInternal* js, int32_t axis, float value);
		static void InternalInputControllerButton(ControllerInternal* js, int32_t button, bool pressed);
		
		///////////
		//Mapping//
		///////////	
		static std::vector<Mapping> Mappings;
		
		static bool ParseMapping(Mapping& mapping, const std::string& str);
		static Mapping* FindMapping(const std::string& guid);
		static Mapping* FindValidMapping(const ControllerInternal* js);
		static bool IsValidElementForController(const MapElement* e, const ControllerInternal* js);
		static bool IsMappedControllerButtonPressed(Controller controller, ControllerButton button);
		static float GetMappedControllerAxis(Controller controller, ControllerAxis axis);
		static ControllerDPad GetMappedControllerDPad(Controller controller, uint32_t dpad);
	};
}

#endif /*_TRAP_INPUT_H_*/