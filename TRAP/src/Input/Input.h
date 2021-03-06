/*
Copyright (c) 2002-2006 Marcus Geelnard

Copyright (c) 2006-2019 Camilla Loewy

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would
   be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not
   be misrepresented as being the original software.

3. This notice may not be removed or altered from any source
   distribution.

Modified by: Jan "GamesTrap" Schuerkamp
The above license only applies to some of the Controller specific parts of this file!
*/

#ifndef _TRAP_INPUT_H_
#define _TRAP_INPUT_H_

#include "TRAPPCH.h" //Needed for OS dependent includes

#include "Maths/Math.h"
#include "Events/Event.h"

#include <functional>
#include <array>

namespace TRAP
{
	class Application;

	namespace INTERNAL
	{
		class WindowingAPI;
	}

	class Window;

	class Input final
	{
	public:
		/// <summary>
		/// Deleted Constructor.
		/// </summary>
		Input() = delete;
		/// <summary>
		/// Default Destructor.
		/// </summary>
		~Input() = default;

		/// <summary>
		/// Deleted Copy Constructor.
		/// </summary>
		Input(const Input&) = delete;
		/// <summary>
		/// Deleted Copy Assignment Operator.
		/// </summary>
		Input& operator=(const Input&) = delete;
		/// <summary>
		/// Deleted Move Constructor.
		/// </summary>
		Input(Input&&) = delete;
		/// <summary>
		/// Deleted Move Assignment Operator.
		/// </summary>
		Input& operator=(Input&&) = delete;

		/// <summary>
		/// Keyboard keys.
		/// </summary>
		enum class Key
		{
			Unknown = -1,
			
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
			Num_Lock       = 282,
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

		/// <summary>
		/// Mouse buttons.
		/// </summary>
		enum class MouseButton
		{
			One = 0,
			Two = 1,
			Three = 2,
			Four = 3,
			Five = 4,
			Six = 5,
			Seven = 6,
			Eight = 7,
			Left = One,
			Right = Two,
			Middle = Three
		};

		/// <summary>
		/// Controller
		/// </summary>
		enum class Controller
		{
			One      = 0,
			Two      = 1,
			Three    = 2,
			Four     = 3,
			Five     = 4,
			Six      = 5,
			Seven    = 6,
			Eight    = 7,
			Nine     = 8,
			Ten      = 9,
			Eleven   = 10,
			Twelve   = 11,
			Thirteen = 12,
			Fourteen = 13,
			Fifteen  = 14,
			Sixteen  = 15
		};

		/// <summary>
		/// Controller axis.
		/// </summary>
		enum class ControllerAxis
		{
			Left_X        = 0,
			Left_Y        = 1,
			Right_X       = 2,
			Right_Y       = 3,
			Left_Trigger  = 4,
			Right_Trigger = 5
		};

		/// <summary>
		/// Controller buttons.
		/// </summary>
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

		/// <summary>
		/// Controller DPad.
		/// </summary>
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

		/// <summary>
		/// Check if a button on the keyboard is pressed.
		/// </summary>
		/// <param name="key">Key to check.</param>
		/// <returns>True if provided key is pressed, false otherwise.</returns>
		static bool IsKeyPressed(Key key);
		/// <summary>
		/// Check if a button on the keyboard in the specified Window is pressed.
		/// </summary>
		/// <param name="key">Key to check.</param>
		/// <param name="window">Window to check on.</param>
		/// <returns>True if provided key is pressed in provided Window, false otherwise.</returns>
		static bool IsKeyPressed(Key key, const Scope<Window>& window);
		/// <summary>
		/// Check if a mouse button on the mouse is pressed.
		/// </summary>
		/// <param name="button">Mouse button to check.</param>
		/// <returns>True if provided mouse button is pressed, false otherwise.</returns>
		static bool IsMouseButtonPressed(MouseButton button);
		/// <summary>
		/// Check if a mouse button on the mouse in the specified Window is pressed.
		/// </summary>
		/// <param name="button">Mouse button to check.</param>
		/// <param name="window">Window to check on.</param>
		/// <returns>True if provided mouse button is pressed in provided Window, false otherwise.</returns>
		static bool IsMouseButtonPressed(MouseButton button, const Scope<Window>& window);
		/// <summary>
		/// Retrieve whether raw mouse input is supported.
		/// </summary>
		/// <returns>True if raw mouse input is supported, false otherwise.</returns>
		static bool IsRawMouseInputSupported();
		/// <summary>
		/// Check if a specific Controller is connected.
		/// </summary>
		/// <param name="controller">Controller to check</param>
		/// <returns>True if provided Controller is connected, false otherwise.</returns>
		static bool IsControllerConnected(Controller controller);
		/// <summary>
		/// Check if a Controller is a Gamepad (is able to map to an XBox like Controller).
		/// </summary>
		/// <param name="controller">Controller to check.</param>
		/// <returns>True if Controller is a Gamepad, false otherwise.</returns>
		static bool IsControllerGamepad(Controller controller);

