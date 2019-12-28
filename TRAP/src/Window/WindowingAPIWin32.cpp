#include "TRAPPCH.h"
#include "WindowingAPI.h"
#include "Utils/String.h"

#ifdef TRAP_PLATFORM_WINDOWS

//Replacement for IsWindowsVersionOrGreater as MinGW lacks versionhelpers.h
BOOL TRAP::INTERNAL::WindowingAPI::IsWindowsVersionOrGreaterWin32(const WORD major, const WORD minor, const WORD sp)
{
	OSVERSIONINFOEXW osvi = { sizeof(osvi), major, minor, 0, 0, {0}, sp };
	const DWORD mask = VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR;
	ULONGLONG cond = VerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL);
	cond = VerSetConditionMask(cond, VER_MINORVERSION, VER_GREATER_EQUAL);
	cond = VerSetConditionMask(cond, VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);
	//HACK: Use RtlVerifyVersionInfo instead of VerifyVersionInfoW as the
	//      latter lies unless the user knew to embed a non-default manifest
	//      announcing support for Windows 10 via supportedOS GUID
	return s_Data.NTDLL.RtlVerifyVersionInfo(&osvi, mask, cond) == 0;
}

//-------------------------------------------------------------------------------------------------------------------//

//Checks whether we are on at least the specified build of Windows 10
BOOL TRAP::INTERNAL::WindowingAPI::IsWindows10BuildOrGreaterWin32(const WORD build)
{
	OSVERSIONINFOEXW osvi = { sizeof(osvi), 10, 0, build };
	const DWORD mask = VER_MAJORVERSION | VER_MINORVERSION | VER_BUILDNUMBER;
	ULONGLONG cond = VerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL);
	cond = VerSetConditionMask(cond, VER_MINORVERSION, VER_GREATER_EQUAL);
	cond = VerSetConditionMask(cond, VER_BUILDNUMBER, VER_GREATER_EQUAL);
	//HACK: Use RtlVerifyVersionInfo instead of VerifyVersionInfoW as the
	//      latter lies unless the user knew to embed a non-default manifest
	//      announcing support for Windows 10 via supportedOS GUID
	return s_Data.NTDLL.RtlVerifyVersionInfo(&osvi, mask, cond) == 0;
}

//-------------------------------------------------------------------------------------------------------------------//

//Checks whether we are on at least Windows 10 Anniversary Update
BOOL TRAP::INTERNAL::WindowingAPI::IsWindows10AnniversaryUpdateOrGreaterWin32()
{
	return IsWindows10BuildOrGreaterWin32(14393);
}

//-------------------------------------------------------------------------------------------------------------------//

//Checks whether we are on at least Windows 10 Creators Update
BOOL TRAP::INTERNAL::WindowingAPI::IsWindows10CreatorsUpdateOrGreaterWin32()
{
	return IsWindows10BuildOrGreaterWin32(15063);
}

//-------------------------------------------------------------------------------------------------------------------//

//Checks whether we are on at least Windows 8.1
BOOL TRAP::INTERNAL::WindowingAPI::IsWindows8Point1OrGreaterWin32()
{
	return IsWindowsVersionOrGreaterWin32(HIBYTE(_WIN32_WINNT_WINBLUE),
		LOBYTE(_WIN32_WINNT_WINBLUE), 0);
}

//-------------------------------------------------------------------------------------------------------------------//

//Checks whether we are on at least Windows 8
BOOL TRAP::INTERNAL::WindowingAPI::IsWindows8OrGreaterWin32()
{
	return IsWindowsVersionOrGreaterWin32(HIBYTE(_WIN32_WINNT_WIN8),
		LOBYTE(_WIN32_WINNT_WIN8), 0);
}

//-------------------------------------------------------------------------------------------------------------------//

//Checks whether we are on at least Windows 7
BOOL TRAP::INTERNAL::WindowingAPI::IsWindows7OrGreaterWin32()
{
	return IsWindowsVersionOrGreaterWin32(HIBYTE(_WIN32_WINNT_WIN7),
		LOBYTE(_WIN32_WINNT_WIN7), 0);
}

//-------------------------------------------------------------------------------------------------------------------//

//Checks whether we are on at least Windows Vista
BOOL TRAP::INTERNAL::WindowingAPI::IsWindowsVistaOrGreaterWin32()
{
	return IsWindowsVersionOrGreaterWin32(HIBYTE(_WIN32_WINNT_VISTA),
		LOBYTE(_WIN32_WINNT_VISTA), 0);
}

//-------------------------------------------------------------------------------------------------------------------//

//Checks whether we are on at least Windows XP
BOOL TRAP::INTERNAL::WindowingAPI::IsWindowsXPOrGreaterWin32()
{
	return IsWindowsVersionOrGreaterWin32(HIBYTE(_WIN32_WINNT_WINXP),
		LOBYTE(_WIN32_WINNT_WINXP), 0);
}

//-------------------------------------------------------------------------------------------------------------------//

//Returns an UTF-8 string version of the specified wide string
std::string TRAP::INTERNAL::WindowingAPI::CreateUTF8StringFromWideStringWin32(const std::wstring& wStr)
{
	std::string result{};

	const int32_t size = WideCharToMultiByte(CP_UTF8, 0, wStr.data(), -1, nullptr, 0, nullptr, nullptr);
	if (!size)
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to convert string to UTF-8");
		return {};
	}

	result.resize(size);
	if (!WideCharToMultiByte(CP_UTF8, 0, wStr.data(), -1, result.data(), size, nullptr, nullptr))
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to convert string to UTF-8");
		return {};
	}

	return result;
}

//-------------------------------------------------------------------------------------------------------------------//

std::wstring TRAP::INTERNAL::WindowingAPI::CreateWideStringFromUTF8StringWin32(const std::string& str)
{
	std::wstring result{};

	const int32_t count = MultiByteToWideChar(CP_UTF8, 0, str.data(), -1, nullptr, 0);
	if (!count)
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to convert string from UTF-8");
		return {};
	}

	result.resize(count);

	if (!MultiByteToWideChar(CP_UTF8, 0, str.data(), -1, result.data(), count))
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to convert string from UTF-8");
		return {};
	}

	return result;
}

//-------------------------------------------------------------------------------------------------------------------//

//Load necessary libraries (DLLs)
bool TRAP::INTERNAL::WindowingAPI::LoadLibraries()
{
	s_Data.User32.Instance = LoadLibraryA("user32.dll");
	if (!s_Data.User32.Instance)
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to load user32.dll");
		return false;
	}

	s_Data.User32.SetProcessDPIAware = reinterpret_cast<PFN_SetProcessDPIAware>(::GetProcAddress(s_Data.User32.Instance, "SetProcessDPIAware"));
	s_Data.User32.ChangeWindowMessageFilterEx = reinterpret_cast<PFN_ChangeWindowMessageFilterEx>(::GetProcAddress(s_Data.User32.Instance, "ChangeWindowMessageFilterEx"));
	s_Data.User32.EnableNonClientDPIScaling = reinterpret_cast<PFN_EnableNonClientDPIScaling>(::GetProcAddress(s_Data.User32.Instance, "EnableNonClientDpiScaling"));
	s_Data.User32.SetProcessDPIAwarenessContext = reinterpret_cast<PFN_SetProcessDPIAwarenessContext>(::GetProcAddress(s_Data.User32.Instance, "SetProcessDpiAwarenessContext"));
	s_Data.User32.GetDPIForWindow = reinterpret_cast<PFN_GetDPIForWindow>(::GetProcAddress(s_Data.User32.Instance, "GetDpiForWindow"));
	s_Data.User32.AdjustWindowRectExForDPI = reinterpret_cast<PFN_AdjustWindowRectExForDPI>(::GetProcAddress(s_Data.User32.Instance, "AdjustWindowRectExForDpi"));

	s_Data.DWMAPI_.Instance = LoadLibraryA("dwmapi.dll");
	if (s_Data.DWMAPI_.Instance)
	{
		s_Data.DWMAPI_.IsCompositionEnabled = reinterpret_cast<PFN_DwmIsCompositionEnabled>(::GetProcAddress(s_Data.DWMAPI_.Instance, "DwmIsCompositionEnabled"));
		s_Data.DWMAPI_.Flush = reinterpret_cast<PFN_DwmFlush>(::GetProcAddress(s_Data.DWMAPI_.Instance, "DwmFlush"));
		s_Data.DWMAPI_.EnableBlurBehindWindow = reinterpret_cast<PFN_DwmEnableBlurBehindWindow>(::GetProcAddress(s_Data.DWMAPI_.Instance, "DwmEnableBlurBehindWindow"));
	}
	
	s_Data.SHCore.Instance = LoadLibraryA("shcore.dll");
	if (s_Data.SHCore.Instance)
	{
		s_Data.SHCore.SetProcessDPIAwareness = reinterpret_cast<PFN_SetProcessDPIAwareness>(::GetProcAddress(s_Data.SHCore.Instance, "SetProcessDpiAwareness"));
		s_Data.SHCore.GetDPIForMonitor = reinterpret_cast<PFN_GetDPIForMonitor>(::GetProcAddress(s_Data.SHCore.Instance, "GetDpiForMonitor"));
	}

	s_Data.NTDLL.Instance = LoadLibraryA("ntdll.dll");
	if (s_Data.NTDLL.Instance)
		s_Data.NTDLL.RtlVerifyVersionInfo = reinterpret_cast<PFN_RtlVerifyVersionInfo>(::GetProcAddress(s_Data.NTDLL.Instance, "RtlVerifyVersionInfo"));

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

//Unload used libraries (DLLs)
void TRAP::INTERNAL::WindowingAPI::FreeLibraries()
{
	if (s_Data.User32.Instance)
		FreeLibrary(s_Data.User32.Instance);

	if (s_Data.DWMAPI_.Instance)
		FreeLibrary(s_Data.DWMAPI_.Instance);

	if (s_Data.SHCore.Instance)
		FreeLibrary(s_Data.SHCore.Instance);

	if (s_Data.NTDLL.Instance)
		FreeLibrary(s_Data.NTDLL.Instance);
}

//-------------------------------------------------------------------------------------------------------------------//

//Reports the specified error, appending information about the last Win32 error
void TRAP::INTERNAL::WindowingAPI::InputErrorWin32(const Error error, const std::string description)
{
	std::wstring buffer{};
	buffer.resize(1024);
	std::string message;
	message.resize(10249);

	FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS |
		FORMAT_MESSAGE_MAX_WIDTH_MASK,
		nullptr,
		GetLastError() & 0xffff,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		buffer.data(),
		static_cast<DWORD>(buffer.size()),
		nullptr);
	WideCharToMultiByte(CP_UTF8, 0, buffer.data(), -1, message.data(), static_cast<int32_t>(message.size()), nullptr, nullptr);

	InputError(error, description + ": " + message);
}

//-------------------------------------------------------------------------------------------------------------------//

//Create key code translation tables
void TRAP::INTERNAL::WindowingAPI::CreateKeyTables()
{
	std::fill(s_Data.KeyCodes.begin(), s_Data.KeyCodes.end(), Input::Key::Unknown);
	std::fill(s_Data.ScanCodes.begin(), s_Data.ScanCodes.end(), -1);

	s_Data.KeyCodes[0x00B] = Input::Key::Zero;
	s_Data.KeyCodes[0x002] = Input::Key::One;
	s_Data.KeyCodes[0x003] = Input::Key::Two;
	s_Data.KeyCodes[0x004] = Input::Key::Three;
	s_Data.KeyCodes[0x005] = Input::Key::Four;
	s_Data.KeyCodes[0x006] = Input::Key::Five;
	s_Data.KeyCodes[0x007] = Input::Key::Six;
	s_Data.KeyCodes[0x008] = Input::Key::Seven;
	s_Data.KeyCodes[0x009] = Input::Key::Eight;
	s_Data.KeyCodes[0x00A] = Input::Key::Nine;
	s_Data.KeyCodes[0x01E] = Input::Key::A;
	s_Data.KeyCodes[0x030] = Input::Key::B;
	s_Data.KeyCodes[0x02E] = Input::Key::C;
	s_Data.KeyCodes[0x020] = Input::Key::D;
	s_Data.KeyCodes[0x012] = Input::Key::E;
	s_Data.KeyCodes[0x021] = Input::Key::F;
	s_Data.KeyCodes[0x022] = Input::Key::G;
	s_Data.KeyCodes[0x023] = Input::Key::H;
	s_Data.KeyCodes[0x017] = Input::Key::I;
	s_Data.KeyCodes[0x024] = Input::Key::J;
	s_Data.KeyCodes[0x025] = Input::Key::K;
	s_Data.KeyCodes[0x026] = Input::Key::L;
	s_Data.KeyCodes[0x032] = Input::Key::M;
	s_Data.KeyCodes[0x031] = Input::Key::N;
	s_Data.KeyCodes[0x018] = Input::Key::O;
	s_Data.KeyCodes[0x019] = Input::Key::P;
	s_Data.KeyCodes[0x010] = Input::Key::Q;
	s_Data.KeyCodes[0x013] = Input::Key::R;
	s_Data.KeyCodes[0x01F] = Input::Key::S;
	s_Data.KeyCodes[0x014] = Input::Key::T;
	s_Data.KeyCodes[0x016] = Input::Key::U;
	s_Data.KeyCodes[0x02F] = Input::Key::V;
	s_Data.KeyCodes[0x011] = Input::Key::W;
	s_Data.KeyCodes[0x02D] = Input::Key::X;
	s_Data.KeyCodes[0x015] = Input::Key::Y;
	s_Data.KeyCodes[0x02C] = Input::Key::Z;

	s_Data.KeyCodes[0x028] = Input::Key::Apostrophe;
	s_Data.KeyCodes[0x02B] = Input::Key::Backslash;
	s_Data.KeyCodes[0x033] = Input::Key::Comma;
	s_Data.KeyCodes[0x00D] = Input::Key::Equal;
	s_Data.KeyCodes[0x029] = Input::Key::Grave_Accent;
	s_Data.KeyCodes[0x01A] = Input::Key::Left_Bracket;
	s_Data.KeyCodes[0x00C] = Input::Key::Minus;
	s_Data.KeyCodes[0x034] = Input::Key::Period;
	s_Data.KeyCodes[0x01B] = Input::Key::Right_Bracket;
	s_Data.KeyCodes[0x027] = Input::Key::Semicolon;
	s_Data.KeyCodes[0x035] = Input::Key::Slash;
	s_Data.KeyCodes[0x056] = Input::Key::World_2;

	s_Data.KeyCodes[0x00E] = Input::Key::Backspace;
	s_Data.KeyCodes[0x153] = Input::Key::Delete;
	s_Data.KeyCodes[0x14F] = Input::Key::End;
	s_Data.KeyCodes[0x01C] = Input::Key::Enter;
	s_Data.KeyCodes[0x001] = Input::Key::Escape;
	s_Data.KeyCodes[0x147] = Input::Key::Home;
	s_Data.KeyCodes[0x152] = Input::Key::Insert;
	s_Data.KeyCodes[0x15D] = Input::Key::Menu;
	s_Data.KeyCodes[0x151] = Input::Key::Page_Down;
	s_Data.KeyCodes[0x149] = Input::Key::Page_Up;
	s_Data.KeyCodes[0x045] = Input::Key::Pause;
	s_Data.KeyCodes[0x146] = Input::Key::Pause;
	s_Data.KeyCodes[0x039] = Input::Key::Space;
	s_Data.KeyCodes[0x00F] = Input::Key::Tab;
	s_Data.KeyCodes[0x03A] = Input::Key::Caps_Lock;
	s_Data.KeyCodes[0x145] = Input::Key::NUM_Lock;
	s_Data.KeyCodes[0x046] = Input::Key::Scroll_Lock;
	s_Data.KeyCodes[0x03B] = Input::Key::F1;
	s_Data.KeyCodes[0x03C] = Input::Key::F2;
	s_Data.KeyCodes[0x03D] = Input::Key::F3;
	s_Data.KeyCodes[0x03E] = Input::Key::F4;
	s_Data.KeyCodes[0x03F] = Input::Key::F5;
	s_Data.KeyCodes[0x040] = Input::Key::F6;
	s_Data.KeyCodes[0x041] = Input::Key::F7;
	s_Data.KeyCodes[0x042] = Input::Key::F8;
	s_Data.KeyCodes[0x043] = Input::Key::F9;
	s_Data.KeyCodes[0x044] = Input::Key::F10;
	s_Data.KeyCodes[0x057] = Input::Key::F11;
	s_Data.KeyCodes[0x058] = Input::Key::F12;
	s_Data.KeyCodes[0x064] = Input::Key::F13;
	s_Data.KeyCodes[0x065] = Input::Key::F14;
	s_Data.KeyCodes[0x066] = Input::Key::F15;
	s_Data.KeyCodes[0x067] = Input::Key::F16;
	s_Data.KeyCodes[0x068] = Input::Key::F17;
	s_Data.KeyCodes[0x069] = Input::Key::F18;
	s_Data.KeyCodes[0x06A] = Input::Key::F19;
	s_Data.KeyCodes[0x06B] = Input::Key::F20;
	s_Data.KeyCodes[0x06C] = Input::Key::F21;
	s_Data.KeyCodes[0x06D] = Input::Key::F22;
	s_Data.KeyCodes[0x06E] = Input::Key::F23;
	s_Data.KeyCodes[0x076] = Input::Key::F24;
	s_Data.KeyCodes[0x038] = Input::Key::Left_ALT;
	s_Data.KeyCodes[0x01D] = Input::Key::Left_Control;
	s_Data.KeyCodes[0x02A] = Input::Key::Left_Shift;
	s_Data.KeyCodes[0x15B] = Input::Key::Left_Super;
	s_Data.KeyCodes[0x137] = Input::Key::Print_Screen;
	s_Data.KeyCodes[0x138] = Input::Key::Right_ALT;
	s_Data.KeyCodes[0x11D] = Input::Key::Right_Control;
	s_Data.KeyCodes[0x036] = Input::Key::Right_Shift;
	s_Data.KeyCodes[0x15C] = Input::Key::Right_Super;
	s_Data.KeyCodes[0x150] = Input::Key::Down;
	s_Data.KeyCodes[0x14B] = Input::Key::Left;
	s_Data.KeyCodes[0x14D] = Input::Key::Right;
	s_Data.KeyCodes[0x148] = Input::Key::Up;

	s_Data.KeyCodes[0x052] = Input::Key::KP_0;
	s_Data.KeyCodes[0x04F] = Input::Key::KP_1;
	s_Data.KeyCodes[0x050] = Input::Key::KP_2;
	s_Data.KeyCodes[0x051] = Input::Key::KP_3;
	s_Data.KeyCodes[0x04B] = Input::Key::KP_4;
	s_Data.KeyCodes[0x04C] = Input::Key::KP_5;
	s_Data.KeyCodes[0x04D] = Input::Key::KP_6;
	s_Data.KeyCodes[0x047] = Input::Key::KP_7;
	s_Data.KeyCodes[0x048] = Input::Key::KP_8;
	s_Data.KeyCodes[0x049] = Input::Key::KP_9;
	s_Data.KeyCodes[0x04E] = Input::Key::KP_Add;
	s_Data.KeyCodes[0x053] = Input::Key::KP_Decimal;
	s_Data.KeyCodes[0x135] = Input::Key::KP_Divide;
	s_Data.KeyCodes[0x11C] = Input::Key::KP_Enter;
	s_Data.KeyCodes[0x059] = Input::Key::KP_Equal;
	s_Data.KeyCodes[0x037] = Input::Key::KP_Multiply;
	s_Data.KeyCodes[0x04A] = Input::Key::KP_Subtract;

	for (uint32_t scanCode = 0; scanCode < 512; scanCode++)
		if (static_cast<int32_t>(s_Data.KeyCodes[scanCode]) > 0)
			s_Data.ScanCodes[static_cast<int32_t>(s_Data.KeyCodes[scanCode])] = scanCode;
}