		/// <summary>
		/// Retrieve the current mouse position.
		/// </summary>
		/// <returns>Mouse position as a Math::Vec2.</returns>
		static Math::Vec2 GetMousePosition();
		/// <summary>
		/// Retrieve the current mouse position for the provided Window.
		/// </summary>
		/// <param name="window">Window to check.</param>
		/// <returns>Mouse position of the Window as a Math::Vec2.</returns>
		static Math::Vec2 GetMousePosition(const Scope<Window>& window);
		/// <summary>
		/// Retrieve the current mouse position on the x axis.
		/// </summary>
		/// <returns>X mouse position.</returns>
		static float GetMouseX();
		/// <summary>
		/// Retrieve the current mouse position on the y axis.
		/// </summary>
		/// <returns>Y mouse position.</returns>
		static float GetMouseY();
		/// <summary>
		/// Retrieve the current mouse position on the x axis for the provided Window.
		/// </summary>
		/// <param name="window">Window to check.</param>
		/// <returns>X mouse position.</returns>
		static float GetMouseX(const Scope<Window>& window);
		/// <summary>
		/// Retrieve the current mouse position on the y axis for the provided Window.
		/// </summary>
		/// <param name="window">Window to check.</param>
		/// <returns>Y mouse position.</returns>
		static float GetMouseY(const Scope<Window>& window);
		/// <summary>
		/// Retrieve the string representation of a Key.
		/// </summary>
		/// <param name="key">Key to retrieve.</param>
		/// <returns>String representation of Key.</returns>
		static std::string GetKeyName(Key key);
		/// <summary>
		/// Retrieve the value of the specified ControllerAxis from the provided Controller.
		/// </summary>
		/// <param name="controller">Controller to query.</param>
		/// <param name="axis">ControllerAxis to check.</param>
		/// <returns>Value of the axis.</returns>
		static float GetControllerAxis(Controller controller, ControllerAxis axis);
		/// <summary>
		/// Retrieve the state of the specified DPad from the provided Controller.
		/// </summary>
		/// <param name="controller">Controller to query.</param>
		/// <param name="dpad">DPad to check.</param>
		/// <returns>State of DPad.</returns>
		static ControllerDPad GetControllerDPad(Controller controller, uint32_t dpad);

		/// <summary>
		/// Retrieve whether the specified ControllerButton from the provided Controller is pressed or not.
		/// </summary>
		/// <param name="controller">Controller to query.</param>
		/// <param name="button">ControllerButton to check.</param>
		/// <returns>True if ControllerButton is pressed, false otherwise.</returns>
		static bool IsControllerButtonPressed(Controller controller, ControllerButton button);
		/// <summary>
		/// Retrieve the name of the provided Controller.
		/// </summary>
		/// <param name="controller">Controller to query.</param>
		/// <returns>Name of the Controller.</returns>
		static std::string GetControllerName(Controller controller);
		/// <summary>
		/// Retrieve the GUID of the provided Controller.
		/// </summary>
		/// <param name="controller">Controller to query.</param>
		/// <returns>GUID of the Controller.</returns>
		static std::string GetControllerGUID(Controller controller);
		/// <summary>
		/// Retrieve all states of every Axis from the provided Controller.
		/// </summary>
		/// <param name="controller">Controller to query.</param>
		/// <returns>Vector with every Axis state.</returns>
		static std::vector<float> GetAllControllerAxes(Controller controller);
		/// <summary>
		/// Retrieve all states of every button from the provided Controller.
		/// </summary>
		/// <param name="controller">Controller to query.</param>
		/// <returns>Vector with every button state.</returns>
		static std::vector<bool> GetAllControllerButtons(Controller controller);
		/// <summary>
		/// Retrieve all states of every DPad from the provided Controller.
		/// </summary>
		/// <param name="controller">Controller to query.</param>
		/// <returns>Vector with every DPad state.</returns>
		static std::vector<ControllerDPad> GetAllControllerDPads(Controller controller);

		/// <summary>
		/// Retrieve the name of the current keyboard layout.
		/// </summary>
		/// <returns>Name of keyboard layout.</returns>
		static std::string GetKeyboardLayoutName();

		/// <summary>
		/// Set the vibration level(s) for the specified Controller.<br>
		/// Intensity values are normalized and range from 0-1.
		/// Note: Only takes effect when on Linux or Windows via XInput (DirectInput doesn't support vibrations)!
		/// </summary>
		/// <param name="controller">Controller to affect.</param>
		/// <param name="leftMotor">Normalized intensity for the left motor.</param>
		/// <param name="rightMotor">Normalized intensity for the right motor.</param>
		static void SetControllerVibration(Controller controller, float leftMotor, float rightMotor);
		/// <summary>
		/// Set the vibration level(s) for the specified Controller.<br>
		/// Intensity values are normalized and range from 0-1.
		/// Note: Only takes effect when on Linux or Windows via XInput (DirectInput doesn't support vibrations)!
		/// </summary>
		/// <param name="controller">Controller to affect.</param>
		/// <param name="intensity">Normalized intensity for both motors.</param>
		static void SetControllerVibration(Controller controller, const Math::Vec2& intensity);

		/// <summary>
		/// Set the mouse position.
		/// </summary>
		/// <param name="x">New X position.</param>
		/// <param name="y">New Y position.</param>
		static void SetMousePosition(float x, float y);
		/// <summary>
		/// Set the mouse position for the provided Window.
		/// </summary>
		/// <param name="x">New X position.</param>
		/// <param name="y">New Y position.</param>
		/// <param name="window">Window to affect.</param>
		static void SetMousePosition(float x, float y, const Scope<Window>& window);
		/// <summary>
		/// Set the mouse position.
		/// </summary>
		/// <param name="position">New position.</param>
		static void SetMousePosition(const Math::Vec2& position);
		/// <summary>
		/// Set the mouse position for the provided Window.
		/// </summary>
		/// <param name="position">New position.</param>
		/// <param name="window">Window to affect.</param>
		static void SetMousePosition(const Math::Vec2& position, const Scope<Window>& window);

		/// <summary>
		/// Set the system clipboard to the specified UTF-8 encoded string.
		/// </summary>
		/// <param name="str">string.</param>
		static void SetClipboard(std::string_view str);
		/// <summary>
		/// Retrieve the contents of the system clipboard.
		/// </summary>
		/// <returns>Contents of clipboard.</returns>
		static std::string GetClipboard();
		