//-------------------------------------------------------------------------------------------------------------------//

//Updates key names according to the current keyboard layout
void TRAP::INTERNAL::WindowingAPI::UpdateKeyNamesWin32()
{
	std::array<BYTE, 256> state{};

	s_Data.KeyNames = {};

	for (uint32_t key = static_cast<uint32_t>(Input::Key::Space); key <= static_cast<uint32_t>(Input::Key::Menu); key++)
	{
		uint32_t virtualKey;
		std::array<WCHAR, 16> chars{};

		const int32_t scanCode = s_Data.ScanCodes[key];
		if (scanCode == -1)
			continue;

		if (key >= static_cast<uint32_t>(Input::Key::KP_0) && key <= static_cast<uint32_t>(Input::Key::KP_Add))
		{
			const std::array<uint32_t, 15> virtualKeys = {
				VK_NUMPAD0,  VK_NUMPAD1,  VK_NUMPAD2, VK_NUMPAD3,
				VK_NUMPAD4,  VK_NUMPAD5,  VK_NUMPAD6, VK_NUMPAD7,
				VK_NUMPAD8,  VK_NUMPAD9,  VK_DECIMAL, VK_DIVIDE,
				VK_MULTIPLY, VK_SUBTRACT, VK_ADD
			};

			virtualKey = virtualKeys[key - static_cast<uint32_t>(Input::Key::KP_0)];
		}
		else
			virtualKey = MapVirtualKey(scanCode, MAPVK_VSC_TO_VK);

		int32_t length = ToUnicode(virtualKey,
			scanCode,
			state.data(),
			chars.data(),
			static_cast<int32_t>(chars.size()),
			0);

		if (length == -1)
		{
			length = ToUnicode(virtualKey, scanCode, state.data(),
				chars.data(), static_cast<int32_t>(chars.size()),
				0);
		}

		if (length < 1)
			continue;

		WideCharToMultiByte(CP_UTF8, 0, chars.data(), 1,
			s_Data.KeyNames[key].data(),
			static_cast<int32_t>(s_Data.KeyNames[key].size()),
			nullptr, nullptr);
	}
}

//-------------------------------------------------------------------------------------------------------------------//

//Notifies shared code of a mouse button click event
void TRAP::INTERNAL::WindowingAPI::InputMouseClick(Ref<InternalWindow> window, Input::MouseButton button, const bool pressed)
{
	window->MouseButtons[static_cast<uint32_t>(button)] = pressed;

	if (window->Callbacks.MouseButton)
		window->Callbacks.MouseButton(window, button, pressed);
}

//-------------------------------------------------------------------------------------------------------------------//

//Notifies shared code that a window has lost or received input focus
void TRAP::INTERNAL::WindowingAPI::InputWindowFocus(Ref<InternalWindow> window, const bool focused)
{
	if (window->Callbacks.Focus)
		window->Callbacks.Focus(window, focused);

	if (!focused)
	{
		for (uint32_t key = 0; key <= static_cast<uint32_t>(Input::Key::Menu); key++)
			if (window->Keys[key] == true)
			{
				const int32_t scanCode = PlatformGetKeyScanCode(static_cast<Input::Key>(key));
				InputKey(window, static_cast<Input::Key>(key), scanCode, false);
			}

		for (uint32_t button = 0; button <= static_cast<uint32_t>(Input::MouseButton::Eight); button++)
			if (window->MouseButtons[button])
				InputMouseClick(window, static_cast<Input::MouseButton>(button), false);
	}
}

//-------------------------------------------------------------------------------------------------------------------//

//Notifies shared code of a Unicode codepoint input event
//The 'plain' parameter determines whether to emit a regular character event
void TRAP::INTERNAL::WindowingAPI::InputChar(const Ref<InternalWindow> window, const uint32_t codePoint)
{
	if (codePoint < 32 || (codePoint > 126 && codePoint < 160))
		return;

	if (window->Callbacks.Character)
		window->Callbacks.Character(window, codePoint);
}

//-------------------------------------------------------------------------------------------------------------------//

//Notifies shared code of a cursor motion event
//The position is specified in content area relative screen coordinates
void TRAP::INTERNAL::WindowingAPI::InputCursorPos(const Ref<InternalWindow> window, const double xPos, const double yPos)
{
	if (window->VirtualCursorPosX == xPos && window->VirtualCursorPosY == yPos)
		return;

	window->VirtualCursorPosX = xPos;
	window->VirtualCursorPosY = yPos;

	if (window->Callbacks.CursorPos)
		window->Callbacks.CursorPos(window, xPos, yPos);
}

//-------------------------------------------------------------------------------------------------------------------//

//Notifies shared code of a scroll event
void TRAP::INTERNAL::WindowingAPI::InputScroll(const Ref<InternalWindow> window, const double xOffset, const double yOffset)
{
	if (window->Callbacks.Scroll)
		window->Callbacks.Scroll(window, xOffset, yOffset);
}

//-------------------------------------------------------------------------------------------------------------------//

//Notifies shared code that a window framebuffer has been resized
//The size is specified in pixels
void TRAP::INTERNAL::WindowingAPI::InputFrameBufferSize(const Ref<InternalWindow> window, const int32_t width, const int32_t height)
{
	if (window->Callbacks.FBSize)
		window->Callbacks.FBSize(window, width, height);
}

//-------------------------------------------------------------------------------------------------------------------//

//Notifies shared code that a window has been resized
//The size is specified in screen coordinates
void TRAP::INTERNAL::WindowingAPI::InputWindowSize(const Ref<InternalWindow> window, const int32_t width, const int32_t height)
{
	if (window->Callbacks.Size)
		window->Callbacks.Size(window, width, height);
}

//-------------------------------------------------------------------------------------------------------------------//

//Notifies shared code that a window has moved
//The position is specified in content area relative screen coordinates
void TRAP::INTERNAL::WindowingAPI::InputWindowPos(const Ref<InternalWindow> window, const int32_t x, const int32_t y)
{
	if (window->Callbacks.Pos)
		window->Callbacks.Pos(window, x, y);
}

//-------------------------------------------------------------------------------------------------------------------//

//Notifies shared code that a window content scale has changed
//The scale is specified as the ratio between the current and default DPI
void TRAP::INTERNAL::WindowingAPI::InputWindowContentScale(const Ref<InternalWindow> window, const float xScale, const float yScale)
{
	if (window->Callbacks.Scale)
		window->Callbacks.Scale(window, xScale, yScale);
}

//-------------------------------------------------------------------------------------------------------------------//

//Notifies shared code of files or directories dropped on a window
void TRAP::INTERNAL::WindowingAPI::InputDrop(Ref<InternalWindow> window, const std::vector<std::string>& paths)
{
	if (window->Callbacks.Drop)
		window->Callbacks.Drop(window, paths);
}

//-------------------------------------------------------------------------------------------------------------------//

//Translates a Windows key to the corresponding TRAP key
TRAP::Input::Key TRAP::INTERNAL::WindowingAPI::TranslateKey(const WPARAM wParam, const LPARAM lParam)
{
	//The Ctrl keys require special handling
	if (wParam == VK_CONTROL)
	{
		MSG next;

		//Right side keys have the extended key bit set
		if (HIWORD(lParam) & KF_EXTENDED)
			return Input::Key::Right_Control;

		//HACK: Alt Gr sends Left Ctrl and then Right Alt in close sequence
		//      We only want the Right Alt message, so if the next message is
		//      Right Alt we ignore this (synthetic) Left Ctrl message
		const DWORD time = GetMessageTime();

		if (PeekMessageW(&next, nullptr, 0, 0, PM_NOREMOVE))
		{
			if (next.message == WM_KEYDOWN || next.message == WM_SYSKEYDOWN ||
				next.message == WM_KEYUP ||	next.message == WM_SYSKEYUP)
			{
				if (next.wParam == VK_MENU && (HIWORD(next.lParam) & KF_EXTENDED) && next.time == time)
				{
					//Next message is Right Alt down so discard this
					return Input::Key::Invalid;
				}
			}
		}

		return Input::Key::Left_Control;
	}

	if (wParam == VK_PROCESSKEY)
	{
		//IME notifies that keys have been filtered by setting the virtual
		//key-code to VK_PROCESSKEY
		return Input::Key::Invalid;
	}

	return s_Data.KeyCodes[HIWORD(lParam) & 0x1FF];
}

//-------------------------------------------------------------------------------------------------------------------//