		/// <summary>
		/// Update an existing Controller mapping or add a new one.<br>
		/// <br>
		/// Description:<br>
		/// Each mapping is a single line of comma-separated values describing the GUID, name and layout of the Controller.<br>
		/// Note: Lines that do not begin with a hexadecimal digit are ignored!<br>
		/// <br>
		/// The first value is always the Controller GUID, a 32 character long hexadecimal string that typically identifies its make, model, revision and tht type
		/// of connection to the computer.<br>
		/// When this information is not available, the GUID is generated using the Controller name.<br>
		/// TRAP uses the SDL 2.0.5+ GUID format but can convert from the older formats.<br>
		/// <br>
		/// The second value is always the human-readable name of the Controller.<br>
		/// <br>
		/// All subsequent values are in the form "<field>:<value>" and describe the layout of the mapping.<br>
		/// These fields may not all be present and may occur in any order.<br>
		/// <br>
		/// The button fields are "a", "b", "c", "d", "back", "start", "guide", "dpup", "dpright", "dpdown", "dpleft", "leftshoulder", "rightshoulder", "leftstick" and "rightstick".<br>
		/// The axis fields are "leftx", "lefty", "rightx", "righty", "lefttrigger" and "righttrigger".<br>
		/// <br>
		/// The value of an axis or button field can be a Controller button, a Controller axis, a hat bitmask or empty.<br>
		/// Controller buttons are specified as "bN", for example "b2" for the third button.<br>
		/// Controller axes are specified as "aN", for example "a7" for the eighth axis.<br>
		/// Controller hit bit masks are specified as "hN.N", for example "h0.8" for left on the first hat. More than one bit may be set in the mask.<br>
		/// <br>
		/// Before an axis there may be a "+" or "-" range modifier, for example "+a3" for the positive half of the fourth axis.<br>
		/// This restricts input to only the positive or negative halves of the Controller axis.<br>
		/// After an axis of half-axis there may be the "~" inversion modifier, for example "a2~" or "-a7~".<br>
		/// This negates the values of the Controller axis.<br>
		/// <br>
		/// There is also the special "platform" field that specifies which platform the mapping is valid for.<br>
		/// Possible values are "Windows" and "Linux".
		/// </summary>
		/// <param name="map">Controller mapping to update or add.</param>
		static void UpdateControllerMappings(std::string_view map);

	private:
		/// <summary>
		/// Describes a callback function which gets called when an Input Event occurs.
		/// </summary>
		using EventCallbackFn = std::function<void(Events::Event&)>;
		/// <summary>
		/// Set the function to call when an Input Event occurred.
		/// </summary>
		/// <param name="callback">Function to call.</param>
		static void SetEventCallback(const EventCallbackFn& callback);

		/// <summary>
		/// Initialize Input.
		/// </summary>
		static void Init();
		/// <summary>
		/// Shutdown Input.
		/// </summary>
		static void Shutdown();
		
		friend class TRAP::Application;
		
#ifdef TRAP_PLATFORM_WINDOWS
		static void DetectControllerConnectionWin32();
		static void DetectControllerDisconnectionWin32();
#elif defined(TRAP_PLATFORM_LINUX)
		static void DetectControllerConnectionLinux();
#endif
		friend class TRAP::INTERNAL::WindowingAPI;

		/// <summary>
		/// Modes for polling.
		/// </summary>
		enum class PollMode
		{
			Presence = 0,
			Axes = 1,
			Buttons = 2,
			All = (Axes | Buttons)
		};
		
		//Universal API Methods

		/// <summary>
		/// Initialize Controller(s).
		/// </summary>
		/// <returns>True on success, false otherwise.</returns>
		static bool InitController();
		/// <summary>
		/// Shutdown Controller(s).
		/// </summary>
		static void ShutdownController();
		/// <summary>
		/// OS-dependent function for Controller vibrations.
		/// </summary>
		static void SetControllerVibrationInternal(Controller controller, float leftMotor, float rightMotor);
		/// <summary>
		/// OS-dependent function for Controller polling.
		/// </summary>
		/// <param name="controller">Controller to poll.</param>
		/// <param name="mode">Mode for polling.</param>
		/// <returns>True on success, false otherwise.</returns>
		static bool PollController(Controller controller, PollMode mode);
		/// <summary>
		/// OS-dependent function for Controller disconnections.
		/// </summary>
		/// <param name="controller">Controller to disconnect.</param>
		static void CloseController(Controller controller);
		/// <summary>
		/// OS-dependent function for updating a Controller GUID.
		/// </summary>
		/// <param name="guid">New GUID.</param>
		static void UpdateControllerGUID(std::string& guid);
		
#ifdef TRAP_PLATFORM_WINDOWS
		static constexpr std::string_view MappingName = "Windows";
		///////////////
		//DirectInput//
		///////////////
		//dinput8.dll function pointer typedefs
		static constexpr uint32_t TRAP_TYPE_AXIS = 0;
		static constexpr uint32_t TRAP_TYPE_SLIDER = 1;
		static constexpr uint32_t TRAP_TYPE_BUTTON = 2;
		static constexpr uint32_t TRAP_TYPE_DPAD = 3;
		//Define local copies of the necessary GUIDs
		static constexpr GUID TRAP_IID_IDirectInput8W =
		{ 0xbf798031,0x483a,0x4da2,{0xaa,0x99,0x5d,0x64,0xed,0x36,0x97,0x00} };
		static constexpr GUID TRAP_GUID_XAxis =
		{ 0xa36d02e0,0xc9f3,0x11cf,{0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00} };
		static constexpr GUID TRAP_GUID_YAxis =
		{ 0xa36d02e1,0xc9f3,0x11cf,{0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00} };
		static constexpr GUID TRAP_GUID_ZAxis =
		{ 0xa36d02e2,0xc9f3,0x11cf,{0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00} };
		static constexpr GUID TRAP_GUID_RxAxis =
		{ 0xa36d02f4,0xc9f3,0x11cf,{0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00} };
		static constexpr GUID TRAP_GUID_RyAxis =
		{ 0xa36d02f5,0xc9f3,0x11cf,{0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00} };
		static constexpr GUID TRAP_GUID_RzAxis =
		{ 0xa36d02e3,0xc9f3,0x11cf,{0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00} };
		static constexpr GUID TRAP_GUID_Slider =
		{ 0xa36d02e4,0xc9f3,0x11cf,{0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00} };
		static constexpr GUID TRAP_GUID_DPad =
		{ 0xa36d02f2,0xc9f3,0x11cf,{0xbf,0xc7,0x44,0x45,0x53,0x54,0x00,0x00} };
		static constexpr GUID TRAP_GUID_IID_IDirectInputDevice2W =
		{ 0x5944E683,0xC92E,0x11CF,{0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00} };
		//Object data array for our clone of c_dfDIJoystick
		inline static std::array<DIOBJECTDATAFORMAT, 44> TRAPObjectDataFormats =
		{
			{
				{ &TRAP_GUID_XAxis,DIJOFS_X,DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,DIDOI_ASPECTPOSITION },
				{ &TRAP_GUID_YAxis,DIJOFS_Y,DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,DIDOI_ASPECTPOSITION },
				{ &TRAP_GUID_ZAxis,DIJOFS_Z,DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,DIDOI_ASPECTPOSITION },
				{ &TRAP_GUID_RxAxis,DIJOFS_RX,DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,DIDOI_ASPECTPOSITION },
				{ &TRAP_GUID_RyAxis,DIJOFS_RY,DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,DIDOI_ASPECTPOSITION },
				{ &TRAP_GUID_RzAxis,DIJOFS_RZ,DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,DIDOI_ASPECTPOSITION },
				{ &TRAP_GUID_Slider,DIJOFS_SLIDER(0),DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,DIDOI_ASPECTPOSITION },
				{ &TRAP_GUID_Slider,DIJOFS_SLIDER(1),DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,DIDOI_ASPECTPOSITION },
				{ &TRAP_GUID_DPad,DIJOFS_POV(0),DIDFT_POV | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ &TRAP_GUID_DPad,DIJOFS_POV(1),DIDFT_POV | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ &TRAP_GUID_DPad,DIJOFS_POV(2),DIDFT_POV | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ &TRAP_GUID_DPad,DIJOFS_POV(3),DIDFT_POV | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(0),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(1),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(2),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(3),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(4),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(5),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(6),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(7),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(8),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(9),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(10),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(11),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(12),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(13),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(14),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(15),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(16),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(17),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(18),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(19),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(20),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(21),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(22),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(23),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(24),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(25),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(26),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(27),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(28),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(29),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(30),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 },
				{ nullptr,DIJOFS_BUTTON(31),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0 }
			}
		};
		//Our clone of c_dfDIJoystick
		inline static const DIDATAFORMAT TRAPDataFormat =
		{
			sizeof(DIDATAFORMAT),
			sizeof(DIOBJECTDATAFORMAT),
			DIDFT_ABSAXIS,
			sizeof(DIJOYSTATE2),
			static_cast<DWORD>(TRAPObjectDataFormats.size()),
			const_cast<DIOBJECTDATAFORMAT*>(TRAPObjectDataFormats.data())
		};
		typedef HRESULT(WINAPI* PFN_DirectInput8Create)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);
		struct DInput8
		{
			HINSTANCE Instance{};
			PFN_DirectInput8Create Create{};
			IDirectInput8W* API = nullptr;
		} inline static s_dinput8{};