//Window callback function (handles window messages)
LRESULT CALLBACK TRAP::INTERNAL::WindowingAPI::WindowProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
{
	InternalWindow* winPtr = static_cast<InternalWindow*>(GetPropW(hWnd, L"TRAP"));
	Ref<InternalWindow> window = nullptr;
	if(winPtr)
		//Hack: Convert raw pointer to a smart pointer without deleter so we can use our functions
		window = Ref<InternalWindow>(winPtr, [](InternalWindow*) {});

	if (!window)
	{
		//This is the message handling for the hidden helper window
		//and for a regular window during its initial creation

		switch (uMsg)
		{
			case WM_NCCREATE:
			{
				if (IsWindows10AnniversaryUpdateOrGreaterWin32())
					s_Data.User32.EnableNonClientDPIScaling(hWnd);

				break;
			}

			case WM_DISPLAYCHANGE:
			{
				PollMonitorsWin32();
				break;
			}

			case WM_DEVICECHANGE:
			{
				if (wParam == DBT_DEVICEARRIVAL)
				{
					DEV_BROADCAST_HDR* dbh = reinterpret_cast<DEV_BROADCAST_HDR*>(lParam);
					if (dbh && dbh->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
						Input::UpdateControllerConnectionWindows();
				}
				else if (wParam == DBT_DEVICEREMOVECOMPLETE)
				{
					DEV_BROADCAST_HDR* dbh = reinterpret_cast<DEV_BROADCAST_HDR*>(lParam);
					if (dbh && dbh->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
						Input::DetectControllerConnection();
				}

				break;
			}			
			
		default:
			break;
		}

		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}
	
	switch (uMsg)
	{
		case WM_MOUSEACTIVATE:
		{
			//HACK: Postpone cursor disabling when the window was activated by
			//      clicking a caption button
			if (HIWORD(lParam) == WM_LBUTTONDOWN)
				if (LOWORD(lParam) != HTCLIENT)
					window->FrameAction = true;

			break;
		}

		case WM_CAPTURECHANGED:
		{
			//HACK: Disable the cursor once the caption button action has been
			//      completed or cancelled
			if (lParam == 0 && window->FrameAction)
			{
				if (window->CursorMode == CursorMode::Disabled)
					DisableCursor(window);

				window->FrameAction = false;
			}

			break;
		}

		case WM_SETFOCUS:
		{
			InputWindowFocus(window, true);

			//HACK: Do not disable cursor while the user is interacting with
			//      a caption button
			if (window->FrameAction)
				break;

			if (window->CursorMode == CursorMode::Disabled)
				DisableCursor(window);

			return 0;
		}

		case WM_KILLFOCUS:
		{
			if (window->CursorMode == CursorMode::Disabled)
				EnableCursor(window);

			if (window->Monitor && !window->BorderlessFullscreen)
				PlatformMinimizeWindow(window);

			InputWindowFocus(window, false);

			return 0;
		}

		case WM_SYSCOMMAND:
		{
			switch (wParam & 0xFFF0)
			{
			case SC_SCREENSAVE:
			case SC_MONITORPOWER:
			{
				if (window->Monitor)
					//We are running in full screen mode, so disallow
					//screen saver and screen blanking
					return 0;

				break;
			}

			//User trying to access application menu using ALT?
			case SC_KEYMENU:
			{
				return 0;
			}

			default:
				break;
			}

			break;
		}

		case WM_CLOSE:
		{
			InputWindowCloseRequest(window);
			return 0;
		}

		case WM_INPUTLANGCHANGE:
		{
			UpdateKeyNamesWin32();
			break;
		}

		case WM_CHAR:
		case WM_SYSCHAR:
		case WM_UNICHAR:
		{
			if (uMsg == WM_UNICHAR && wParam == UNICODE_NOCHAR)
			{
				//WM_UNICHAR is not sent by Windows, but is sent by some
				//3rd party input method engine
				//Returning TRUE here announces support for this message
				return TRUE;
			}

			InputChar(window, static_cast<uint32_t>(wParam));

			return 0;
		}

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			const Input::Key key = TranslateKey(wParam, lParam);
			const int32_t scanCode = (HIWORD(lParam) & 0x1FF);
			const bool action = (HIWORD(lParam) & KF_UP) ? false : true;

			if (key == Input::Key::Invalid)
				break;

			if (!action && wParam == VK_SHIFT)
			{
				//HACK: Release both Shift keys on Shift up event, as when both
				//      are pressed the first release does not emit any event
				//NOTE: The other half of this is in PlatformPollEvents
				InputKey(window, Input::Key::Left_Shift, scanCode, action);
				InputKey(window, Input::Key::Right_Shift, scanCode, action);
			}
			else if (wParam == VK_SNAPSHOT)
			{
				//HACK: Key down is not reported for the Print Screen Key
				InputKey(window, key, scanCode, true);
				InputKey(window, key, scanCode, false);
			}
			else
				InputKey(window, key, scanCode, action);

			break;
		}

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_XBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_XBUTTONUP:
		{
			int32_t i;
			Input::MouseButton button;
			bool pressed;

			if (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP)
				button = Input::MouseButton::Left;
			else if (uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP)
				button = Input::MouseButton::Right;
			else if (uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONUP)
				button = Input::MouseButton::Middle;
			else if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
				button = Input::MouseButton::Four;
			else
				button = Input::MouseButton::Five;

			if (uMsg == WM_LBUTTONDOWN || uMsg == WM_RBUTTONDOWN ||
				uMsg == WM_MBUTTONDOWN || uMsg == WM_XBUTTONDOWN)
				pressed = true;
			else
				pressed = false;

			for (i = 0; i <= static_cast<uint32_t>(Input::MouseButton::Eight); i++)
				if (window->MouseButtons[i])
					break;

			if (i > static_cast<uint32_t>(Input::MouseButton::Eight))
				SetCapture(hWnd);

			InputMouseClick(window, button, pressed);

			for (i = 0; i <= static_cast<uint32_t>(Input::MouseButton::Eight); i++)
				if (window->MouseButtons[i])
					break;

			if (i > static_cast<uint32_t>(TRAP::Input::MouseButton::Eight))
				ReleaseCapture();

			if (uMsg == WM_XBUTTONDOWN || uMsg == WM_XBUTTONUP)
				return TRUE;

			return 0;
		}

		case WM_MOUSEMOVE:
		{
			const int32_t x = GET_X_LPARAM(lParam);
			const int32_t y = GET_Y_LPARAM(lParam);

			if (!window->CursorTracked)
			{
				TRACKMOUSEEVENT tme;
				ZeroMemory(&tme, sizeof(tme));
				tme.cbSize = sizeof(tme);
				tme.dwFlags = TME_LEAVE;
				tme.hwndTrack = window->Handle;
				TrackMouseEvent(&tme);

				window->CursorTracked = true;
			}

			if (window->CursorMode == CursorMode::Disabled)
			{
				const int32_t dx = x - window->LastCursorPosX;
				const int32_t dy = y - window->LastCursorPosY;

				if (s_Data.DisabledCursorWindow != window)
					break;
				if (window->RawMouseMotion)
					break;

				InputCursorPos(window, window->VirtualCursorPosX + dx, window->VirtualCursorPosY + dy);
			}
			else
				InputCursorPos(window, x, y);

			window->LastCursorPosX = x;
			window->LastCursorPosY = y;

			return 0;
		}

		case WM_INPUT:
		{
			UINT size = 0;
			const HRAWINPUT ri = reinterpret_cast<HRAWINPUT>(lParam);
			int32_t dx, dy;

			if (s_Data.DisabledCursorWindow != window)
				break;
			if (!window->RawMouseMotion)
				break;

			GetRawInputData(ri, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER));
			if (size > static_cast<UINT>(s_Data.RawInputSize))
			{
				s_Data.RawInput.clear();
				s_Data.RawInput.resize(size);
				s_Data.RawInputSize = size;
			}

			size = s_Data.RawInputSize;
			if (GetRawInputData(ri, RID_INPUT, s_Data.RawInput.data(), &size, sizeof(RAWINPUTHEADER)) == static_cast<UINT>(-1))
			{
				InputError(Error::Platform_Error, "[Win32] Failed to retrieve raw input data!");
				break;
			}

			std::vector<RAWINPUT> data = s_Data.RawInput;
			if (data[0].data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE)
			{
				dx = data[0].data.mouse.lLastX - window->LastCursorPosX;
				dy = data[0].data.mouse.lLastY - window->LastCursorPosY;
			}
			else
			{
				dx = data[0].data.mouse.lLastX;
				dy = data[0].data.mouse.lLastY;
			}

			InputCursorPos(window, window->VirtualCursorPosX + dx, window->VirtualCursorPosY + dy);

			window->LastCursorPosX += dx;
			window->LastCursorPosY += dy;

			break;
		}

		case WM_MOUSELEAVE:
		{
			window->CursorTracked = false;
			return 0;
		}

		case WM_MOUSEWHEEL:
		{
			InputScroll(window, 0.0f, static_cast<SHORT>(HIWORD(wParam)) / static_cast<double>(WHEEL_DELTA));
			return 0;
		}

		case WM_MOUSEHWHEEL:
		{
			//This message is only sent on Windows Vista and later
			//NOTE: The X-axis is inverted for consistency with X11
			InputScroll(window, -(static_cast<SHORT>(HIWORD(wParam)) / static_cast<double>(WHEEL_DELTA)), 0.0);
			return 0;
		}

		case WM_ENTERSIZEMOVE:
		case WM_ENTERMENULOOP:
		{
			if (window->FrameAction)
				break;

			//HACK: Enable the cursor while the user is moving or
			//      resizing the window or using the window menu
			if (window->CursorMode == CursorMode::Disabled)
				EnableCursor(window);

			break;
		}

		case WM_EXITSIZEMOVE:
		case WM_EXITMENULOOP:
		{
			if (window->FrameAction)
				break;

			//HACK: Disable the cursor once the user is done moving or
			//      resizing the window or using the menu
			if (window->CursorMode == CursorMode::Disabled)
				DisableCursor(window);

			break;
		}

		case WM_SIZE:
		{
			const bool minimized = wParam == SIZE_MINIMIZED;
			const bool maximized = wParam == SIZE_MAXIMIZED || (window->Maximized && wParam != SIZE_RESTORED);

			if (s_Data.DisabledCursorWindow == window)
				UpdateClipRect(window);

			InputFrameBufferSize(window, LOWORD(lParam), HIWORD(lParam));
			InputWindowSize(window, LOWORD(lParam), HIWORD(lParam));

			if (window->Monitor && window->Minimized != minimized)
			{
				if (minimized)
					ReleaseMonitor(window);
				else
				{
					AcquireMonitor(window);
					FitToMonitor(window);
				}
			}

			window->Minimized = minimized;
			window->Maximized = maximized;

			return 0;
		}

		case WM_MOVE:
		{
			if (s_Data.DisabledCursorWindow == window)
				UpdateClipRect(window);

			//NOTE: This cannot use LOWORD/HIWORD recommended by MSDN, as
			//      those macros do not handle negative window positions correctly
			InputWindowPos(window, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		}

		case WM_GETMINMAXINFO:
		{
			int32_t xOffset, yOffset;
			UINT DPI = USER_DEFAULT_SCREEN_DPI;
			MINMAXINFO* mmi = reinterpret_cast<MINMAXINFO*>(lParam);

			if (window->Monitor)
				break;

			if (IsWindows10AnniversaryUpdateOrGreaterWin32())
				DPI = s_Data.User32.GetDPIForWindow(window->Handle);

			GetFullWindowSize(GetWindowStyle(window), GetWindowExStyle(window), 0, 0, xOffset, yOffset, DPI);

			if(!window->Decorated)
			{
				MONITORINFO mi;
				const HMONITOR mh = MonitorFromWindow(window->Handle, MONITOR_DEFAULTTONEAREST);

				ZeroMemory(&mi, sizeof(mi));
				mi.cbSize = sizeof(mi);
				GetMonitorInfo(mh, &mi);

				mmi->ptMaxPosition.x = mi.rcWork.left - mi.rcMonitor.left;
				mmi->ptMaxPosition.y = mi.rcWork.top - mi.rcMonitor.top;
				mmi->ptMaxSize.x = mi.rcWork.right - mi.rcWork.left;
				mmi->ptMaxSize.y = mi.rcWork.bottom - mi.rcWork.top;
			}

			return 0;
		}

		case WM_ERASEBKGND:
		{
			return TRUE;
		}

		case WM_NCACTIVATE:
		case WM_NCPAINT:
		{
			//Prevent title bar from being drawn after restoring a minimized undecorated window
			if (!window->Decorated)
				return TRUE;
			
			break;
		}

		case WM_DWMCOMPOSITIONCHANGED:
		{
			return 0;
		}

		case WM_GETDPISCALEDSIZE:
		{
			//Adjust the window size to keep the content area size constant
			if (IsWindows10CreatorsUpdateOrGreaterWin32())
			{
				RECT source = { 0 }, target = { 0 };
				SIZE* size = reinterpret_cast<SIZE*>(lParam);

				s_Data.User32.AdjustWindowRectExForDPI(&source, GetWindowStyle(window), FALSE, GetWindowExStyle(window), s_Data.User32.GetDPIForWindow(window->Handle));
				s_Data.User32.AdjustWindowRectExForDPI(&target, GetWindowStyle(window), FALSE, GetWindowExStyle(window), LOWORD(wParam));

				size->cx += (target.right - target.left) - (source.right - source.left);
				size->cy += (target.bottom - target.top) - (source.bottom - source.top);

				return TRUE;
			}

			break;
		}

		case WM_DPICHANGED:
		{
			const float xScale = HIWORD(wParam) / static_cast<float>(USER_DEFAULT_SCREEN_DPI);
			const float yScale = LOWORD(wParam) / static_cast<float>(USER_DEFAULT_SCREEN_DPI);

			//Only apply the suggested size if the OS is new enough to have
			//sent a WM_GETDPISCALEDSIZE before this
			if (IsWindows10CreatorsUpdateOrGreaterWin32())
			{
				RECT* suggested = reinterpret_cast<RECT*>(lParam);
				::SetWindowPos(window->Handle,
					HWND_TOP,
					suggested->left,
					suggested->top,
					suggested->right - suggested->left,
					suggested->bottom - suggested->top,
					SWP_NOACTIVATE | SWP_NOZORDER);
			}

			InputWindowContentScale(window, xScale, yScale);
			break;
		}

		case WM_SETCURSOR:
		{
			if (LOWORD(lParam) == HTCLIENT)
			{
				UpdateCursorImage(window);
				return TRUE;
			}

			break;
		}

		case WM_DROPFILES:
		{
			const HDROP drop = reinterpret_cast<HDROP>(wParam);
			POINT pt;

			const uint32_t count = DragQueryFileW(drop, 0xFFFFFFFF, nullptr, 0);
			std::vector<std::string> paths(count);

			//Move the mouse to the position of the drop
			DragQueryPoint(drop, &pt);
			InputCursorPos(window, pt.x, pt.y);

			for (uint32_t i = 0; i < paths.size(); i++)
			{
				const UINT length = DragQueryFileW(drop, i, nullptr, 0);
				std::wstring buffer{};
				buffer.resize(length + 1);

				DragQueryFileW(drop, i, buffer.data(), static_cast<UINT>(buffer.size()));
				paths[i] = CreateUTF8StringFromWideStringWin32(buffer);
			}

			InputDrop(window, paths);

			DragFinish(drop);
			return 0;
		}

		default:
			break;
	}

	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//-------------------------------------------------------------------------------------------------------------------//

//Registers the TRAP window class
bool TRAP::INTERNAL::WindowingAPI::RegisterWindowClassWin32()
{
	WNDCLASSEXW wc;

	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = static_cast<WNDPROC>(WindowProc);
	wc.hInstance = GetModuleHandleW(nullptr);
	wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	wc.lpszClassName = L"TRAP060";

	//Load user-provided icon if available
	wc.hIcon = static_cast<HICON>(LoadImageW(GetModuleHandleW(nullptr),
		L"TRAP_ICON",
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED));
	if (!wc.hIcon)
	{
		//No user-provided icon found, load default icon
		wc.hIcon = static_cast<HICON>(LoadImageW(nullptr,
			IDI_APPLICATION,
			IMAGE_ICON,
			0,
			0,
			LR_DEFAULTSIZE | LR_SHARED));
	}

	if (!RegisterClassExW(&wc))
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to register window class");
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

//Unregisters the TRAP window class
void TRAP::INTERNAL::WindowingAPI::UnregisterWindowClassWin32()
{
	UnregisterClassW(L"TRAP060", GetModuleHandleW(nullptr));
}

//-------------------------------------------------------------------------------------------------------------------//

//Callback for EnumDisplayMonitors in createMonitor
BOOL CALLBACK TRAP::INTERNAL::WindowingAPI::MonitorCallback(const HMONITOR handle, HDC dc, RECT* rect, LPARAM data)
{
	MONITORINFOEXW mi;
	ZeroMemory(&mi, sizeof(mi));
	mi.cbSize = sizeof(mi);

	if (GetMonitorInfoW(handle, static_cast<MONITORINFO*>(&mi)))
	{
		const Ref<InternalMonitor> monitor = *(reinterpret_cast<Ref<InternalMonitor>*>(data));
		if (wcscmp(mi.szDevice, monitor->AdapterName.data()) == 0)
			monitor->Handle = handle;
	}

	return TRUE;
}

//-------------------------------------------------------------------------------------------------------------------//

//Create monitor from an adapter and (optionally) a display
TRAP::Ref<TRAP::INTERNAL::WindowingAPI::InternalMonitor> TRAP::INTERNAL::WindowingAPI::CreateMonitor(DISPLAY_DEVICEW* adapter, DISPLAY_DEVICEW* display)
{
	std::string name;
	DEVMODEW dm{};
	RECT rect;

	if (display)
		name = CreateUTF8StringFromWideStringWin32(display->DeviceString);
	else
		name = CreateUTF8StringFromWideStringWin32(adapter->DeviceString);
	if (name.empty())
		return nullptr;

	ZeroMemory(&dm, sizeof(dm));
	dm.dmSize = sizeof(dm);
	EnumDisplaySettingsW(adapter->DeviceName, ENUM_CURRENT_SETTINGS, &dm);

	Ref<InternalMonitor> monitor = MakeRef<InternalMonitor>();
	monitor->Name = name;

	if (adapter->StateFlags & DISPLAY_DEVICE_MODESPRUNED)
		monitor->ModesPruned = true;

	monitor->AdapterName = adapter->DeviceName;
	monitor->PublicAdapterName.resize(32);
	WideCharToMultiByte(CP_UTF8, 0,
		adapter->DeviceName, -1,
		monitor->PublicAdapterName.data(),
		static_cast<int32_t	>(monitor->PublicAdapterName.size()),
		nullptr, nullptr);

	if (display)
	{
		monitor->DisplayName = display->DeviceName;
		monitor->PublicDisplayName.resize(32);
		WideCharToMultiByte(CP_UTF8, 0,
			display->DeviceName, -1,
			monitor->PublicDisplayName.data(),
			static_cast<int32_t>(monitor->PublicDisplayName.size()),
			nullptr, nullptr);
	}

	rect.left = dm.dmPosition.x;
	rect.top = dm.dmPosition.y;
	rect.right = dm.dmPosition.x + dm.dmPelsWidth;
	rect.bottom = dm.dmPosition.y + dm.dmPelsHeight;

	EnumDisplayMonitors(nullptr, &rect, MonitorCallback, reinterpret_cast<LPARAM>(&monitor));
	return monitor;
}

//-------------------------------------------------------------------------------------------------------------------//

//Notifies shared code of a monitor connection or disconnection
void TRAP::INTERNAL::WindowingAPI::InputMonitor(Ref<InternalMonitor> monitor, const bool connected, const uint32_t placement)
{
	if (connected)
	{
		if (placement == 0)
			s_Data.Monitors.insert(s_Data.Monitors.begin(), monitor);
		else
			s_Data.Monitors.emplace_back(monitor);
	}
	else
	{
		for (Ref<InternalWindow> window = s_Data.WindowListHead; window; window = window->Next)
		{
			if (window->Monitor == monitor)
			{
				int32_t width = 0, height = 0, xOff = 0, yOff = 0, unused = 0;
				PlatformGetWindowSize(window, width, height);
				PlatformSetWindowMonitor(window, nullptr, 0, 0, width, height, 0);
				PlatformGetWindowFrameSize(window, xOff, yOff, unused, unused);
				PlatformSetWindowPos(window, xOff, yOff);
			}
		}

		for (uint32_t i = 0; i < s_Data.Monitors.size(); i++)
		{
			if (s_Data.Monitors[i] == monitor)
			{
				s_Data.Monitors.erase(s_Data.Monitors.begin() + i);
				break;
			}
		}
	}

	if (s_Data.Callbacks.Monitor)
		s_Data.Callbacks.Monitor(monitor, connected);

	if (!connected)
		if (monitor)
			monitor.reset();
}

//-------------------------------------------------------------------------------------------------------------------//

//Poll for changes in the set of connected monitors
void TRAP::INTERNAL::WindowingAPI::PollMonitorsWin32()
{
	uint32_t i;
	const uint32_t disconnectedCount = static_cast<uint32_t>(s_Data.Monitors.size());
	std::vector<Ref<InternalMonitor>> disconnected = s_Data.Monitors;
	DWORD displayIndex;
	DISPLAY_DEVICEW adapter, display;
	Ref<InternalMonitor> monitor;

	for (DWORD adapterIndex = 0; ; adapterIndex++)
	{
		uint32_t type = 1;

		ZeroMemory(&adapter, sizeof(adapter));
		adapter.cb = sizeof(adapter);

		if (!EnumDisplayDevicesW(nullptr, adapterIndex, &adapter, 0))
			break;

		if (!(adapter.StateFlags & DISPLAY_DEVICE_ACTIVE))
			continue;

		if (adapter.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
			type = 0;

		for (displayIndex = 0; ; displayIndex++)
		{
			ZeroMemory(&display, sizeof(display));
			display.cb = sizeof(display);

			if (!EnumDisplayDevicesW(adapter.DeviceName, displayIndex, &display, 0))
				break;

			if (!(display.StateFlags & DISPLAY_DEVICE_ACTIVE))
				continue;

			for (i = 0; i < disconnectedCount; i++)
			{
				if (disconnected[i] && wcscmp(disconnected[i]->DisplayName.data(), display.DeviceName) == 0)
				{
					disconnected[i] = nullptr;
					break;
				}
			}

			if (i < disconnectedCount)
				continue;

			monitor = CreateMonitor(&adapter, &display);
			if (!monitor)
				return;

			InputMonitor(monitor, true, type);

			type = 1;
		}

		//HACK: If an active adapter does not have any display devices
		//      (as sometimes happens), add it directly as a monitor
		if (displayIndex == 0)
		{
			for (i = 0; i < disconnectedCount; i++)
			{
				if (disconnected[i] && wcscmp(disconnected[i]->AdapterName.data(), adapter.DeviceName) == 0)
				{
					disconnected[i] = nullptr;
					break;
				}
			}

			if (i < disconnectedCount)
				continue;

			monitor = CreateMonitor(&adapter, nullptr);
			if (!monitor)
				return;

			InputMonitor(monitor, true, type);
		}
	}

	for (i = 0; i < disconnectedCount; i++)
	{
		if (disconnected[i])
			InputMonitor(disconnected[i], false, 0);
	}
}

//-------------------------------------------------------------------------------------------------------------------//

//Make the specified window and its video mode active on its monitor
void TRAP::INTERNAL::WindowingAPI::AcquireMonitor(Ref<InternalWindow> window)
{
	if (!s_Data.AcquiredMonitorCount)
	{
		SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);

		//HACK: When mouse trails are enabled the cursor becomes invisible when
		//      the OpenGL ICD switches to page flipping
		if (IsWindowsXPOrGreaterWin32())
		{
			SystemParametersInfo(SPI_GETMOUSETRAILS, 0, &s_Data.MouseTrailSize, 0);
			SystemParametersInfo(SPI_SETMOUSETRAILS, 0, nullptr, 0);
		}
	}

	if (!window->Monitor->Window)
		s_Data.AcquiredMonitorCount++;

	SetVideoModeWin32(window->Monitor, window->VideoMode);
	window->Monitor->Window = window;
}

//-------------------------------------------------------------------------------------------------------------------//

//Make the specified window active on its monitor
void TRAP::INTERNAL::WindowingAPI::AcquireMonitorBorderless(Ref<InternalWindow> window)
{
	if(!s_Data.AcquiredMonitorCount)
	{
		SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);

		//HACK: When mouse trails are enabled the cursor becomes invisible when
		//      the OpenGL ICD switches to page flipping
		if (IsWindowsXPOrGreaterWin32())
		{
			SystemParametersInfo(SPI_GETMOUSETRAILS, 0, &s_Data.MouseTrailSize, 0);
			SystemParametersInfo(SPI_SETMOUSETRAILS, 0, nullptr, 0);
		}
	}

	if (!window->Monitor->Window)
		s_Data.AcquiredMonitorCount++;

	window->Monitor->Window = window;
}

//-------------------------------------------------------------------------------------------------------------------//

//Remove the window and restore the original video mode
void TRAP::INTERNAL::WindowingAPI::ReleaseMonitor(Ref<InternalWindow> window)
{
	if (window->Monitor->Window != window)
		return;

	s_Data.AcquiredMonitorCount--;
	if (!s_Data.AcquiredMonitorCount)
	{
		SetThreadExecutionState(ES_CONTINUOUS);

		//HACK: Restore mouse trail length saved in acquireMonitor
		if (IsWindowsXPOrGreaterWin32())
			SystemParametersInfo(SPI_SETMOUSETRAILS, s_Data.MouseTrailSize, nullptr, 0);
	}

	window->Monitor->Window = nullptr;

	if (window->Monitor->ModeChanged)
	{
		ChangeDisplaySettingsExW(window->Monitor->AdapterName.data(), nullptr, nullptr, CDS_FULLSCREEN, nullptr);
		window->Monitor->ModeChanged = false;
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::FitToMonitor(const Ref<InternalWindow> window)
{
	MONITORINFO mi = { sizeof(mi) };
	GetMonitorInfo(window->Monitor->Handle, &mi);
	::SetWindowPos(window->Handle, HWND_TOPMOST,
		mi.rcMonitor.left,
		mi.rcMonitor.top,
		mi.rcMonitor.right - mi.rcMonitor.left,
		mi.rcMonitor.bottom - mi.rcMonitor.top,
		SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
}

//-------------------------------------------------------------------------------------------------------------------//

//Lexically compare video modes, used by qsort
int32_t TRAP::INTERNAL::WindowingAPI::CompareVideoModes(const void* fp, const void* sp)
{
	const VideoMode* fm = static_cast<const VideoMode*>(fp);
	const VideoMode* sm = static_cast<const VideoMode*>(sp);
	const int32_t fbpp = fm->RedBits + fm->GreenBits + fm->BlueBits;
	const int32_t sbpp = sm->RedBits + sm->GreenBits + sm->BlueBits;
	const int32_t farea = fm->Width * fm->Height;
	const int32_t sarea = sm->Width * sm->Height;

	//First sort on color bits per pixel
	if (fbpp != sbpp)
		return fbpp - sbpp;

	//Then sort on screen area
	if (farea != sarea)
		return farea - sarea;

	//Then sort on width
	if (fm->Width != sm->Width)
		return fm->Width - sm->Width;

	//Lastly sort on refresh rate
	return fm->RefreshRate - sm->RefreshRate;
}

//-------------------------------------------------------------------------------------------------------------------//

//Retrieves the available modes for the specified monitor
bool TRAP::INTERNAL::WindowingAPI::RefreshVideoModes(Ref<InternalMonitor> monitor)
{
	if (!monitor->Modes.empty())
		return true;

	std::vector<VideoMode> modes = PlatformGetVideoModes(monitor);
	if (modes.empty())
		return false;

	std::qsort(modes.data(), modes.size(), sizeof(VideoMode), CompareVideoModes);

	monitor->Modes = {};
	monitor->Modes = modes;

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

//Chooses the video mode most closely matching the desired one
TRAP::INTERNAL::WindowingAPI::VideoMode* TRAP::INTERNAL::WindowingAPI::ChooseVideoMode(Ref<InternalMonitor> monitor, const VideoMode& desired)
{
	uint32_t leastSizeDiff = UINT_MAX;
	uint32_t rateDiff, leastRateDiff = UINT_MAX;
	uint32_t leastColorDiff = UINT_MAX;
	VideoMode* closest = nullptr;

	if (!RefreshVideoModes(monitor))
		return nullptr;

	for (uint32_t i = 0; i < monitor->Modes.size(); i++)
	{
		VideoMode* current = &monitor->Modes[i];

		uint32_t colorDiff = 0;

		if (desired.RedBits != -1)
			colorDiff += abs(current->RedBits - desired.RedBits);
		if (desired.GreenBits != -1)
			colorDiff += abs(current->GreenBits - desired.GreenBits);
		if (desired.BlueBits != -1)
			colorDiff += abs(current->BlueBits - desired.BlueBits);

		const uint32_t sizeDiff = abs((current->Width - desired.Width) *
			(current->Width - desired.Width) +
			(current->Height - desired.Height) *
			(current->Height - desired.Height));

		if (desired.RefreshRate != -1)
			rateDiff = abs(current->RefreshRate - desired.RefreshRate);
		else
			rateDiff = UINT_MAX - current->RefreshRate;

		if ((colorDiff < leastColorDiff) ||
			(colorDiff == leastColorDiff && sizeDiff < leastSizeDiff) ||
			(colorDiff == leastColorDiff && sizeDiff == leastSizeDiff && rateDiff < leastRateDiff))
		{
			closest = current;
			leastSizeDiff = sizeDiff;
			leastRateDiff = rateDiff;
			leastColorDiff = colorDiff;
		}
	}

	return closest;
}

//-------------------------------------------------------------------------------------------------------------------//

//Change the current video mode
void TRAP::INTERNAL::WindowingAPI::SetVideoModeWin32(Ref<InternalMonitor> monitor, const VideoMode& desired)
{
	VideoMode current;
	const VideoMode* best = nullptr;
	DEVMODEW dm;
	LONG result = 0;

	best = ChooseVideoMode(monitor, desired);
	PlatformGetVideoMode(monitor, current);
	/*if (!CompareVideoModes(&current, best)) //TODO Only on Borderless?
		return;*/

	ZeroMemory(&dm, sizeof(dm));
	dm.dmSize = sizeof(dm);
	dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL |
		DM_DISPLAYFREQUENCY;
	dm.dmPelsWidth = best->Width;
	dm.dmPelsHeight = best->Height;
	dm.dmBitsPerPel = best->RedBits + best->GreenBits + best->BlueBits;
	dm.dmDisplayFrequency = best->RefreshRate;

	if (dm.dmBitsPerPel < 15 || dm.dmBitsPerPel >= 24)
		dm.dmBitsPerPel = 32;

	result = ChangeDisplaySettingsExW(monitor->AdapterName.data(),
		&dm,
		nullptr,
		CDS_FULLSCREEN,
		nullptr);
	if (result == DISP_CHANGE_SUCCESSFUL)
		monitor->ModeChanged = true;
	else
	{
		std::string description = "Unknown error";

		if (result == DISP_CHANGE_BADDUALVIEW)
			description = "The system uses DualView";
		else if (result == DISP_CHANGE_BADFLAGS)
			description = "Invalid flags";
		else if (result == DISP_CHANGE_BADMODE)
			description = "Graphics mode not supported";
		else if (result == DISP_CHANGE_BADPARAM)
			description = "Invalid parameter";
		else if (result == DISP_CHANGE_FAILED)
			description = "Graphics mode failed";
		else if (result == DISP_CHANGE_NOTUPDATED)
			description = "Failed to write to registry";
		else if (result == DISP_CHANGE_RESTART)
			description = "Computer restart required";

		InputError(Error::Platform_Error, "[Win32] Failed to set video mode: " + description);
	}
}


//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::GetMonitorContentScaleWin32(const HMONITOR handle, float& xScale, float& yScale)
{
	UINT xDPI = 0, yDPI = 0;

	if (IsWindows8Point1OrGreaterWin32())
		s_Data.SHCore.GetDPIForMonitor(handle, Monitor_DPI_Type::MDT_Effective_DPI, &xDPI, &yDPI);
	else
	{
		const HDC dc = GetDC(nullptr);
		xDPI = GetDeviceCaps(dc, LOGPIXELSX);
		yDPI = GetDeviceCaps(dc, LOGPIXELSY);
		ReleaseDC(nullptr, dc);
	}

	xScale = xDPI / static_cast<float>(USER_DEFAULT_SCREEN_DPI);
	yScale = yDPI / static_cast<float>(USER_DEFAULT_SCREEN_DPI);
}

//-------------------------------------------------------------------------------------------------------------------//

//Splits a color depth into red, green and blue bit depths
void TRAP::INTERNAL::WindowingAPI::SplitBPP(int32_t bpp, int32_t& red, int32_t& green, int32_t& blue)
{
	//We assume that by 32 the user really meant 24
	if (bpp == 32)
		bpp = 24;

	//Convert "bits per pixel" to red, green & blue sizes

	red = green = blue = bpp / 3;
	const int32_t delta = bpp - (red * 3);
	if (delta >= 1)
		green = green + 1;

	if (delta == 2)
		red = red + 1;
}

//-------------------------------------------------------------------------------------------------------------------//

//Returns the window style for the specified window
DWORD TRAP::INTERNAL::WindowingAPI::GetWindowStyle(const Ref<InternalWindow> window)
{
	DWORD style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (window->Monitor)
		style |= WS_POPUP;
	else
	{
		style |= WS_SYSMENU | WS_MINIMIZEBOX;

		if (window->Decorated)
		{
			style |= WS_CAPTION;

			if (window->Resizable)
				style |= WS_MAXIMIZEBOX | WS_THICKFRAME;
		}
		else
			style |= WS_POPUP;
	}

	return style;
}

//-------------------------------------------------------------------------------------------------------------------//

//Returns the extended window style for the specified window
DWORD TRAP::INTERNAL::WindowingAPI::GetWindowExStyle(const Ref<InternalWindow> window)
{
	DWORD style = WS_EX_APPWINDOW;

	if (window->Monitor)
		style |= WS_EX_TOPMOST;

	return style;
}

//-------------------------------------------------------------------------------------------------------------------//

//Creates the TRAP window
int32_t TRAP::INTERNAL::WindowingAPI::CreateNativeWindow(Ref<InternalWindow>& window,
	                                                     const WindowConfig& WNDConfig,
	                                                     const FrameBufferConfig& FBConfig)
{
	int32_t xPos, yPos, fullWidth, fullHeight;
	DWORD style = GetWindowStyle(window);
	const DWORD exStyle = GetWindowExStyle(window);

	if (window->Monitor)
	{
		VideoMode mode;

		//NOTE: This window placement is temporary and approximate, as the
		//      correct position and size cannot be known until the monitor
		//      video mode has been picked in SetVideoModeWin32
		PlatformGetMonitorPos(window->Monitor, xPos, yPos);
		PlatformGetVideoMode(window->Monitor, mode);
		fullWidth = mode.Width;
		fullHeight = mode.Height;
	}
	else
	{
		xPos = CW_USEDEFAULT;
		yPos = CW_USEDEFAULT;

		window->Maximized = WNDConfig.Maximized;
		if (WNDConfig.Maximized)
			style |= WS_MAXIMIZE;

		GetFullWindowSize(style, exStyle,
			WNDConfig.Width, WNDConfig.Height,
			fullWidth, fullHeight,
			USER_DEFAULT_SCREEN_DPI);
	}

	std::wstring wideTitle = CreateWideStringFromUTF8StringWin32(WNDConfig.Title);
	if (wideTitle.empty())
		return false;

	window->Handle = CreateWindowExW(exStyle,
		L"TRAP060",
		wideTitle.data(),
		style,
		xPos, yPos,
		fullWidth, fullHeight,
		nullptr, //No parent window
		nullptr, //No window menu
		GetModuleHandleW(nullptr),
		nullptr);

	if (!window->Handle)
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to create window");
		return false;
	}

	SetPropW(window->Handle, L"TRAP", static_cast<void*>(window.get()));

	if (IsWindows7OrGreaterWin32())
	{
		s_Data.User32.ChangeWindowMessageFilterEx(window->Handle,
			WM_DROPFILES, MSGFLT_ALLOW, nullptr);
		s_Data.User32.ChangeWindowMessageFilterEx(window->Handle,
			WM_COPYDATA, MSGFLT_ALLOW, nullptr);
		s_Data.User32.ChangeWindowMessageFilterEx(window->Handle,
			WM_COPYGLOBALDATA, MSGFLT_ALLOW, nullptr);
	}

	//Adjust window rect to account for DPI scaling of the window frame and
	//(if enabled) DPI scaling of the content area
	//This cannot be done until we know what monitor the window was placed on
	if (!window->Monitor)
	{
		RECT rect = { 0, 0, static_cast<LONG>(WNDConfig.Width), static_cast<LONG>(WNDConfig.Height) };
		WINDOWPLACEMENT wp = { sizeof(wp) };

		ClientToScreen(window->Handle, reinterpret_cast<POINT*>(&rect.left));
		ClientToScreen(window->Handle, reinterpret_cast<POINT*>(&rect.right));

		if (IsWindows10AnniversaryUpdateOrGreaterWin32())
		{
			s_Data.User32.AdjustWindowRectExForDPI(&rect, style, FALSE, exStyle,
				s_Data.User32.GetDPIForWindow(window->Handle));
		}
		else
			AdjustWindowRectEx(&rect, style, FALSE, exStyle);

		//Only update the restored window rect as the window may be maximized
		GetWindowPlacement(window->Handle, &wp);
		wp.rcNormalPosition = rect;
		wp.showCmd = SW_HIDE;
		SetWindowPlacement(window->Handle, &wp);
	}

	DragAcceptFiles(window->Handle, TRUE);

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::INTERNAL::WindowingAPI::CreateHelperWindow()
{
	MSG msg;

	s_Data.HelperWindowHandle = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW,
		L"TRAP060",
		L"TRAP Message Window",
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		0, 0, 1, 1,
		nullptr, nullptr,
		GetModuleHandleW(nullptr),
		nullptr);

	if (!s_Data.HelperWindowHandle)
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to create helper window");
		return false;
	}

	//HACK: The command to the first ShowWindow call is ignored if the parent
	//      process passed along a STARTUPINFO, so clear that with a no-op call
	ShowWindow(s_Data.HelperWindowHandle, SW_HIDE);

	//Register for HID device notifications
	{
		DEV_BROADCAST_DEVICEINTERFACE_W dbi;
		ZeroMemory(&dbi, sizeof(dbi));
		dbi.dbcc_size = sizeof(dbi);
		dbi.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
		dbi.dbcc_classguid = { 0x4d1e55b2,0xf16f,0x11cf,{0x88,0xcb,0x00,0x11,0x11,0x00,0x00,0x30} };

		s_Data.DeviceNotificationHandle =
			RegisterDeviceNotificationW(s_Data.HelperWindowHandle,
				reinterpret_cast<DEV_BROADCAST_HDR*>(&dbi),
				DEVICE_NOTIFY_WINDOW_HANDLE);
	}

	while (PeekMessageW(&msg, s_Data.HelperWindowHandle, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

//Translate content area size to full window size according to styles and DPI
void TRAP::INTERNAL::WindowingAPI::GetFullWindowSize(const DWORD style, const DWORD exStyle,
	const int32_t contentWidth, const int32_t contentHeight,
	int32_t& fullWidth, int32_t& fullHeight,
	const UINT dpi)
{
	RECT rect = { 0, 0, contentWidth, contentHeight };

	if (IsWindows10AnniversaryUpdateOrGreaterWin32())
		s_Data.User32.AdjustWindowRectExForDPI(&rect, style, FALSE, exStyle, dpi);
	else
		AdjustWindowRectEx(&rect, style, FALSE, exStyle);

	fullWidth = rect.right - rect.left;
	fullHeight = rect.bottom - rect.top;
}

//-------------------------------------------------------------------------------------------------------------------//

//Initialize WGL
bool TRAP::INTERNAL::WindowingAPI::InitWGL()
{
	PIXELFORMATDESCRIPTOR pfd;

	if (s_Data.WGL.Instance)
		return true;

	s_Data.WGL.Instance = LoadLibraryA("opengl32.dll");
	if (!s_Data.WGL.Instance)
	{
		InputErrorWin32(Error::Platform_Error, "[WGL] Failed to load opengl32.dll");
		return false;
	}

	s_Data.WGL.CreateContext = reinterpret_cast<PFN_WGLCreateContext>(::GetProcAddress(s_Data.WGL.Instance, "wglCreateContext"));
	s_Data.WGL.DeleteContext = reinterpret_cast<PFN_WGLDeleteContext>(::GetProcAddress(s_Data.WGL.Instance, "wglDeleteContext"));
	s_Data.WGL.GetProcAddress = reinterpret_cast<PFN_WGLGetProcAddress>(::GetProcAddress(s_Data.WGL.Instance, "wglGetProcAddress"));
	s_Data.WGL.GetCurrentDC = reinterpret_cast<PFN_WGLGetCurrentDC>(::GetProcAddress(s_Data.WGL.Instance, "wglGetCurrentDC"));
	s_Data.WGL.GetCurrentContext = reinterpret_cast<PFN_WGLGetCurrentContext>(::GetProcAddress(s_Data.WGL.Instance, "wglGetCurrentContext"));
	s_Data.WGL.MakeCurrent = reinterpret_cast<PFN_WGLMakeCurrent>(::GetProcAddress(s_Data.WGL.Instance, "wglMakeCurrent"));
	s_Data.WGL.ShareLists = reinterpret_cast<PFN_WGLShareLists>(::GetProcAddress(s_Data.WGL.Instance, "wglShareLists"));

	//NOTE: A dummy context has to be created for opengl32.dll to load the
	//      OpenGL ICD, from which we can then query WGL extensions
	//NOTE: This code will accept the Microsoft GDI ICD; accelerated context
	//      creation failure occurs during manual pixel format enumeration

	const HDC dc = GetDC(s_Data.HelperWindowHandle);

	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;

	if (!SetPixelFormat(dc, ::ChoosePixelFormat(dc, &pfd), &pfd))
	{
		InputErrorWin32(Error::Platform_Error, "[WGL] Failed to set pixel format for dummy context");
		ReleaseDC(s_Data.HelperWindowHandle, dc);
		return false;
	}

	const HGLRC rc = s_Data.WGL.CreateContext(dc);
	if (!rc)
	{
		InputErrorWin32(Error::Platform_Error, "[WGL] Failed to create dummy context");
		return false;
	}

	const HDC pdc = s_Data.WGL.GetCurrentDC();
	const HGLRC prc = s_Data.WGL.GetCurrentContext();

	if (!s_Data.WGL.MakeCurrent(dc, rc))
	{
		InputErrorWin32(Error::Platform_Error, "[WGL] Failed to make dummy context current");
		s_Data.WGL.MakeCurrent(pdc, prc);
		s_Data.WGL.DeleteContext(rc);
		return false;
	}

	//NOTE: Functions must be loaded first as they're needed to retrieve the
	//      extension string that tells us whether the functions are supported
	s_Data.WGL.GetExtensionsStringEXT = reinterpret_cast<PFNWGLGETEXTENSIONSSTRINGEXTPROC>(s_Data.WGL.GetProcAddress("wglGetExtensionsStringEXT"));
	s_Data.WGL.GetExtensionsStringARB = reinterpret_cast<PFNWGLGETEXTENSIONSSTRINGARBPROC>(s_Data.WGL.GetProcAddress("wglGetExtensionsStringARB"));
	s_Data.WGL.CreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(s_Data.WGL.GetProcAddress("wglCreateContextAttribsARB"));
	s_Data.WGL.SwapIntervalEXT = reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(s_Data.WGL.GetProcAddress("wglSwapIntervalEXT"));
	s_Data.WGL.GetPixelFormatAttribivARB = reinterpret_cast<PFNWGLGETPIXELFORMATATTRIBIVARBPROC>(s_Data.WGL.GetProcAddress("wglGetPixelFormatAttribivARB"));

	//NOTE: WGL_ARB_extensions_string and WGL_EXT_extensions_string are not
	//      checked below as we are already using them
	s_Data.WGL.ARB_multisample =
		ExtensionSupportedWGL("WGL_ARB_multisample");
	s_Data.WGL.ARB_framebuffer_sRGB =
		ExtensionSupportedWGL("WGL_ARB_framebuffer_sRGB");
	s_Data.WGL.EXT_framebuffer_sRGB =
		ExtensionSupportedWGL("WGL_EXT_framebuffer_sRGB");
	s_Data.WGL.ARB_create_context =
		ExtensionSupportedWGL("WGL_ARB_create_context");
	s_Data.WGL.ARB_create_context_profile =
		ExtensionSupportedWGL("WGL_ARB_create_context_profile");
	s_Data.WGL.EXT_swap_control =
		ExtensionSupportedWGL("WGL_EXT_swap_control");
	s_Data.WGL.ARB_pixel_format =
		ExtensionSupportedWGL("WGL_ARB_pixel_format");
	s_Data.WGL.ARB_context_flush_control =
		ExtensionSupportedWGL("WGL_ARB_context_flush_control");

	s_Data.WGL.MakeCurrent(pdc, prc);
	s_Data.WGL.DeleteContext(rc);
	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

//Shutdown WGL
void TRAP::INTERNAL::WindowingAPI::ShutdownWGL()
{
	if (s_Data.WGL.Instance)
		FreeLibrary(s_Data.WGL.Instance);
}

//-------------------------------------------------------------------------------------------------------------------//

//Create the OpenGL context
bool TRAP::INTERNAL::WindowingAPI::CreateContextWGL(const Ref<InternalWindow>& window,
	                                                const ContextConfig& CTXConfig,
	                                                const FrameBufferConfig& FBConfig)
{
	std::vector<int32_t> attribs{};
	PIXELFORMATDESCRIPTOR pfd{};
	HGLRC share = nullptr;

	if (CTXConfig.Share)
		share = CTXConfig.Share->Context.Handle;

	window->Context.DC = GetDC(window->Handle);
	if (!window->Context.DC)
	{
		InputError(Error::Platform_Error, "[WGL] Failed to retrieve DC for window");
		return false;
	}

	const int32_t pixelFormat = WindowingAPI::ChoosePixelFormat(window, CTXConfig, FBConfig);
	if (!pixelFormat)
		return false;

	if (!DescribePixelFormat(window->Context.DC,
		pixelFormat, sizeof(pfd), &pfd))
	{
		InputErrorWin32(Error::Platform_Error, "[WGL] Failed to retrieve PFD for selected pixel format");
		return false;
	}

	if (!SetPixelFormat(window->Context.DC, pixelFormat, &pfd))
	{
		InputErrorWin32(Error::Platform_Error, "[WGL] Failed to set selected pixel format");
		return false;
	}

	if (CTXConfig.Client == ContextAPI::OpenGL)
	{
		if (!s_Data.WGL.ARB_create_context)
		{
			InputError(Error::Version_Unavailable, "[WGL] A forward compatible OpenGL context requested but WGL_ARB_create_context is unavailable");
			return false;
		}

		if (!s_Data.WGL.ARB_create_context_profile)
		{
			InputError(Error::Version_Unavailable, "[WGL] OpenGL profile requested but WGL_ARB_create_context_profile is unavailable");
			return false;
		}
	}

	if (s_Data.WGL.ARB_create_context)
	{
		int32_t mask = 0, flags = 0;

		if (CTXConfig.Client == ContextAPI::OpenGL)
		{
			flags |= WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;

			mask |= WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
		}

		attribs.emplace_back(WGL_CONTEXT_MAJOR_VERSION_ARB);
		attribs.emplace_back(4);
		attribs.emplace_back(WGL_CONTEXT_MINOR_VERSION_ARB);
		attribs.emplace_back(6);

		if (flags)
		{
			attribs.emplace_back(WGL_CONTEXT_FLAGS_ARB);
			attribs.emplace_back(flags);
		}

		if (mask)
		{
			attribs.emplace_back(WGL_CONTEXT_PROFILE_MASK_ARB);
			attribs.emplace_back(mask);
		}

		attribs.emplace_back(0);
		attribs.emplace_back(0);

		window->Context.Handle =
			s_Data.WGL.CreateContextAttribsARB(window->Context.DC, share, attribs.data());
		if (!window->Context.Handle)
		{
			const DWORD error = GetLastError();

			if (error == (0xc0070000 | ERROR_INVALID_VERSION_ARB))
			{
				if (CTXConfig.Client == ContextAPI::OpenGL)
					InputError(Error::Version_Unavailable, "[WGL] Driver does not support OpenGL version 4.6");
			}
			else if (error == (0xc0070000 | ERROR_INVALID_PROFILE_ARB))
				InputError(Error::Version_Unavailable, "[WGL] Driver does not support the requested OpenGL profile");
			else if (error == (0xc0070000 | ERROR_INCOMPATIBLE_DEVICE_CONTEXTS_ARB))
				InputError(Error::Invalid_Value, "[WGL] The share context is not compatible with the requested context");
			else
			{
				if (CTXConfig.Client == ContextAPI::OpenGL)
					InputError(Error::Version_Unavailable, "[WGL] Failed to create OpenGL context");
			}

			return false;
		}
	}
	else
	{
		window->Context.Handle = s_Data.WGL.CreateContext(window->Context.DC);
		if (!window->Context.Handle)
		{
			InputErrorWin32(Error::Version_Unavailable, "[WGL] Failed to create OpenGL context");
			return false;
		}

		if (share)
		{
			if (!s_Data.WGL.ShareLists(share, window->Context.Handle))
			{
				InputErrorWin32(Error::Platform_Error, "[WGL] Failed to enable sharing with specified OpenGL context");
				return false;
			}
		}
	}

	window->Context.MakeCurrent = MakeContextCurrentWGL;
	window->Context.SwapBuffers = SwapBuffersWGL;
	window->Context.SwapInterval = SwapIntervalWGL;
	window->Context.ExtensionSupported = ExtensionSupportedWGL;
	window->Context.GetProcAddress = GetProcAddressWGL;
	window->Context.Destroy = DestroyContextWGL;

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::DestroyContextWGL(const Ref<InternalWindow>& window)
{
	if (window->Context.Handle)
	{
		s_Data.WGL.DeleteContext(window->Context.Handle);
		window->Context.Handle = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::MakeContextCurrentWGL(const Ref<InternalWindow> window)
{
	if (window)
	{
		if (s_Data.WGL.MakeCurrent(window->Context.DC, window->Context.Handle))
			PlatformSetTLS(s_Data.ContextSlot, static_cast<void*>(window.get()));
		else
		{
			InputErrorWin32(Error::Platform_Error, "[WGL] Failed to make context current");
			PlatformSetTLS(s_Data.ContextSlot, nullptr);
		}
	}
	else
	{
		if (!s_Data.WGL.MakeCurrent(nullptr, nullptr))
			InputErrorWin32(Error::Platform_Error, "[WGL] Failed to clear current context");

		PlatformSetTLS(s_Data.ContextSlot, nullptr);
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::SwapBuffersWGL(const Ref<InternalWindow>& window)
{
	if (!window->Monitor)
	{
		if (IsWindowsVistaOrGreaterWin32())
		{
			//DWM Composition is always enabled on Win8+
			BOOL enabled = IsWindows8OrGreaterWin32();

			//HACK: Use DwmFlush when desktop composition is enabled
			if (enabled ||
				(SUCCEEDED(s_Data.DWMAPI_.IsCompositionEnabled(&enabled)) && enabled))
			{
				int32_t count = Math::Abs(window->Context.Interval);
				while (count--)
					s_Data.DWMAPI_.Flush();
			}
		}
	}

	::SwapBuffers(window->Context.DC);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::SwapIntervalWGL(int32_t interval)
{
	const auto winPtr = static_cast<InternalWindow*>(PlatformGetTLS(s_Data.ContextSlot));
	const Ref<InternalWindow> window = Ref<InternalWindow>(winPtr, [](InternalWindow*) {});

	window->Context.Interval = interval;

	if (!window->Monitor)
	{
		if (IsWindowsVistaOrGreaterWin32())
		{
			//DWM Composition is always enabled on Win8+
			BOOL enabled = IsWindows8OrGreaterWin32();

			//HACK: Disable WGL swap interval when desktop composition is enabled to
			//      avoid interfering with DWM vsync
			if (enabled ||
				(SUCCEEDED(s_Data.DWMAPI_.IsCompositionEnabled(&enabled)) && enabled))
				interval = 0;
		}
	}

	if (s_Data.WGL.EXT_swap_control)
		s_Data.WGL.SwapIntervalEXT(interval);
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::INTERNAL::WindowingAPI::GLProcess TRAP::INTERNAL::WindowingAPI::GetProcAddressWGL(const char* procName)
{
	const GLProcess proc = reinterpret_cast<GLProcess>(s_Data.WGL.GetProcAddress(procName));
	if (proc)
		return proc;

	return reinterpret_cast<GLProcess>(::GetProcAddress(s_Data.WGL.Instance, procName));
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::INTERNAL::WindowingAPI::ExtensionSupportedWGL(const char* extension)
{
	const char* extensions = nullptr;

	if (s_Data.WGL.GetExtensionsStringARB)
		extensions = s_Data.WGL.GetExtensionsStringARB(s_Data.WGL.GetCurrentDC());
	else if (s_Data.WGL.GetExtensionsStringEXT)
		extensions = s_Data.WGL.GetExtensionsStringEXT();

	if (!extensions)
		return false;

	return StringInExtensionString(extension, extensions);
}

//-------------------------------------------------------------------------------------------------------------------//

//Searches an extension string for the specified extension
bool TRAP::INTERNAL::WindowingAPI::StringInExtensionString(const char* string, const char* extensions)
{
	const char* start = extensions;

	for (;;)
	{
		const char* where = strstr(start, string);
		if (!where)
			return false;

		const char* terminator = where + strlen(string);
		if (where == start || *(where - 1) == ' ')
		{
			if (*terminator == ' ' || *terminator == '\0')
				break;
		}

		start = terminator;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

//Return the value corresponding to the specified attribute
int32_t TRAP::INTERNAL::WindowingAPI::FindPixelFormatAttribValue(const std::vector<int32_t>& attribs,
	                                                             const std::vector<int32_t>& values,
	                                                             const int32_t attrib)
{
	for (uint32_t i = 0; i < attribs.size(); i++)
	{
		if (attribs[i] == attrib)
			return values[i];
	}

	InputErrorWin32(Error::Platform_Error, "[WGL] Unknown pixel format attribute requested");
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------//

//Chooses the framebuffer config that best matches the desired one
const TRAP::INTERNAL::WindowingAPI::FrameBufferConfig* TRAP::INTERNAL::WindowingAPI::ChooseFBConfig(const FrameBufferConfig& desired,
	                                                                                                const std::vector<FrameBufferConfig>& alternatives)
{
	uint32_t missing, leastMissing = UINT_MAX;
	uint32_t colorDiff, leastColorDiff = UINT_MAX;
	uint32_t extraDiff, leastExtraDiff = UINT_MAX;
	const FrameBufferConfig* closest = nullptr;

	for (uint32_t i = 0; i < alternatives.size(); i++)
	{
		const FrameBufferConfig* current = &alternatives[i];

		if (desired.Stereo != current->Stereo)
			//Stereo is a hard constraint
			continue;

		if (desired.DoubleBuffer != current->DoubleBuffer)
			//Double buffering is a hard constraint
			continue;

			//Count number of missing buffers
		{
			missing = 0;

			if (desired.AlphaBits > 0 && current->AlphaBits == 0)
				missing++;

			if (desired.DepthBits > 0 && current->DepthBits == 0)
				missing++;

			if (desired.StencilBits > 0 && current->StencilBits == 0)
				missing++;

			if (desired.AuxBuffers > 0 && current->AuxBuffers < desired.AuxBuffers)
				missing += desired.AuxBuffers - current->AuxBuffers;
			
			if (desired.Samples > 0 && current->Samples == 0)
			{
				//Technically, several multisampling buffers could be
				//involved, but that's a lower level implementation detail and
				//not important to us here, so we count them as one
				missing++;
			}

			if (desired.Transparent != current->Transparent)
				missing++;
		}

		//These polynomials make many small channel size differences matter
		//less than one large channel size difference

		//Calculate color channel size difference value
		{
			colorDiff = 0;

			if (desired.RedBits != -1)
			{
				colorDiff += (desired.RedBits - current->RedBits) *
					         (desired.RedBits - current->RedBits);
			}

			if (desired.GreenBits != -1)
			{
				colorDiff += (desired.GreenBits - current->GreenBits) *
					         (desired.GreenBits - current->GreenBits);
			}

			if (desired.BlueBits != -1)
			{
				colorDiff += (desired.BlueBits - current->BlueBits) *
					         (desired.BlueBits - current->BlueBits);
			}
		}

		//Calculate non-color channel size difference value
		{
			extraDiff = 0;

			if (desired.AlphaBits != -1)
			{
				extraDiff += (desired.AlphaBits - current->AlphaBits) *
					         (desired.AlphaBits - current->AlphaBits);
			}

			if (desired.DepthBits != -1)
			{
				extraDiff += (desired.DepthBits - current->DepthBits) *
					         (desired.DepthBits - current->DepthBits);
			}

			if (desired.StencilBits != -1)
			{
				extraDiff += (desired.StencilBits - current->StencilBits) *
					         (desired.StencilBits - current->StencilBits);
			}

			if (desired.AccumRedBits != -1)
			{
				extraDiff += (desired.AccumRedBits - current->AccumRedBits) *
					         (desired.AccumRedBits - current->AccumRedBits);
			}

			if (desired.AccumGreenBits != -1)
			{
				extraDiff += (desired.AccumGreenBits - current->AccumGreenBits) *
					         (desired.AccumGreenBits - current->AccumGreenBits);
			}

			if (desired.AccumBlueBits != -1)
			{
				extraDiff += (desired.AccumBlueBits - current->AccumBlueBits) *
					         (desired.AccumBlueBits - current->AccumBlueBits);
			}

			if (desired.AccumAlphaBits != -1)
			{
				extraDiff += (desired.AccumAlphaBits - current->AccumAlphaBits) *
					         (desired.AccumAlphaBits - current->AccumAlphaBits);
			}

			if (desired.Samples != -1)
			{
				extraDiff += (desired.Samples - current->Samples) *
					         (desired.Samples - current->Samples);
			}

			if (desired.SRGB && !current->SRGB)
				extraDiff++;
		}

		//Figure out if the current one is better than the best one found so far
		//Least number of missing buffers is the most important heuristic,
		//then color buffer size match and lastly size match for other buffers

		if (missing < leastMissing)
			closest = current;
		else if (missing == leastMissing)
		{
			if ((colorDiff < leastColorDiff) ||
				(colorDiff == leastColorDiff && extraDiff < leastExtraDiff))
			{
				closest = current;
			}
		}

		if (current == closest)
		{
			leastMissing = missing;
			leastColorDiff = colorDiff;
			leastExtraDiff = extraDiff;
		}
	}

	return closest;
}

//-------------------------------------------------------------------------------------------------------------------//

//Returns a list of available and usable framebuffer configs
int32_t TRAP::INTERNAL::WindowingAPI::ChoosePixelFormat(const Ref<InternalWindow> window,
                                                        const ContextConfig& CTXConfig,
                                                        const FrameBufferConfig& FBConfig)
{
	std::vector<FrameBufferConfig> usableConfigs{};
	int32_t pixelFormat, nativeCount, usableCount = 0;
	std::vector<int32_t> attribs{};
	std::vector<int32_t> values{};

	if (s_Data.WGL.ARB_pixel_format)
	{
		const int32_t attrib = WGL_NUMBER_PIXEL_FORMATS_ARB;

		if (!s_Data.WGL.GetPixelFormatAttribivARB(window->Context.DC,
			1, 0, 1, &attrib, &nativeCount))
		{
			InputErrorWin32(Error::Platform_Error, "[WGL] Failed to retrieve pixel format attribute");
			return 0;
		}

		attribs.emplace_back(WGL_SUPPORT_OPENGL_ARB);
		attribs.emplace_back(WGL_DRAW_TO_WINDOW_ARB);
		attribs.emplace_back(WGL_PIXEL_TYPE_ARB);
		attribs.emplace_back(WGL_ACCELERATION_ARB);
		attribs.emplace_back(WGL_RED_BITS_ARB);
		attribs.emplace_back(WGL_RED_SHIFT_ARB);
		attribs.emplace_back(WGL_GREEN_BITS_ARB);
		attribs.emplace_back(WGL_GREEN_SHIFT_ARB);
		attribs.emplace_back(WGL_BLUE_BITS_ARB);
		attribs.emplace_back(WGL_BLUE_SHIFT_ARB);
		attribs.emplace_back(WGL_ALPHA_BITS_ARB);
		attribs.emplace_back(WGL_ALPHA_SHIFT_ARB);
		attribs.emplace_back(WGL_DEPTH_BITS_ARB);
		attribs.emplace_back(WGL_STENCIL_BITS_ARB);
		attribs.emplace_back(WGL_ACCUM_BITS_ARB);
		attribs.emplace_back(WGL_ACCUM_RED_BITS_ARB);
		attribs.emplace_back(WGL_ACCUM_GREEN_BITS_ARB);
		attribs.emplace_back(WGL_ACCUM_BLUE_BITS_ARB);
		attribs.emplace_back(WGL_ACCUM_ALPHA_BITS_ARB);
		attribs.emplace_back(WGL_AUX_BUFFERS_ARB);
		attribs.emplace_back(WGL_STEREO_ARB);
		attribs.emplace_back(WGL_DOUBLE_BUFFER_ARB);

		if (s_Data.WGL.ARB_multisample)
			attribs.emplace_back(WGL_SAMPLES_ARB);

		if (s_Data.WGL.ARB_framebuffer_sRGB || s_Data.WGL.EXT_framebuffer_sRGB)
			attribs.emplace_back(WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB);
	}
	else
	{
		nativeCount = DescribePixelFormat(window->Context.DC,
			1,
			sizeof(PIXELFORMATDESCRIPTOR),
			nullptr);
	}

	usableConfigs.resize(nativeCount);

	for (uint32_t i = 0; i < static_cast<uint32_t>(nativeCount); i++)
	{
		FrameBufferConfig& u = usableConfigs[usableCount];
		pixelFormat = i + 1;

		if (s_Data.WGL.ARB_pixel_format)
		{
			//Get pixel format attributes through "modern" extension
			values.resize(attribs.size());
			
			if (!s_Data.WGL.GetPixelFormatAttribivARB(window->Context.DC,
				pixelFormat, 0,
				static_cast<uint32_t>(attribs.size()),
				attribs.data(), values.data()))
			{
				InputErrorWin32(Error::Platform_Error, "[WGL] Failed to retrieve pixel format attributes");
				return 0;
			}

			if (!FindPixelFormatAttribValue(attribs, values, WGL_SUPPORT_OPENGL_ARB) ||
				!FindPixelFormatAttribValue(attribs, values, WGL_DRAW_TO_WINDOW_ARB))
				continue;

			if (FindPixelFormatAttribValue(attribs, values, WGL_PIXEL_TYPE_ARB) != WGL_TYPE_RGBA_ARB)
				continue;

			if (FindPixelFormatAttribValue(attribs, values, WGL_ACCELERATION_ARB) == WGL_NO_ACCELERATION_ARB)
				continue;

			u.RedBits = FindPixelFormatAttribValue(attribs, values, WGL_RED_BITS_ARB);
			u.GreenBits = FindPixelFormatAttribValue(attribs, values, WGL_GREEN_BITS_ARB);
			u.BlueBits = FindPixelFormatAttribValue(attribs, values, WGL_BLUE_BITS_ARB);
			u.AlphaBits = FindPixelFormatAttribValue(attribs, values, WGL_ALPHA_BITS_ARB);

			u.DepthBits = FindPixelFormatAttribValue(attribs, values, WGL_DEPTH_BITS_ARB);
			u.StencilBits = FindPixelFormatAttribValue(attribs, values, WGL_STENCIL_BITS_ARB);

			u.AccumRedBits = FindPixelFormatAttribValue(attribs, values, WGL_ACCUM_RED_BITS_ARB);
			u.AccumGreenBits = FindPixelFormatAttribValue(attribs, values, WGL_ACCUM_GREEN_BITS_ARB);
			u.AccumBlueBits = FindPixelFormatAttribValue(attribs, values, WGL_ACCUM_BLUE_BITS_ARB);
			u.AccumAlphaBits = FindPixelFormatAttribValue(attribs, values, WGL_ACCUM_ALPHA_BITS_ARB);

			u.AuxBuffers = FindPixelFormatAttribValue(attribs, values, WGL_AUX_BUFFERS_ARB);

			if (FindPixelFormatAttribValue(attribs, values, WGL_STEREO_ARB))
				u.Stereo = true;
			if (FindPixelFormatAttribValue(attribs, values, WGL_DOUBLE_BUFFER_ARB))
				u.DoubleBuffer = true;

			if (s_Data.WGL.ARB_multisample)
				u.Samples = FindPixelFormatAttribValue(attribs, values, WGL_SAMPLES_ARB);

			if (s_Data.WGL.ARB_framebuffer_sRGB || s_Data.WGL.EXT_framebuffer_sRGB)
				if (FindPixelFormatAttribValue(attribs, values, WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB))
					u.SRGB = true;
		}
		else
		{
			//Get pixel format attributes through legacy PFDs

			PIXELFORMATDESCRIPTOR pfd;

			if (!DescribePixelFormat(window->Context.DC,
				pixelFormat,
				sizeof(PIXELFORMATDESCRIPTOR),
				&pfd))
			{
				InputErrorWin32(Error::Platform_Error, "[WGL] Failed to describe pixel format");
				return 0;
			}

			if (!(pfd.dwFlags & PFD_DRAW_TO_WINDOW) ||
				!(pfd.dwFlags & PFD_SUPPORT_OPENGL))
				continue;

			if (!(pfd.dwFlags & PFD_GENERIC_ACCELERATED) &&
				(pfd.dwFlags & PFD_GENERIC_FORMAT))
				continue;

			if (pfd.iPixelType != PFD_TYPE_RGBA)
				continue;

			u.RedBits = pfd.cRedBits;
			u.GreenBits = pfd.cGreenBits;
			u.BlueBits = pfd.cBlueBits;
			u.AlphaBits = pfd.cAlphaBits;

			u.DepthBits = pfd.cDepthBits;
			u.StencilBits = pfd.cStencilBits;

			u.AccumRedBits = pfd.cAccumRedBits;
			u.AccumGreenBits = pfd.cAccumGreenBits;
			u.AccumBlueBits = pfd.cAccumBlueBits;
			u.AccumAlphaBits = pfd.cAccumAlphaBits;

			u.AuxBuffers = pfd.cAuxBuffers;

			if (pfd.dwFlags & PFD_STEREO)
				u.Stereo = true;
			if (pfd.dwFlags & PFD_DOUBLEBUFFER)
				u.DoubleBuffer = true;
		}

		u.Handle = pixelFormat;
		usableCount++;
	}

	if (!usableCount)
	{
		InputError(Error::API_Unavailable, "[WGL] The driver does not appear to support OpenGL");
		return 0;
	}

	const FrameBufferConfig* closest = ChooseFBConfig(FBConfig, usableConfigs);
	if (!closest)
	{
		InputError(Error::Format_Unavailable, "[WGL] Failed to find a suitable pixel format");
		return 0;
	}

	pixelFormat = static_cast<int32_t>(closest->Handle);

	return pixelFormat;
}

//-------------------------------------------------------------------------------------------------------------------//

//Retrieves the attributes of the current context
bool TRAP::INTERNAL::WindowingAPI::RefreshContextAttribs(const Ref<InternalWindow>& window,
	                                                     const ContextConfig& CTXConfig)
{
	window->Context.Client = ContextAPI::OpenGL;

	const auto winPtr = static_cast<InternalWindow*>(PlatformGetTLS(s_Data.ContextSlot));
	const Ref<InternalWindow> previous = Ref<InternalWindow>(winPtr, [](InternalWindow*) {});;
	MakeContextCurrent(window);

	window->Context.GetIntegerv = reinterpret_cast<PFNGLGETINTEGERVPROC>(window->Context.GetProcAddress("glGetIntegerv"));
	window->Context.GetString = reinterpret_cast<PFNGLGETSTRINGPROC>(window->Context.GetProcAddress("glGetString"));
	if (!window->Context.GetIntegerv || !window->Context.GetString)
	{
		InputError(Error::Platform_Error, " Entry point retrieval is broken");
		MakeContextCurrent(previous);
		return false;
	}

	const char* version = reinterpret_cast<const char*>(window->Context.GetString(GL_VERSION));
	if (!version)
	{
		if (CTXConfig.Client == ContextAPI::OpenGL)
		{
			InputError(Error::Platform_Error, "[OpenGL] version string retrieval is broken");
		}

		MakeContextCurrent(previous);
		return false;
	}

	std::vector<std::string> splittedVersion = Utils::String::SplitString(version, '.');

	if (splittedVersion.empty() || splittedVersion.size() < 2)
	{
		if (window->Context.Client == ContextAPI::OpenGL)
			InputError(Error::Platform_Error, "[OpenGL] No version found in OpenGL version string");

		MakeContextCurrent(previous);
		return false;
	}

	window->Context.Major = std::stoi(splittedVersion[0]);
	window->Context.Minor = std::stoi(splittedVersion[1]);

	if (window->Context.Major < 4 ||
		(window->Context.Major == 4 &&
			window->Context.Minor < 6))
	{
		//The desired OpenGL version is greater than the actual version
		//This only happens if the machine lacks {GLX|WGL}_ARB_create_context
		//and the user has requested an OpenGL version greater than 1.0

		//For API consistency, we emulate the behavior of the
		//{GLX|WGL}_ARB_create_context extension and fail here

		if (window->Context.Client == ContextAPI::OpenGL)
			InputError(Error::Version_Unavailable, "[OpenGl] Requested OpenGL version 4.6, got version " + std::to_string(window->Context.Major) + "." + std::to_string(window->Context.Minor));

		MakeContextCurrent(previous);
		return false;
	}

	//OpenGL 3.0+ uses a different function for extension string retrieval
	//We cache it here instead of in ExtensionSupported mostly to alert
	//users as early as possible that their build may be broken

	window->Context.GetStringi = reinterpret_cast<PFNGLGETSTRINGIPROC>(window->Context.GetProcAddress("glGetStringi"));
	if (!window->Context.GetStringi)
	{
		InputError(Error::Platform_Error, " Entry point retrieval is broken");
		MakeContextCurrent(previous);
		return false;
	}

	if (window->Context.Client == ContextAPI::OpenGL)
	{
		GLint flags;
		window->Context.GetIntegerv(GL_CONTEXT_FLAGS, &flags);

		//Read back OpenGL context profile (OpenGL 3.2 and above)
		GLint mask;
		window->Context.GetIntegerv(GL_CONTEXT_PROFILE_MASK, &mask);
	}

	//Clearing the front buffer to black to avoid garbage pixels left over from
	//previous uses of our bit of VRAM
	{
		const PFNGLCLEARPROC glClearWin = reinterpret_cast<PFNGLCLEARPROC>(window->Context.GetProcAddress("glClear"));
		glClearWin(GL_COLOR_BUFFER_BIT);
		window->Context.SwapBuffers(window);
	}

	MakeContextCurrent(previous);
	return true;
}


//-------------------------------------------------------------------------------------------------------------------//

//Returns whether the cursor is in the content area of the specified window
bool TRAP::INTERNAL::WindowingAPI::CursorInContentArea(const Ref<InternalWindow> window)
{
	RECT area{};
	POINT pos{};

	if (!::GetCursorPos(&pos))
		return false;

	if (WindowFromPoint(pos) != window->Handle)
		return false;

	GetClientRect(window->Handle, &area);
	ClientToScreen(window->Handle, reinterpret_cast<POINT*>(&area.left));
	ClientToScreen(window->Handle, reinterpret_cast<POINT*>(&area.right));

	return PtInRect(&area, pos);
}

//-------------------------------------------------------------------------------------------------------------------//

//Updates the cursor image according to its cursor mode
void TRAP::INTERNAL::WindowingAPI::UpdateCursorImage(const Ref<InternalWindow> window)
{
	if (window->CursorMode == CursorMode::Normal)
	{
		if (window->Cursor)
			::SetCursor(window->Cursor->Handle);
		else
			::SetCursor(LoadCursorW(nullptr, IDC_ARROW));
	}
	else
		::SetCursor(nullptr);
}

//-------------------------------------------------------------------------------------------------------------------//

//Creates an RGBA icon or cursor
HICON TRAP::INTERNAL::WindowingAPI::CreateIcon(const Scope<Image>& image, const int32_t xHot, const int32_t yHot, const bool icon)
{
	BITMAPV5HEADER bi;
	ICONINFO ii;
	uint8_t* target = nullptr;
	uint8_t* source = static_cast<uint8_t*>(image->GetPixelData());

	ZeroMemory(&bi, sizeof(bi));
	bi.bV5Size = sizeof(bi);
	bi.bV5Width = image->GetWidth();
	bi.bV5Height = -static_cast<int32_t>(image->GetHeight());
	bi.bV5Planes = 1;
	bi.bV5BitCount = 32;
	bi.bV5Compression = BI_BITFIELDS;
	bi.bV5RedMask = 0x00ff0000;
	bi.bV5GreenMask = 0x0000ff00;
	bi.bV5BlueMask = 0x000000ff;
	bi.bV5AlphaMask = 0xff000000;

	const HDC dc = GetDC(nullptr);
	const HBITMAP color = CreateDIBSection(dc,
		reinterpret_cast<BITMAPINFO*>(&bi),
		DIB_RGB_COLORS,
		reinterpret_cast<void**>(&target),
		nullptr,
		static_cast<DWORD>(0));
	ReleaseDC(nullptr, dc);

	if (!color)
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to create RGBA bitmap");
		return nullptr;
	}

	const HBITMAP mask = CreateBitmap(image->GetWidth(), image->GetHeight(), 1, 1, nullptr);
	if (!mask)
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to create mask bitmap");
		DeleteObject(color);
		return nullptr;
	}

	for (uint32_t i = 0; i < image->GetWidth() * image->GetHeight(); i++)
	{
		target[0] = source[2];
		target[1] = source[1];
		target[2] = source[0];
		target[3] = source[3];
		target += 4;
		source += 4;
	}

	ZeroMemory(&ii, sizeof(ii));
	ii.fIcon = icon;
	ii.xHotspot = xHot;
	ii.yHotspot = yHot;
	ii.hbmMask = mask;
	ii.hbmColor = color;

	const HICON handle = CreateIconIndirect(&ii);

	DeleteObject(color);
	DeleteObject(mask);

	if (!handle)
	{
		if (icon)
			InputErrorWin32(Error::Platform_Error, "[Win32] Failed to create icon");
		else
			InputErrorWin32(Error::Platform_Error, "[Win32] Failed to create cursor");
	}

	return handle;
}

//-------------------------------------------------------------------------------------------------------------------//

//Notifies shared code that the user wishes to close a window
void TRAP::INTERNAL::WindowingAPI::InputWindowCloseRequest(const Ref<InternalWindow> window)
{
	window->ShouldClose = true;

	if (window->Callbacks.Close)
		window->Callbacks.Close(window);
}

//-------------------------------------------------------------------------------------------------------------------//

//Notifies shared code of a physical key event
void TRAP::INTERNAL::WindowingAPI::InputKey(Ref<InternalWindow> window, Input::Key key, const int32_t scancode, const bool pressed)
{
	if (!pressed && window->Keys[static_cast<uint32_t>(key)] == false)
		return;

	window->Keys[static_cast<uint32_t>(key)] = pressed;

	if (window->Callbacks.Key)
		window->Callbacks.Key(window, key, scancode, pressed);
}

//-------------------------------------------------------------------------------------------------------------------//

//Updates the cursor clip rect
void TRAP::INTERNAL::WindowingAPI::UpdateClipRect(const Ref<InternalWindow> window)
{
	if (window)
	{
		RECT clipRect;
		GetClientRect(window->Handle, &clipRect);
		ClientToScreen(window->Handle, reinterpret_cast<POINT*>(&clipRect.left));
		ClientToScreen(window->Handle, reinterpret_cast<POINT*>(&clipRect.right));
		ClipCursor(&clipRect);
	}
	else
		ClipCursor(nullptr);
}

//-------------------------------------------------------------------------------------------------------------------//

//Enables WM_INPUT messages for the mouse for the specified window
void TRAP::INTERNAL::WindowingAPI::EnableRawMouseMotion(const Ref<InternalWindow> window)
{
	const RAWINPUTDEVICE rid = { 0x01, 0x02, 0, window->Handle };

	if (!RegisterRawInputDevices(&rid, 1, sizeof(rid)))
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to register raw input device");
}

//-------------------------------------------------------------------------------------------------------------------//

//Disables WM_INPUT messages for the mouse
void TRAP::INTERNAL::WindowingAPI::DisableRawMouseMotion(Ref<InternalWindow> window)
{
	const RAWINPUTDEVICE rid = { 0x01, 0x02, RIDEV_REMOVE, nullptr };

	if (!RegisterRawInputDevices(&rid, 1, sizeof(rid)))
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to remove raw input device");
}

//-------------------------------------------------------------------------------------------------------------------//

//Exit disabled cursor mode for the specified window
void TRAP::INTERNAL::WindowingAPI::EnableCursor(const Ref<InternalWindow> window)
{
	if (window->RawMouseMotion)
		DisableRawMouseMotion(window);

	s_Data.DisabledCursorWindow = nullptr;
	UpdateClipRect(nullptr);
	PlatformSetCursorPos(window, s_Data.RestoreCursorPosX, s_Data.RestoreCursorPosY);
	UpdateCursorImage(window);
}

//-------------------------------------------------------------------------------------------------------------------//

//Apply disabled cursor mode to a focused window
void TRAP::INTERNAL::WindowingAPI::DisableCursor(const Ref<InternalWindow> window)
{
	s_Data.DisabledCursorWindow = window;
	PlatformGetCursorPos(window, s_Data.RestoreCursorPosX, s_Data.RestoreCursorPosY);
	UpdateCursorImage(window);
	CenterCursorInContentArea(window);
	UpdateClipRect(window);

	if (window->RawMouseMotion)
		EnableRawMouseMotion(window);
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::INTERNAL::WindowingAPI::InitVulkan(const uint32_t mode)
{
	uint32_t count;

	if (s_Data.VK.Available)
		return true;

	VkResult err = vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
	if (err)
	{
		//NOTE: This happens on systems with a loader but without any Vulkan ICD
		if (mode == 2)
			InputError(Error::API_Unavailable, "[Vulkan] Failed to query instance extension count: " + GetVulkanResultString(err));

		return false;
	}

	std::vector<VkExtensionProperties> ep(count);

	err = vkEnumerateInstanceExtensionProperties(nullptr, &count, ep.data());
	if (err)
	{
		InputError(Error::API_Unavailable, "[Vulkan] Failed to query instance extensions: " + GetVulkanResultString(err));
		return false;
	}

	for (uint32_t i = 0; i < count; i++)
	{
		const std::string_view ext(ep[i].extensionName);
		
		if (ext == "VK_KHR_surface")
			s_Data.VK.KHR_Surface = true;
#if defined(TRAP_PLATFORM_WINDOWS)
		else if (ext == "VK_KHR_win32_surface")
			s_Data.VK.KHR_Win32_Surface = true;
#elif defined(TRAP_PLATFORM_LINUX_X11)
		else if (ext == "VK_KHR_xlib_surface")
			s_Data.VK.KHR_XLib_Surface = true;
		else if (ext == "VK_KHR_xcb_surface")
			s_Data.VK.KHR_XCB_Surface = true;
#elif defined(TRAP_PLATFORM_LINUX_WAYLAND)
		else if (ext == "VK_KHR_wayland_surface")
			s_Data.VK.KHR_Wayland_Surface = true;
#endif
	}

	s_Data.VK.Available = true;

	PlatformGetRequiredInstanceExtensions(s_Data.VK.Extensions);

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

std::string TRAP::INTERNAL::WindowingAPI::GetVulkanResultString(const VkResult result)
{
	switch (result)
	{
	case VK_SUCCESS:
		return "Success";
	case VK_NOT_READY:
		return "A fence or query has not yet completed";
	case VK_TIMEOUT:
		return "A wait operation has not completed in the specified time";
	case VK_EVENT_SET:
		return "An event is signaled";
	case VK_EVENT_RESET:
		return "An event is unsignaled";
	case VK_INCOMPLETE:
		return "A return array was too small for the result";
	case VK_ERROR_OUT_OF_HOST_MEMORY:
		return "A host memory allocation has failed";
	case VK_ERROR_OUT_OF_DEVICE_MEMORY:
		return "A device memory allocation has failed";
	case VK_ERROR_INITIALIZATION_FAILED:
		return "Initialization of an object could not be completed for implementation-specific reasons";
	case VK_ERROR_DEVICE_LOST:
		return "The logical or physical device has been lost";
	case VK_ERROR_MEMORY_MAP_FAILED:
		return "Mapping of a memory object has failed";
	case VK_ERROR_LAYER_NOT_PRESENT:
		return "A requested layer is not present or could not be loaded";
	case VK_ERROR_EXTENSION_NOT_PRESENT:
		return "A requested extension is not supported";
	case VK_ERROR_FEATURE_NOT_PRESENT:
		return "A requested feature is not supported";
	case VK_ERROR_INCOMPATIBLE_DRIVER:
		return "The requested version of Vulkan is not supported by the driver or is otherwise incompatible";
	case VK_ERROR_TOO_MANY_OBJECTS:
		return "Too many objects of the type have already been created";
	case VK_ERROR_FORMAT_NOT_SUPPORTED:
		return "A requested format is not supported on this device";
	case VK_ERROR_SURFACE_LOST_KHR:
		return "A surface is no longer available";
	case VK_SUBOPTIMAL_KHR:
		return "A swapchain no longer matches the surface properties exactly, but can still be used";
	case VK_ERROR_OUT_OF_DATE_KHR:
		return "A surface has changed in such a way that it is no longer compatible with the swapchain";
	case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
		return "The display used by a swapchain does not use the same presentable image layout";
	case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
		return "The requested window is already connected to a VkSurfaceKHR, or to some other non-Vulkan API";
	case VK_ERROR_VALIDATION_FAILED_EXT:
		return "A validation layer found an error";
	default:
		return "UNKNOWN VULKAN ERROR";
	}
}

//-------------------------------------------------------------------------------------------------------------------//

HWND TRAP::INTERNAL::WindowingAPI::GetWin32Window(const Ref<InternalWindow> window)
{	
	return window->Handle;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformGetVideoMode(Ref<InternalMonitor> monitor, VideoMode& mode)
{
	DEVMODEW dm;
	ZeroMemory(&dm, sizeof(dm));
	dm.dmSize = sizeof(dm);

	EnumDisplaySettingsW(monitor->AdapterName.data(), ENUM_CURRENT_SETTINGS, &dm);

	mode.Width = dm.dmPelsWidth;
	mode.Height = dm.dmPelsHeight;
	mode.RefreshRate = dm.dmDisplayFrequency;
	SplitBPP(dm.dmBitsPerPel,
		mode.RedBits,
		mode.GreenBits,
		mode.BlueBits);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformGetWindowSize(const Ref<InternalWindow> window, int32_t& width, int32_t& height)
{
	RECT area{};
	GetClientRect(window->Handle, &area);

	width = area.right;
	height = area.bottom;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformGetWindowFrameSize(const Ref<InternalWindow> window,
                                                              int32_t& left, int32_t& top,
                                                              int32_t& right, int32_t& bottom)
{
	RECT rect{};
	int32_t width = 0, height = 0;

	PlatformGetWindowSize(window, width, height);
	SetRect(&rect, 0, 0, width, height);

	if (IsWindows10AnniversaryUpdateOrGreaterWin32())
	{
		s_Data.User32.AdjustWindowRectExForDPI(&rect, GetWindowStyle(window),
			FALSE, GetWindowExStyle(window),
			s_Data.User32.GetDPIForWindow(window->Handle));
	}
	else
	{
		AdjustWindowRectEx(&rect, GetWindowStyle(window),
			FALSE, GetWindowExStyle(window));
	}

	left = -rect.left;
	top = -rect.top;
	right = rect.right - width;
	bottom = rect.bottom - height;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformSetWindowPos(const Ref<InternalWindow> window, const int32_t xPos, const int32_t yPos)
{
	RECT rect = { xPos, yPos, xPos, yPos };

	if (IsWindows10AnniversaryUpdateOrGreaterWin32())
	{
		s_Data.User32.AdjustWindowRectExForDPI(&rect, GetWindowStyle(window),
			FALSE, GetWindowExStyle(window),
			s_Data.User32.GetDPIForWindow(window->Handle));
	}
	else
	{
		AdjustWindowRectEx(&rect, GetWindowStyle(window),
			FALSE, GetWindowExStyle(window));
	}

	::SetWindowPos(window->Handle, nullptr, rect.left, rect.top, 0, 0,
		SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformSetWindowMonitor(const Ref<InternalWindow>& window,
                                                            const Ref<InternalMonitor> monitor,
	                                                        const int32_t xPos, const int32_t yPos,
	                                                        const int32_t width, const int32_t height,
	                                                        const int32_t refreshRate)
{
	if (window->Monitor == monitor)
	{
		if (monitor)
		{
			if (monitor->Window == window)
			{
				AcquireMonitor(window);
				FitToMonitor(window);
			}
		}
		else
		{
			RECT rect = { xPos, yPos, xPos + width, yPos + height };

			if (IsWindows10AnniversaryUpdateOrGreaterWin32())
			{
				s_Data.User32.AdjustWindowRectExForDPI(&rect, GetWindowStyle(window),
					FALSE, GetWindowExStyle(window),
					s_Data.User32.GetDPIForWindow(window->Handle));
			}
			else
			{
				AdjustWindowRectEx(&rect, GetWindowStyle(window),
					FALSE, GetWindowExStyle(window));
			}

			::SetWindowPos(window->Handle, HWND_TOP,
				rect.left, rect.top,
				rect.right - rect.left, rect.bottom - rect.top,
				SWP_NOCOPYBITS | SWP_NOACTIVATE | SWP_NOZORDER);
		}

		//Note: Set VSync interval again because DWM now doesnt apply here
		SwapInterval(window->Context.Interval);

		return;
	}

	if (window->Monitor)
		ReleaseMonitor(window);
	if (window->BorderlessFullscreen)
		window->BorderlessFullscreen = false;

	window->Monitor = monitor;

	if (window->Monitor)
	{
		MONITORINFO mi = { sizeof(mi) };
		UINT flags = SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOCOPYBITS;

		if (window->Decorated)
		{
			DWORD style = static_cast<DWORD>(GetWindowLongPtrW(window->Handle, GWL_STYLE));
			style &= ~WS_OVERLAPPEDWINDOW;
			style |= GetWindowStyle(window);
			SetWindowLongW(window->Handle, GWL_STYLE, style);
			flags |= SWP_FRAMECHANGED;
		}

		AcquireMonitor(window);

		GetMonitorInfo(window->Monitor->Handle, &mi);
		::SetWindowPos(window->Handle, HWND_TOPMOST,
			mi.rcMonitor.left,
			mi.rcMonitor.top,
			mi.rcMonitor.right - mi.rcMonitor.left,
			mi.rcMonitor.bottom - mi.rcMonitor.top,
			flags);
	}
	else
	{
		RECT rect = { xPos, yPos, xPos + width, yPos + height };
		DWORD style = static_cast<DWORD>(GetWindowLongPtrW(window->Handle, GWL_STYLE));
		UINT flags = SWP_NOACTIVATE | SWP_NOCOPYBITS;

		if (window->Decorated)
		{
			style &= ~WS_POPUP;
			style |= GetWindowStyle(window);
			SetWindowLongW(window->Handle, GWL_STYLE, style);

			flags |= SWP_FRAMECHANGED;
		}

		const HWND after = HWND_NOTOPMOST;

		if (IsWindows10AnniversaryUpdateOrGreaterWin32())
		{
			s_Data.User32.AdjustWindowRectExForDPI(&rect, GetWindowStyle(window),
				FALSE, GetWindowExStyle(window),
				s_Data.User32.GetDPIForWindow(window->Handle));
		}
		else
		{
			AdjustWindowRectEx(&rect, GetWindowStyle(window),
				FALSE, GetWindowExStyle(window));
		}

		::SetWindowPos(window->Handle, after,
			rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top,
			flags);
	}

	//Note: Set VSync interval again because DWM now doesnt apply here
	SwapInterval(window->Context.Interval);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformSetWindowMonitorBorderless(const Ref<InternalWindow>& window, const Ref<InternalMonitor> monitor)
{
	window->BorderlessFullscreen = true;
	window->Monitor = monitor;

	if (window->Monitor)
	{
		MONITORINFO mi = { sizeof(mi) };
		UINT flags = SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOCOPYBITS;

		if (window->Decorated)
		{
			DWORD style = static_cast<DWORD>(GetWindowLongPtrW(window->Handle, GWL_STYLE));
			style &= ~WS_OVERLAPPEDWINDOW;
			style |= GetWindowStyle(window);
			SetWindowLongW(window->Handle, GWL_STYLE, style);
			flags |= SWP_FRAMECHANGED;
		}

		AcquireMonitorBorderless(window);

		GetMonitorInfo(window->Monitor->Handle, &mi);
		::SetWindowPos(window->Handle, HWND_TOP,
			mi.rcMonitor.left,
			mi.rcMonitor.top,
			mi.rcMonitor.right - mi.rcMonitor.left,
			mi.rcMonitor.bottom - mi.rcMonitor.top,
			flags);

		//Note: Set VSync interval again because DWM now doesnt apply here
		SwapInterval(window->Context.Interval);
	}
}

//-------------------------------------------------------------------------------------------------------------------//

std::vector<TRAP::INTERNAL::WindowingAPI::VideoMode> TRAP::INTERNAL::WindowingAPI::PlatformGetVideoModes(Ref<InternalMonitor> monitor)
{
	uint32_t modeIndex = 0, size = 0, count = 0;
	std::vector<VideoMode> result{};

	for (;;)
	{
		uint32_t i;
		VideoMode mode;
		DEVMODEW dm;

		ZeroMemory(&dm, sizeof(dm));
		dm.dmSize = sizeof(dm);

		if (!EnumDisplaySettingsW(monitor->AdapterName.data(), modeIndex, &dm))
			break;

		modeIndex++;

		//Skip modes with less than 15 BPP
		if (dm.dmBitsPerPel < 15)
			continue;

		mode.Width = dm.dmPelsWidth;
		mode.Height = dm.dmPelsHeight;
		mode.RefreshRate = dm.dmDisplayFrequency;
		SplitBPP(dm.dmBitsPerPel,
			mode.RedBits,
			mode.GreenBits,
			mode.BlueBits);

		for (i = 0; i < count; i++)
		{
			if (CompareVideoModes(&result[i], &mode) == 0)
				break;
		}

		//Skip duplicate modes
		if (i < count)
			continue;

		if (monitor->ModesPruned) //TODO Used in old TRAP version by GLFW?!
		{
			//Skip modes not supported by the connected displays
			if (ChangeDisplaySettingsExW(monitor->AdapterName.data(),
				&dm,
				nullptr,
				CDS_TEST,
				nullptr) != DISP_CHANGE_SUCCESSFUL) //Performance Slow!
			{
				continue;
			}
		}

		if (count == size)
		{
			size += 128;
			result.reserve(result.size() + 128);
		}

		count++;
		result.push_back(mode);
	}

	result.shrink_to_fit();

	if (!count)
	{
		//HACK: Report the current mode if no valid modes were found
		result.resize(1);
		PlatformGetVideoMode(monitor, result[0]);
	}

	return result;
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::INTERNAL::WindowingAPI::PlatformInit()
{
	//To make SetForegroundWindow work as we want, we need to fiddle with the FOREGROUNDLOCKTIMEOUT system settings
	//(we do this as early as possible in the hope of still being the foreground process)
	SystemParametersInfoW(SPI_GETFOREGROUNDLOCKTIMEOUT, 0, &s_Data.ForegroundLockTimeout, 0);
	SystemParametersInfoW(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, UIntToPtr(0), SPIF_SENDCHANGE);

	if (!LoadLibraries())
		return false;

	CreateKeyTables();
	UpdateKeyNamesWin32();

	if (IsWindows10CreatorsUpdateOrGreaterWin32())
		s_Data.User32.SetProcessDPIAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
	else if (IsWindows8Point1OrGreaterWin32())
		s_Data.SHCore.SetProcessDPIAwareness(Process_DPI_Awareness::Process_Per_Monitor_DPI_Aware); //Process per monitor DPI aware
	else if (IsWindowsVistaOrGreaterWin32())
		s_Data.User32.SetProcessDPIAware();

	if (!RegisterWindowClassWin32())
		return false;

	if (!CreateHelperWindow())
		return false;

	PollMonitorsWin32();

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::INTERNAL::WindowingAPI::PlatformCreateMutex(Mutex& mutex)
{
	TRAP_WINDOW_ASSERT(!mutex.Allocated, "[Window] Mutex is already in use!");
	InitializeCriticalSection(&mutex.Section);
	mutex.Allocated = true;
	
	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::INTERNAL::WindowingAPI::PlatformCreateTLS(TLS& tls)
{
	TRAP_WINDOW_ASSERT(!tls.Allocated, "[Window] Tls is already in use!");

	tls.Index = TlsAlloc();
	if (tls.Index == TLS_OUT_OF_INDEXES)
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to allocate TLS index");
		return false;
	}

	tls.Allocated = true;
	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformSetTLS(TLS& tls, void* value)
{
	TRAP_WINDOW_ASSERT(tls.Allocated, "[Window] Tls is not allocated!");
	TlsSetValue(tls.Index, value);
}

//-------------------------------------------------------------------------------------------------------------------//

void* TRAP::INTERNAL::WindowingAPI::PlatformGetTLS(TLS& tls)
{
	TRAP_WINDOW_ASSERT(tls.Allocated, "[Window] Tls is not allocated!");
	return TlsGetValue(tls.Index);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformDestroyTLS(TLS& tls)
{
	if (tls.Allocated)
		TlsFree(tls.Index);
	tls = {};
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformDestroyMutex(Mutex& mutex)
{
	if (mutex.Allocated)
		DeleteCriticalSection(&mutex.Section);
	mutex = {};
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformLockMutex(Mutex& mutex)
{
	TRAP_WINDOW_ASSERT(mutex.Allocated, "[Window] Mutex is not allocated!");
	EnterCriticalSection(&mutex.Section);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformUnlockMutex(Mutex& mutex)
{
	TRAP_WINDOW_ASSERT(mutex.Allocated, "[Window] Mutex is not allocated!");
	LeaveCriticalSection(&mutex.Section);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformDestroyWindow(const Ref<InternalWindow> window)
{
	if (window->Monitor)
		ReleaseMonitor(window);

	if (window->Context.Destroy)
		window->Context.Destroy(window);

	if (s_Data.DisabledCursorWindow == window)
		s_Data.DisabledCursorWindow = nullptr;

	if (window->Handle)
	{
		RemovePropW(window->Handle, L"TRAP");
		::DestroyWindow(window->Handle);
		window->Handle = nullptr;
	}

	if (window->BigIcon)
		DestroyIcon(window->BigIcon);

	if (window->SmallIcon)
		DestroyIcon(window->SmallIcon);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformShutdown()
{
	if (s_Data.DeviceNotificationHandle)
		UnregisterDeviceNotification(s_Data.DeviceNotificationHandle);

	if (s_Data.HelperWindowHandle)
		::DestroyWindow(s_Data.HelperWindowHandle);

	UnregisterWindowClassWin32();

	//Restore previous foreground lock timeout system setting
	SystemParametersInfoW(SPI_SETFOREGROUNDLOCKTIMEOUT, 0,
		UIntToPtr(s_Data.ForegroundLockTimeout),
		SPIF_SENDCHANGE);

	s_Data.ClipboardString = {};
	s_Data.RawInput = {};

	ShutdownWGL();

	FreeLibraries();
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformGetMonitorContentScale(const Ref<InternalMonitor> monitor, float& xScale, float& yScale)
{
	GetMonitorContentScaleWin32(monitor->Handle, xScale, yScale);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformGetMonitorPos(Ref<InternalMonitor> monitor, int32_t& xPos, int32_t& yPos)
{
	DEVMODEW dm;
	ZeroMemory(&dm, sizeof(dm));
	dm.dmSize = sizeof(dm);

	EnumDisplaySettingsExW(monitor->AdapterName.data(),
		ENUM_CURRENT_SETTINGS,
		&dm,
		EDS_ROTATEDMODE);

	xPos = dm.dmPosition.x;
	yPos = dm.dmPosition.y;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformShowWindow(const Ref<InternalWindow> window)
{
	ShowWindow(window->Handle, SW_SHOWNA);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformFocusWindow(const Ref<InternalWindow> window)
{
	BringWindowToTop(window->Handle);
	SetForegroundWindow(window->Handle);
	SetFocus(window->Handle);
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::INTERNAL::WindowingAPI::PlatformCreateWindow(Ref<InternalWindow>& window,
	                                                    const WindowConfig& WNDConfig,
	                                                    const ContextConfig& CTXConfig,
	                                                    const FrameBufferConfig& FBConfig)
{
	if (!CreateNativeWindow(window, WNDConfig, FBConfig))
		return false;

	if (CTXConfig.Client != ContextAPI::None)
	{
		if (!InitWGL())
			return false;
		if (!CreateContextWGL(window, CTXConfig, FBConfig))
			return false;
	}

	if (window->Monitor)
	{
		PlatformShowWindow(window);
		PlatformFocusWindow(window);
		AcquireMonitor(window);
		FitToMonitor(window);
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformSetWindowTitle(const Ref<InternalWindow> window, const std::string& title)
{
	std::wstring wideTitle = CreateWideStringFromUTF8StringWin32(title);
	if (wideTitle.empty())
		return;

	SetWindowTextW(window->Handle, wideTitle.data());
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::INTERNAL::WindowingAPI::PlatformCreateCursor(const Ref<InternalCursor> cursor,
                                                        const Scope<Image>& image,
                                                        const int32_t xHotspot,
                                                        const int32_t yHotspot)
{
	cursor->Handle = static_cast<HCURSOR>(CreateIcon(image, xHotspot, yHotspot, false));
	if (!cursor->Handle)
		return false;

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::INTERNAL::WindowingAPI::PlatformCreateStandardCursor(const Ref<InternalCursor> cursor, const CursorType& type)
{
	uint32_t id = OCR_NORMAL;

	switch(type)
	{
		case CursorType::Arrow:
			id = OCR_NORMAL;
			break;

		case CursorType::Input:
			id = OCR_IBEAM;
			break;

		case CursorType::Crosshair:
			id = OCR_CROSS;
			break;

		case CursorType::PointingHand:
			id = OCR_HAND;
			break;

		case CursorType::ResizeVertical:
			id = OCR_SIZENS;
			break;

		case CursorType::ResizeHorizontal:
			id = OCR_SIZEWE;
			break;

		case CursorType::ResizeDiagonalTopLeftBottomRight:
			id = OCR_SIZENWSE;
			break;

		case CursorType::ResizeDiagonalTopRightBottomLeft:
			id = OCR_SIZENESW;
			break;

		case CursorType::ResizeAll:
			id = OCR_SIZEALL;
			break;

		case CursorType::NotAllowed:
			id = OCR_NO;
			break;
		
		default:
			break;
	}
	

	cursor->Handle = static_cast<HCURSOR>(LoadImageW(nullptr,
		MAKEINTRESOURCEW(id),
		IMAGE_CURSOR,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED));
	if (!cursor->Handle)
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to create standard cursor");
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformDestroyCursor(const Ref<InternalCursor> cursor)
{
	if (cursor->Handle)
		DestroyIcon(static_cast<HICON>(cursor->Handle));
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformSetCursor(const Ref<InternalWindow> window, Ref<InternalCursor> cursor)
{
	if (CursorInContentArea(window))
		UpdateCursorImage(window);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformSetCursorMode(const Ref<InternalWindow> window, const CursorMode mode)
{
	if (mode == CursorMode::Disabled)
	{
		if (PlatformWindowFocused(window))
			DisableCursor(window);
	}
	else if (s_Data.DisabledCursorWindow == window)
		EnableCursor(window);
	else if (CursorInContentArea(window))
		UpdateCursorImage(window);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformSetCursorPos(const Ref<InternalWindow> window,
                                                        const double xPos, const double yPos)
{
	POINT pos = { static_cast<int32_t>(xPos), static_cast<int32_t>(yPos) };

	//Store the new position so it can be recognized later
	window->LastCursorPosX = pos.x;
	window->LastCursorPosY = pos.y;

	ClientToScreen(window->Handle, &pos);
	SetCursorPos(pos.x, pos.y);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformGetCursorPos(const Ref<InternalWindow> window, double& xPos, double& yPos)
{
	POINT pos;

	if (::GetCursorPos(&pos))
	{
		ScreenToClient(window->Handle, &pos);

		xPos = pos.x;
		yPos = pos.y;
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformSetWindowIcon(const Ref<InternalWindow> window, const Scope<Image>& image)
{
	HICON bigIcon, smallIcon;

	if (image)
	{
		bigIcon = CreateIcon(image, 0, 0, true);
		smallIcon = bigIcon;
	}
	else
	{
		bigIcon = reinterpret_cast<HICON>(GetClassLongPtrW(window->Handle, GCLP_HICON));
		smallIcon = reinterpret_cast<HICON>(GetClassLongPtrW(window->Handle, GCLP_HICONSM));
	}

	SendMessage(window->Handle, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(bigIcon));
	SendMessage(window->Handle, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(smallIcon));

	if (window->BigIcon)
		DestroyIcon(window->BigIcon);

	if (window->SmallIcon)
		DestroyIcon(window->SmallIcon);

	if (image)
	{
		window->BigIcon = bigIcon;
		window->SmallIcon = smallIcon;
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformGetWindowPos(const Ref<InternalWindow> window, int32_t& xPos, int32_t& yPos)
{
	POINT pos = { 0, 0 };
	ClientToScreen(window->Handle, &pos);

	xPos = pos.x;
	yPos = pos.y;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformSetWindowSize(const Ref<InternalWindow> window, const int32_t width, const int32_t height)
{
	if (window->Monitor)
	{
		if (window->Monitor->Window == window)
		{
			AcquireMonitor(window);
			FitToMonitor(window);
		}
	}
	else
	{
		RECT rect = { 0, 0, width, height };

		if (IsWindows10AnniversaryUpdateOrGreaterWin32())
		{
			s_Data.User32.AdjustWindowRectExForDPI(&rect, GetWindowStyle(window),
				FALSE, GetWindowExStyle(window),
				s_Data.User32.GetDPIForWindow(window->Handle));
		}
		else
		{
			AdjustWindowRectEx(&rect, GetWindowStyle(window),
				FALSE, GetWindowExStyle(window));
		}

		::SetWindowPos(window->Handle, HWND_TOP,
			0, 0, rect.right - rect.left, rect.bottom - rect.top,
			SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOZORDER);
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformGetFrameBufferSize(const Ref<InternalWindow> window, int32_t& width, int32_t& height)
{
	PlatformGetWindowSize(window, width, height);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformGetWindowContentScale(const Ref<InternalWindow> window, float& xScale, float& yScale)
{
	const HANDLE handle = MonitorFromWindow(window->Handle, MONITOR_DEFAULTTONEAREST);
	GetMonitorContentScaleWin32(static_cast<HMONITOR>(handle), xScale, yScale);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformPollEvents()
{
	MSG msg;
	Ref<InternalWindow> window;

	while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			//NOTE: While TRAP does not itself post WM_QUIT, other processes
			//      may post it to this one, for example Task Manager
			//HACK: Treat WM_QUIT as a close on all windows

			window = s_Data.WindowListHead;
			while (window)
			{
				InputWindowCloseRequest(window);
				window = window->Next;
			}
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	const HWND handle = GetActiveWindow();
	if (handle)
	{
		//NOTE: Shift keys on Windows tend to "stick" when both are pressed as
		//      no key up message is generated by the first key release
		//      The other half of this is in the handling of WM_KEYUP
		//HACK: Query actual key state and synthesize release events as needed
		InternalWindow* winPtr = static_cast<InternalWindow*>(GetPropW(handle, L"TRAP"));
		Ref<InternalWindow> windowKey = nullptr;
		if(winPtr)
			//Hack: Convert raw pointer to a smart pointer without deleter so we can use our functions
			windowKey = Ref<InternalWindow>(winPtr, [](InternalWindow*){});

		if (windowKey)
		{
			const bool leftShift = (GetAsyncKeyState(VK_LSHIFT) & 0x8000) != 0;
			const bool rightShift = (GetAsyncKeyState(VK_RSHIFT) & 0x8000) != 0;

			if (!leftShift && windowKey->Keys[static_cast<uint32_t>(Input::Key::Left_Shift)] == true)
			{
				const uint32_t scanCode = s_Data.ScanCodes[static_cast<uint32_t>(Input::Key::Left_Shift)];
				InputKey(Ref<InternalWindow>(windowKey), Input::Key::Left_Shift, scanCode, false);
			}
			else if (!rightShift && windowKey->Keys[static_cast<uint32_t>(Input::Key::Right_Shift)] == true)
			{
				const uint32_t scancode = s_Data.ScanCodes[static_cast<uint32_t>(Input::Key::Right_Shift)];
				InputKey(Ref<InternalWindow>(windowKey), Input::Key::Right_Shift, scancode, false);
			}
		}
	}

	window = s_Data.DisabledCursorWindow;
	if (window)
	{
		int32_t width, height;
		PlatformGetWindowSize(window, width, height);

		if (window->LastCursorPosX != width / 2 ||
			window->LastCursorPosY != height / 2)
			PlatformSetCursorPos(window, width / 2, height / 2);
	}
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::INTERNAL::WindowingAPI::PlatformWindowFocused(const Ref<InternalWindow> window)
{
	return window->Handle == GetActiveWindow();
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::INTERNAL::WindowingAPI::PlatformRawMouseMotionSupported()
{
	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformSetRawMouseMotion(const Ref<InternalWindow> window, const bool enabled)
{
	if (s_Data.DisabledCursorWindow != window)
		return;

	if (enabled)
		EnableRawMouseMotion(window);
	else
		DisableRawMouseMotion(window);
}

//-------------------------------------------------------------------------------------------------------------------//

int32_t TRAP::INTERNAL::WindowingAPI::PlatformGetKeyScanCode(Input::Key key)
{
	return s_Data.ScanCodes[static_cast<uint32_t>(key)];
}

//-------------------------------------------------------------------------------------------------------------------//

const char* TRAP::INTERNAL::WindowingAPI::PlatformGetScanCodeName(const int32_t scanCode)
{
	return s_Data.KeyNames[static_cast<uint32_t>(s_Data.KeyCodes[scanCode])].data();
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformSetClipboardString(const std::string& string)
{
	const int32_t characterCount = MultiByteToWideChar(CP_UTF8, 0, string.data(), -1, nullptr, 0);
	if (!characterCount)
		return;

	const HANDLE object = GlobalAlloc(GMEM_MOVEABLE, characterCount * sizeof(WCHAR));
	if (!object)
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to allocate global handle for clipboard");
		return;
	}

	WCHAR* buffer = static_cast<WCHAR*>(GlobalLock(object));
	if (!buffer)
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to lock global handle");
		GlobalFree(object);
		return;
	}

	MultiByteToWideChar(CP_UTF8, 0, string.data(), -1, buffer, characterCount);
	GlobalUnlock(object);

	if (!OpenClipboard(s_Data.HelperWindowHandle))
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to open clipboard");
		GlobalFree(object);
		return;
	}

	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, object);
	CloseClipboard();
}

//-------------------------------------------------------------------------------------------------------------------//

std::string TRAP::INTERNAL::WindowingAPI::PlatformGetClipboardString()
{
	if (!OpenClipboard(s_Data.HelperWindowHandle))
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to open clipboard");
		return {};
	}

	const HANDLE object = GetClipboardData(CF_UNICODETEXT);
	if (!object)
	{
		InputErrorWin32(Error::Format_Unavailable, "[Win32] Failed to convert clipboard to string");
		CloseClipboard();
		return {};
	}

	WCHAR* buffer = static_cast<WCHAR*>(GlobalLock(object));
	if (!buffer)
	{
		InputErrorWin32(Error::Platform_Error, "[Win32] Failed to lock global handle");
		CloseClipboard();
		return {};
	}

	s_Data.ClipboardString = CreateUTF8StringFromWideStringWin32(buffer);

	GlobalUnlock(object);
	CloseClipboard();

	return s_Data.ClipboardString;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformGetRequiredInstanceExtensions(std::array<std::string, 2>& extensions)
{
	if (!s_Data.VK.KHR_Surface || !s_Data.VK.KHR_Win32_Surface)
		return;

	extensions[0] = "VK_KHR_surface";
	extensions[1] = "VK_KHR_win32_surface";
}

//-------------------------------------------------------------------------------------------------------------------//

VkResult TRAP::INTERNAL::WindowingAPI::PlatformCreateWindowSurface(const VkInstance instance,
                                                                   const Ref<InternalWindow> window,
                                                                   const VkAllocationCallbacks* allocator, VkSurfaceKHR& surface)
{
	const PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(vkGetInstanceProcAddr(instance, "vkCreateWin32SurfaceKHR"));

	if (!vkCreateWin32SurfaceKHR)
	{
		InputError(Error::API_Unavailable, "[Win32] Vulkan instance missing VK_KHR_win32_surface extension");
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}

	VkWin32SurfaceCreateInfoKHR sci
	{
		VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
		nullptr,
		0,
		GetModuleHandle(nullptr),
		window->Handle
	};

	const VkResult err = vkCreateWin32SurfaceKHR(instance, &sci, allocator, &surface);
	if (err)
		InputError(Error::Platform_Error, "[Win32] Failed to create Vulkan surface: " + GetVulkanResultString(err));

	return err;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::WindowingAPI::PlatformMinimizeWindow(const Ref<InternalWindow> window)
{
	ShowWindow(window->Handle, SW_MINIMIZE);
}

#endif