		//////////
		//XInput//
		//////////
		//xinput.dll function pointer typedefs
		static constexpr uint32_t TRAP_XINPUT_CAPS_WIRELESS = 0x0002;
		static constexpr uint32_t TRAP_XINPUT_DEVSUBTYPE_GAMEPAD = 0x01;
		static constexpr uint32_t TRAP_XINPUT_DEVSUBTYPE_WHEEL = 0x02;
		static constexpr uint32_t TRAP_XINPUT_DEVSUBTYPE_ARCADE_STICK = 0x03;
		static constexpr uint32_t TRAP_XINPUT_DEVSUBTYPE_FLIGHT_STICK = 0x04;
		static constexpr uint32_t TRAP_XINPUT_DEVSUBTYPE_DANCE_PAD = 0x05;
		static constexpr uint32_t TRAP_XINPUT_DEVSUBTYPE_GUITAR = 0x06;
		static constexpr uint32_t TRAP_XINPUT_DEVSUBTYPE_DRUM_KIT = 0x08;
		static constexpr uint32_t TRAP_XINPUT_DEVSUBTYPE_ARCADE_PAD = 0x13;
		static constexpr uint32_t TRAP_XUSER_MAX_COUNT = 4;
		typedef DWORD(WINAPI* PFN_XInputGetCapabilities)(DWORD, DWORD, XINPUT_CAPABILITIES*);
		typedef DWORD(WINAPI* PFN_XInputGetState)(DWORD, XINPUT_STATE*);
		typedef DWORD(WINAPI* PFN_XInputSetState)(DWORD, XINPUT_VIBRATION*);
		static BOOL CALLBACK DeviceObjectCallback(const DIDEVICEOBJECTINSTANCEW* doi, void* user);
		static int CompareControllerObjects(const void* first, const void* second);
		static BOOL CALLBACK DeviceCallback(const DIDEVICEINSTANCE* deviceInstance, void* user);
		static bool SupportsXInput(const GUID* guid);
		static std::string GetDeviceDescription(const XINPUT_CAPABILITIES* xic);
		struct XInput
		{
			HINSTANCE Instance{};
			PFN_XInputGetCapabilities GetCapabilities{};
			PFN_XInputGetState GetState{};
			PFN_XInputSetState SetState{};
		} inline static s_xinput{};
		
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
			bool XInput = false;
			bool ForceFeedback = false;
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
		static constexpr std::string_view MappingName = "Linux";
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
		
		static EventCallbackFn s_eventCallback;

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
			bool Connected = false;
			float LeftMotor = 0.0f;
			float RightMotor = 0.0f;
			
#ifdef TRAP_PLATFORM_WINDOWS
			ControllerWindows WinCon;
#elif defined(TRAP_PLATFORM_LINUX)
			ControllerLinux LinuxCon;
#endif
		};
		static std::array<ControllerInternal, 16> s_controllerInternal;
		/// <summary>
		/// Internally add a Controller.
		/// </summary>
		/// <param name="name">Name of the Controller.</param>
		/// <param name="guid">GUID of the Controller.</param>
		/// <param name="axisCount">Amount of Axes.</param>
		/// <param name="buttonCount">Amount of Buttons.</param>
		/// <param name="dpadCount">Amount of DPads.</param>
		/// <returns>Pointer to the new ControllerInternal or nullptr if there are already 16 Controller connected.</returns>
		static ControllerInternal* AddInternalController(const std::string& name, const std::string& guid, int32_t axisCount, int32_t buttonCount, int32_t dpadCount);
		/// <summary>
		/// Internally DPad input processing.
		/// </summary>
		/// <param name="con">Which Controller.</param>
		/// <param name="dpad">Which DPad.</param>
		/// <param name="value">New State.</param>
		static void InternalInputControllerDPad(ControllerInternal* con, int32_t dpad, uint8_t value);
		/// <summary>
		/// Internally Axis input processing.
		/// </summary>
		/// <param name="con">Which Controller</param>
		/// <param name="axis">Which DPad.</param>
		/// <param name="value">New Axis value.</param>
		static void InternalInputControllerAxis(ControllerInternal* con, int32_t axis, float value);
		/// <summary>
		/// Internally Button input processing.
		/// </summary>
		/// <param name="con">Which Controller.</param>
		/// <param name="button">Which Button.</param>
		/// <param name="pressed">New pressed or not pressed state.</param>
		static void InternalInputControllerButton(ControllerInternal* con, int32_t button, bool pressed);
		
		///////////
		//Mapping//
		///////////	
		static std::vector<Mapping> s_mappings;

		/// <summary>
		/// Parse a string to a Mapping.
		/// </summary>
		/// <param name="mapping">Output variable for the new Mapping.</param>
		/// <param name="str">Mapping as a string representation.</param>
		/// <returns>True on success, false otherwise.</returns>
		static bool ParseMapping(Mapping& mapping, std::string_view str);
		/// <summary>
		/// Find a loaded Mapping via its GUID.
		/// </summary>
		/// <param name="guid">GUID to search for.</param>
		/// <returns>When found Pointer to Mapping, nullptr otherwise.</returns>
		static Mapping* FindMapping(std::string_view guid);
		/// <summary>
		/// Find a Mapping based on Controller GUID and verifies validity.
		/// </summary>
		/// <param name="con">Controller from which to use GUID.</param>
		/// <returns>When found and valid Pointer to Mapping, nullptr otherwise.</returns>
		static Mapping* FindValidMapping(const ControllerInternal* con);
		/// <summary>
		/// Checks whether a Controller Mapping element is present in the hardware.
		/// </summary>
		/// <param name="e">Map element to check.</param>
		/// <param name="con">Controller to validate with.</param>
		/// <returns>True if MapElement is present in hardware, false otherwise.</returns>
		static bool IsValidElementForController(const MapElement* e, const ControllerInternal* con);
		/// <summary>
		/// Retrieve state of a specific button from a Controller.
		/// </summary>
		/// <param name="controller">Controller to query.</param>
		/// <param name="button">Button to get state from.</param>
		/// <returns>On success button state, false otherwise.</returns>
		static bool GetMappedControllerButton(Controller controller, ControllerButton button);
		/// <summary>
		/// Retrieve state of a specific axis from a Controller.
		/// </summary>
		/// <param name="controller">Controller to query.</param>
		/// <param name="axis">Axis to get state from.</param>
		/// <returns>On success axis state, 0.0f otherwise.</returns>
		static float GetMappedControllerAxis(Controller controller, ControllerAxis axis);
		/// <summary>
		/// Retrieve state of a specific DPad from a Controller.
		/// </summary>
		/// <param name="controller">Controller to query.</param>
		/// <param name="dpad">DPad to get state from.</param>
		/// <returns>On success DPad state, ControllerDPad::Centered otherwise.</returns>
		static ControllerDPad GetMappedControllerDPad(Controller controller, uint32_t dpad);
	};
}

#endif /*_TRAP_INPUT_H_*/