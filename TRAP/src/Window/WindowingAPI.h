#ifndef _TRAP_WINDOWINGAPI_H_
#define _TRAP_WINDOWINGAPI_H_

#include "Utils/Singleton.h"
#include "Input/Input.h"
#include "ImageLoader/Image.h"

namespace TRAP::INTERNAL
{	
	class WindowingAPI final : public Singleton
	{
	public:	
		//-------------------------------------------------------------------------------------------------------------------//
		//Forward Declarations-----------------------------------------------------------------------------------------------//
		//-------------------------------------------------------------------------------------------------------------------//
		//---------//
		//Universal//
		//---------//
		struct InternalWindow;
		struct InternalMonitor;
		struct InternalCursor;
		enum class Error;
	private:
		struct VkWin32SurfaceCreateInfoKHR;
		//---------//
		//Windows//
		//---------//
#ifdef TRAP_PLATFORM_WINDOWS
		enum class Monitor_DPI_Type;
		enum class Process_DPI_Awareness;
#endif
		//-------------------------------------------------------------------------------------------------------------------//
		//Typedefs-----------------------------------------------------------------------------------------------------------//
		//-------------------------------------------------------------------------------------------------------------------//
		//---------//
		//Callbacks//
		//---------//
	public:
		//The function pointer type for error callbacks.
		typedef void (*ErrorFunc)(Error error, const std::string& description);
		//The function pointer type for window position callbacks.
		typedef void (*WindowPositionFunc)(const InternalWindow*, int32_t xPos, int32_t yPos);
		//The function pointer type for window size callbacks.
		typedef void (*WindowSizeFunc)(const InternalWindow*, int32_t width, int32_t height);
		//The function pointer type for window close callbacks.
		typedef void (*WindowCloseFunc)(const InternalWindow*);
		//The function pointer type for window focus callbacks.
		typedef void (*WindowFocusFunc)(const InternalWindow*, bool focused);
		//The function pointer type for framebuffer size callbacks.
		typedef void (*FrameBufferSizeFunc)(const InternalWindow*, int32_t width, int32_t height);
		//The function pointer type for window content scale callbacks.
		typedef void (*WindowContentScaleFunc)(const InternalWindow*, float xScale, float yScale);
		//The function pointer type for mouse button callbacks.
		typedef void (*MouseButtonFunc)(const InternalWindow*, Input::MouseButton mouseButton, bool pressed);
		//The function pointer type for cursor position callbacks.
		typedef void (*CursorPositionFunc)(const InternalWindow*, double xPos, double yPos);
		//The function pointer type for cursor enter callbacks.
		typedef void (*CursorEnterFunc)(const InternalWindow*, bool entered);
		//The function pointer type for scroll callbacks.
		typedef void (*ScrollFunc)(const InternalWindow*, double xOffset, double yOffset);
		//The function pointer type for keyboard key callbacks.
		typedef void (*KeyFunc)(const InternalWindow*, Input::Key key, bool pressed);
		//The function pointer type for Unicode character callbacks.
		typedef void (*CharFunc)(const InternalWindow*, uint32_t codePoint);
		//The function pointer type for path drop callbacks.
		typedef void (*DropFunc)(const InternalWindow*, std::vector<std::string> paths);
		//The function pointer type for monitor configuration callbacks.
		typedef void (*MonitorFunc)(const InternalMonitor*, bool connected); //TODO Implement Interface
	private:
		//--------------//
		//OpenGL Context//
		//--------------//
		//Generic function pointer used for returning client API function pointers
		//without forcing a cast from a regular pointer.
		typedef void (*GLProcess)();
		typedef void (*MakeContextCurrentFunc)(InternalWindow* window);
		typedef void (*SwapBuffersFunc)(const InternalWindow* window);
		typedef void (*SwapIntervalFunc)(int32_t interval);
		typedef bool (*ExtensionSupportedFunc)(const char* extension);
		typedef GLProcess(*GetProcAddressFunc)(const char* process);
		typedef void (*DestroyContextFunc)(InternalWindow* window);
		//--------------//
		//Vulkan Surface//
		//--------------//
		typedef VkFlags VkWin32SurfaceCreateFlagsKHR;
		typedef VkResult(*PFN_vkCreateWin32SurfaceKHR)(VkInstance, const VkWin32SurfaceCreateInfoKHR*, const VkAllocationCallbacks*, VkSurfaceKHR*);
		//-------//
		//Windows//
		//-------//
#ifdef TRAP_PLATFORM_WINDOWS
		//user32.dll function pointer typedefs
		typedef BOOL(WINAPI* PFN_SetProcessDPIAware)();
		typedef BOOL(WINAPI* PFN_ChangeWindowMessageFilterEx)(HWND, UINT, DWORD, CHANGEFILTERSTRUCT*);
		typedef BOOL(WINAPI* PFN_EnableNonClientDPIScaling)(HWND);
		typedef BOOL(WINAPI* PFN_SetProcessDPIAwarenessContext)(HANDLE);
		typedef UINT(WINAPI* PFN_GetDPIForWindow)(HWND);
		typedef BOOL(WINAPI* PFN_AdjustWindowRectExForDPI)(LPRECT, DWORD, BOOL, DWORD, UINT);

		//dwmapi.dll function pointer typedefs
		typedef HRESULT(WINAPI* PFN_DwmIsCompositionEnabled)(BOOL*);
		typedef HRESULT(WINAPI* PFN_DwmFlush)();
		typedef HRESULT(WINAPI* PFN_DwmEnableBlurBehindWindow)(HWND, const DWM_BLURBEHIND*);

		//shcore.dll function pointer typedefs
		typedef HRESULT(WINAPI* PFN_SetProcessDPIAwareness)(Process_DPI_Awareness);
		typedef HRESULT(WINAPI* PFN_GetDPIForMonitor)(HMONITOR, Monitor_DPI_Type, UINT*, UINT*);

		//ntdll.dll function pointer typedefs
		typedef LONG(WINAPI* PFN_RtlVerifyVersionInfo)(OSVERSIONINFOEXW*, ULONG, ULONGLONG);

		//WGL extension pointer typedefs
		typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int32_t interval);
		typedef BOOL(WINAPI* PFNWGLGETPIXELFORMATATTRIBIVARBPROC)(HDC, int32_t, int32_t, UINT, const int32_t*, int32_t*);
		typedef const char* (WINAPI* PFNWGLGETEXTENSIONSSTRINGEXTPROC)();
		typedef const char* (WINAPI* PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC);
		typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int32_t*);

		//opengl32.dll function pointer typedefs
		typedef HGLRC(WINAPI* PFN_WGLCreateContext)(HDC);
		typedef BOOL(WINAPI* PFN_WGLDeleteContext)(HGLRC);
		typedef PROC(WINAPI* PFN_WGLGetProcAddress)(LPCSTR);
		typedef HDC(WINAPI* PFN_WGLGetCurrentDC)();
		typedef HGLRC(WINAPI* PFN_WGLGetCurrentContext)();
		typedef BOOL(WINAPI* PFN_WGLMakeCurrent)(HDC, HGLRC);
		typedef BOOL(WINAPI* PFN_WGLShareLists)(HGLRC, HGLRC);
#endif
		//-------------------------------------------------------------------------------------------------------------------//
		//Enums--------------------------------------------------------------------------------------------------------------//
		//-------------------------------------------------------------------------------------------------------------------//
		//---------//
		//Universal//
		//---------//
	public:		
		enum class Error
		{
			No_Error,
			No_Current_Context,
			Invalid_Enum,
			Invalid_Value,
			Out_Of_Memory,
			API_Unavailable,
			Version_Unavailable,
			Platform_Error,
			Format_Unavailable,
			No_Window_Context,
			Cursor_Unavailable
		};
		enum class Hint
		{
			Resizable,
			Maximized,
			Minimized,
			Visible,
			Focused,
			FocusOnShow,
			Hovered,
			Decorated,
			Floating,
			MousePassthrough
			//Stereo //Used for 3D/VR
		};
		enum class ContextAPI
		{
			None,
			OpenGL
		};
		enum class CursorMode
		{
			Normal,
			Hidden,
			Disabled
		};
		enum class CursorType
		{
			Arrow,
			Input,
			Crosshair,
			PointingHand,
			ResizeHorizontal,
			ResizeVertical,
			ResizeDiagonalTopLeftBottomRight,
			ResizeDiagonalTopRightBottomLeft,
			ResizeAll,
			NotAllowed
		};
	private:
		//-------//
		//Windows//
		//-------//
#ifdef TRAP_PLATFORM_WINDOWS
	#ifndef DPI_ENUMS_DECLARED
		enum class Process_DPI_Awareness
		{
			Process_DPI_Unaware = 0,
			Process_System_DPI_Aware = 1,
			Process_Per_Monitor_DPI_Aware = 2
		};
		enum class Monitor_DPI_Type
		{
			MDT_Effective_DPI = 0,
			MDT_Angular_DPI = 1,
			MDT_Raw_DPI = 2,
			MDT_DEFAULT = MDT_Effective_DPI
		};
	#endif /*DPI_ENUMS_DECLARED*/
#endif /*TRAP_PLATFORM_WINDOWS*/
		//-------------------------------------------------------------------------------------------------------------------//
		//Constant Expressions-----------------------------------------------------------------------------------------------//
		//-------------------------------------------------------------------------------------------------------------------//
		//-------//
		//Windows//
		//-------//
#ifdef TRAP_PLATFORM_WINDOWS
	#ifndef DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2
		#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 ((HANDLE) -4)
	#endif /*DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2*/
		//HACK: Define macros that some windows.h variants don't		
	#ifndef WM_COPYGLOBALDATA
		inline static constexpr uint32_t WM_COPYGLOBALDATA = 0x0049;
	#endif /*WM_COPYGLOBALDATA*/
		//WGL constants
		inline static constexpr uint32_t WGL_NUMBER_PIXEL_FORMATS_ARB = 0x2000;
		inline static constexpr uint32_t WGL_SUPPORT_OPENGL_ARB = 0x2010;
		inline static constexpr uint32_t WGL_DRAW_TO_WINDOW_ARB = 0x2001;
		inline static constexpr uint32_t WGL_PIXEL_TYPE_ARB = 0x2013;
		inline static constexpr uint32_t WGL_TYPE_RGBA_ARB = 0x202b;
		inline static constexpr uint32_t WGL_ACCELERATION_ARB = 0x2003;
		inline static constexpr uint32_t WGL_NO_ACCELERATION_ARB = 0x2025;
		inline static constexpr uint32_t WGL_RED_BITS_ARB = 0x2015;
		inline static constexpr uint32_t WGL_RED_SHIFT_ARB = 0x2016;
		inline static constexpr uint32_t WGL_GREEN_BITS_ARB = 0x2017;
		inline static constexpr uint32_t WGL_GREEN_SHIFT_ARB = 0x2018;
		inline static constexpr uint32_t WGL_BLUE_BITS_ARB = 0x2019;
		inline static constexpr uint32_t WGL_BLUE_SHIFT_ARB = 0x201a;
		inline static constexpr uint32_t WGL_ALPHA_BITS_ARB = 0x201b;
		inline static constexpr uint32_t WGL_ALPHA_SHIFT_ARB = 0x201c;
		inline static constexpr uint32_t WGL_ACCUM_BITS_ARB = 0x201d;
		inline static constexpr uint32_t WGL_ACCUM_RED_BITS_ARB = 0x201e;
		inline static constexpr uint32_t WGL_ACCUM_GREEN_BITS_ARB = 0x201f;
		inline static constexpr uint32_t WGL_ACCUM_BLUE_BITS_ARB = 0x2020;
		inline static constexpr uint32_t WGL_ACCUM_ALPHA_BITS_ARB = 0x2021;
		inline static constexpr uint32_t WGL_DEPTH_BITS_ARB = 0x2022;
		inline static constexpr uint32_t WGL_STENCIL_BITS_ARB = 0x2023;
		inline static constexpr uint32_t WGL_AUX_BUFFERS_ARB = 0x2024;
		inline static constexpr uint32_t WGL_STEREO_ARB = 0x2012;
		inline static constexpr uint32_t WGL_DOUBLE_BUFFER_ARB = 0x2011;
		inline static constexpr uint32_t WGL_SAMPLES_ARB = 0x2042;
		inline static constexpr uint32_t WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB = 0x20a9;
		inline static constexpr uint32_t WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB = 0x00000002;
		inline static constexpr uint32_t WGL_CONTEXT_PROFILE_MASK_ARB = 0x9126;
		inline static constexpr uint32_t WGL_CONTEXT_CORE_PROFILE_BIT_ARB = 0x00000001;
		inline static constexpr uint32_t WGL_CONTEXT_MAJOR_VERSION_ARB = 0x2091;
		inline static constexpr uint32_t WGL_CONTEXT_MINOR_VERSION_ARB = 0x2092;
		inline static constexpr uint32_t WGL_CONTEXT_FLAGS_ARB = 0x2094;
		
		inline static constexpr uint32_t ERROR_INVALID_VERSION_ARB = 0x2095;
		inline static constexpr uint32_t ERROR_INVALID_PROFILE_ARB = 0x2096;
		inline static constexpr uint32_t ERROR_INCOMPATIBLE_DEVICE_CONTEXTS_ARB = 0x2054;
#endif
		//-------------------------------------------------------------------------------------------------------------------//
		//Structs------------------------------------------------------------------------------------------------------------//
		//-------------------------------------------------------------------------------------------------------------------//
		struct VkWin32SurfaceCreateInfoKHR
		{
			VkStructureType sType;
			const void* pNext;
			VkWin32SurfaceCreateFlagsKHR flags;
			HINSTANCE hinstance;
			HWND hwnd;
		};
		//Thread local storage structure
		struct TLS
		{
#ifdef TRAP_PLATFORM_WINDOWS
			bool Allocated = false;
			DWORD Index = 0;
#endif
		};
		//Mutex structure
		struct Mutex
		{
#ifdef TRAP_PLATFORM_WINDOWS
			bool Allocated = false;
			CRITICAL_SECTION Section{};
#endif
		};
		//Per-thread error structure
		struct WindowingError
		{
			WindowingError* Next = nullptr;
			Error ErrorCode = Error::No_Error;
			std::string Description = "";
		};
		//Framebuffer configuration
		struct FrameBufferConfig
		{
			int32_t RedBits = 0;
			int32_t GreenBits = 0;
			int32_t BlueBits = 0;
			int32_t AlphaBits = 0;
			int32_t DepthBits = 0;
			int32_t StencilBits = 0;
			int32_t AccumRedBits = 0;
			int32_t AccumGreenBits = 0;
			int32_t AccumBlueBits = 0;
			int32_t AccumAlphaBits = 0;
			int32_t AuxBuffers = 0;
			bool Stereo = false;
			int32_t Samples = 0;
			bool SRGB = false;
			bool DoubleBuffer = false;
			bool Transparent = false;
			uintptr_t Handle = 0;
		};
		//Window configuration
		struct WindowConfig
		{
			uint32_t Width = 0;
			uint32_t Height = 0;
			std::string Title{};
			bool Resizable = false;
			bool Visible = false;
			bool Decorated = true;
			bool Maximized = false;
			bool Focused = false;
			bool Floating = false;
			bool FocusOnShow = true;
			bool MousePassthrough = false;
		};
		//Context configuration
		struct ContextConfig
		{
			ContextAPI Client = ContextAPI::None;
			const InternalWindow* Share = nullptr;
		};		
		//Context structure
		struct Context
		{
			ContextAPI Client = ContextAPI::None;
			uint32_t Major = 0, Minor = 0;

			PFNGLGETSTRINGIPROC GetStringi = nullptr;
			PFNGLGETINTEGERVPROC GetIntegerv = nullptr;
			PFNGLGETSTRINGPROC  GetString = nullptr;

			MakeContextCurrentFunc MakeCurrent = nullptr;
			SwapBuffersFunc SwapBuffers = nullptr;
			SwapIntervalFunc SwapInterval = nullptr;
			ExtensionSupportedFunc ExtensionSupported = nullptr;
			GetProcAddressFunc GetProcAddress = nullptr;
			DestroyContextFunc Destroy = nullptr;

#ifdef TRAP_PLATFORM_WINDOWS
			HDC DC = nullptr;
			HGLRC Handle = nullptr;
			int32_t Interval = 0;
#endif
		};
		//Global state
		struct Data
		{
			bool Initialized = false;

			struct
			{
				FrameBufferConfig FrameBuffer{};
				WindowConfig Window{};
				ContextConfig Context{};
			} Hints{};

			Scope<WindowingError> ErrorListHead = nullptr;
			InternalWindow* WindowListHead = nullptr;
			InternalCursor* CursorListHead = nullptr;

			std::vector<Scope<InternalMonitor>> Monitors{};

			TLS ErrorSlot{};
			TLS ContextSlot{};
			Mutex ErrorLock{};

			struct
			{
				MonitorFunc Monitor = nullptr;
			} Callbacks{};

			struct
			{
				bool Available = false;
				void* Handle = nullptr;
				std::array<std::string, 2> Extensions{};
				bool KHR_Surface = false;
#if defined(TRAP_PLATFORM_WINDOWS)
				bool KHR_Win32_Surface = false;
#elif defined(TRAP_PLATFORM_LINUX_X11)
				bool KHR_XLib_Surface = false;
				bool KHR_XCB_Surface = false;
#elif defined(TRAP_PLATFORM_LINUX_WAYLAND)
				bool KHR_Wayland_Surface = false;
#endif
			} VK{};

#ifdef TRAP_PLATFORM_WINDOWS
			HWND HelperWindowHandle = nullptr;
			HDEVNOTIFY DeviceNotificationHandle = nullptr;
			DWORD ForegroundLockTimeout = 0;
			int32_t AcquiredMonitorCount = 0;
			std::string ClipboardString{};
			std::array<Input::Key, 512> KeyCodes{};
			std::array<int16_t, static_cast<uint32_t>(Input::Key::Menu) + 1> ScanCodes{};
			std::array<std::array<char, 5>, static_cast<uint32_t>(Input::Key::Menu) + 1> KeyNames{};
			//Where to place the cursor when re-enabled
			double RestoreCursorPosX = 0.0, RestoreCursorPosY = 0.0;
			//The window whose disabled cursor mode is active
			InternalWindow* DisabledCursorWindow = nullptr;
			std::vector<RAWINPUT> RawInput{};
			int32_t RawInputSize = 0;
			UINT MouseTrailSize = 0;

			struct
			{
				HINSTANCE Instance = nullptr;
				PFN_SetProcessDPIAware SetProcessDPIAware = nullptr;
				PFN_ChangeWindowMessageFilterEx ChangeWindowMessageFilterEx = nullptr;
				PFN_EnableNonClientDPIScaling EnableNonClientDPIScaling = nullptr;
				PFN_SetProcessDPIAwarenessContext SetProcessDPIAwarenessContext = nullptr;
				PFN_GetDPIForWindow GetDPIForWindow = nullptr;
				PFN_AdjustWindowRectExForDPI AdjustWindowRectExForDPI = nullptr;
			} User32;

			struct
			{
				HINSTANCE Instance = nullptr;
				PFN_DwmIsCompositionEnabled IsCompositionEnabled = nullptr;
				PFN_DwmFlush Flush = nullptr;
				PFN_DwmEnableBlurBehindWindow EnableBlurBehindWindow = nullptr;
			} DWMAPI_;

			struct
			{
				HINSTANCE Instance = nullptr;
				PFN_SetProcessDPIAwareness SetProcessDPIAwareness = nullptr;
				PFN_GetDPIForMonitor GetDPIForMonitor = nullptr;
			} SHCore;

			struct
			{
				HINSTANCE Instance = nullptr;
				PFN_RtlVerifyVersionInfo RtlVerifyVersionInfo = nullptr;
			} NTDLL;

			//WGL-specific global data
			struct
			{
				HINSTANCE Instance = nullptr;
				PFN_WGLCreateContext CreateContext = nullptr;
				PFN_WGLDeleteContext DeleteContext = nullptr;
				PFN_WGLGetProcAddress GetProcAddress = nullptr;
				PFN_WGLGetCurrentDC GetCurrentDC = nullptr;
				PFN_WGLGetCurrentContext GetCurrentContext = nullptr;
				PFN_WGLMakeCurrent MakeCurrent = nullptr;
				PFN_WGLShareLists ShareLists = nullptr;

				PFNWGLSWAPINTERVALEXTPROC SwapIntervalEXT = nullptr;
				PFNWGLGETPIXELFORMATATTRIBIVARBPROC GetPixelFormatAttribivARB = nullptr;
				PFNWGLGETEXTENSIONSSTRINGEXTPROC GetExtensionsStringEXT = nullptr;
				PFNWGLGETEXTENSIONSSTRINGARBPROC GetExtensionsStringARB = nullptr;
				PFNWGLCREATECONTEXTATTRIBSARBPROC CreateContextAttribsARB = nullptr;
				bool EXT_swap_control = false;
				bool ARB_multisample = false;
				bool ARB_framebuffer_sRGB = false;
				bool EXT_framebuffer_sRGB = false;
				bool ARB_pixel_format = false;
				bool ARB_create_context = false;
				bool ARB_create_context_profile = false;
				bool ARB_context_flush_control = false;
			} WGL;
#endif
		};
	public:
		//This describes a single video mode.
		struct VideoMode
		{
			//The width, in screen coordinates, of the video mode.
			int32_t Width = 0;
			//The height, in screen coordinates, of the video mode.
			int32_t Height = 0;
			//The bit depth of the red channel of the video mode.
			int32_t RedBits = 0;
			//The bit depth of the green channel of the video mode.
			int32_t GreenBits = 0;
			//The bit depth of the blue channel of the video mode.
			int32_t BlueBits = 0;
			//The refresh rate, in Hz, of the video mode.
			int32_t RefreshRate = 0;
		};
		//Monitor structure
		struct InternalMonitor
		{
			std::string Name{};

			//The window whose video mode is current on this monitor
			InternalWindow* Window = nullptr;

			std::vector<VideoMode> Modes{};
			VideoMode CurrentMode;

#ifdef TRAP_PLATFORM_WINDOWS
			HMONITOR Handle = nullptr;
			std::wstring AdapterName{};
			std::wstring DisplayName{};
			std::string PublicAdapterName{};
			std::string PublicDisplayName{};
			bool ModesPruned = false;
			bool ModeChanged = false;
#endif
		};
		//Cursor structure
		struct InternalCursor
		{
			InternalCursor* Next = nullptr;

#ifdef TRAP_PLATFORM_WINDOWS
			HCURSOR Handle = nullptr;
#endif
		};
		//Window and Context structure
		struct InternalWindow
		{
			InternalWindow* Next = nullptr;
			
			//Window settings and state
			bool Resizable = true;
			bool Decorated = true;
			bool Floating = false;
			bool ShouldClose = false;
			bool FocusOnShow = true;
			bool MousePassthrough = false;
			bool BorderlessFullscreen = false;
			void* UserPointer = nullptr;
			VideoMode VideoMode{};
			InternalMonitor* Monitor = nullptr;
			InternalCursor* Cursor = nullptr;

			int32_t MinWidth = -1, MinHeight = -1;
			int32_t MaxWidth = -1, MaxHeight = -1;

			CursorMode CursorMode = CursorMode::Normal;
			std::array<bool, 8> MouseButtons{};
			std::array<bool, 349 + 1> Keys{};
			//Virtual Cursor position when Cursor is disabled
			double VirtualCursorPosX = 0.0, VirtualCursorPosY = 0.0;
			bool RawMouseMotion = false;

			Context Context{};

			struct
			{
				WindowPositionFunc Pos = nullptr;
				WindowSizeFunc Size = nullptr;
				WindowCloseFunc Close = nullptr;
				WindowFocusFunc Focus = nullptr;
				FrameBufferSizeFunc FBSize = nullptr;
				WindowContentScaleFunc Scale = nullptr;
				MouseButtonFunc MouseButton = nullptr;
				CursorPositionFunc CursorPos = nullptr;
				CursorEnterFunc CursorEnter = nullptr;
				ScrollFunc Scroll = nullptr;
				KeyFunc Key = nullptr;
				CharFunc Character = nullptr;
				DropFunc Drop = nullptr;
			} Callbacks;

#ifdef TRAP_PLATFORM_WINDOWS
			HWND Handle = nullptr;
			HICON BigIcon = nullptr;
			HICON SmallIcon = nullptr;

			bool CursorTracked = false;
			bool FrameAction = false;
			bool Minimized = false;
			bool Maximized = false;

			//The last received cursor position, regardless of source
			int32_t LastCursorPosX = 0, LastCursorPosY = 0;
#endif
		};		
	private:
		//-------------------------------------------------------------------------------------------------------------------//
		//Static Members-----------------------------------------------------------------------------------------------------//
		//-------------------------------------------------------------------------------------------------------------------//
		static WindowingError s_MainThreadError;
		static ErrorFunc s_ErrorCallback;
		static Data s_Data;		
		//-------------------------------------------------------------------------------------------------------------------//
		//Platform Independent Functions-------------------------------------------------------------------------------------//
		//-------------------------------------------------------------------------------------------------------------------//
		//------//
		//Public//
		//------//
	public:
		//Initializes the Windowing API.
		static bool Init();
		//Shuts down the Windowing API.
		static void Shutdown();
		//Destroys the specified window and its context.
		static void DestroyWindow(Scope<InternalWindow> window);
		//Makes the context of the specified window current for the calling
		static void MakeContextCurrent(InternalWindow* window);
		//Resets all window hints to their default values.
		static void DefaultWindowHints();
		//Sets the specified window hint to the desired value.
		static void WindowHint(Hint hint, bool value);
		//Sets the specified sample count to the desired sample value.
		static void SetSamples(uint32_t samples); //TODO Implement for OpenGL MSAA
		//Sets the specified window context API to the desired value
		static void SetContextAPI(ContextAPI contextAPI);
		//Returns the name of the specified monitor.
		static std::string GetMonitorName(const InternalMonitor* monitor);
		//Returns the primary monitor.
		static const Scope<InternalMonitor>& GetPrimaryMonitor();
		//Returns the currently connected monitors.
		static std::vector<InternalMonitor*> GetMonitors();
		//Returns the current mode of the specified monitor.
		static const VideoMode& GetVideoMode(InternalMonitor* monitor);
		//Returns the available video modes for the specified monitor.
		static std::vector<VideoMode> GetVideoModes(InternalMonitor* monitor);
		//Creates a window and its associated context.
		//
		//Win32:   - Window creation will fail if the Microsoft GDI software OpenGL implementation is the only one available.
		//         - If the executable has an icon resource named 'TRAP_ICON', it will be set as the initial icon for the window.
		//           If no such icon is present, the 'IDI_APPLICATION' icon will be used instead.
		//X11:     - Some window managers will not respect the placement of initially hidden windows.
		//         - Due to the asynchronous nature of X11, it may take a moment for a window to reach its requested state.
		//           This means you may not be able to query the final size, position or other attributes directly after window creation.
		//         - The class part of the 'WM_CLASS' window property will by default be set to the window title passed to this function.
		//           The instance part will use the contents of the 'RESOURCE_NAME' environment variable, if present and not empty, or
		//           fall back to the window title.
		//Wayland: - Compositors should implement the xdg-decoration protocol for the WindowingAPI to decorate the window properly.
		//           If this protocol isn't supported, or if the compositor prefers client-side decorations, a very simple fallback
		//           frame will be drawn using the wp_viewporter protocol.
		//           A compositor can still emit close, maximize or fullscreen events, using for instance a keybind mechanism.
		//           If neither of these protocls are supported, the window won't be decorated.
		//         - A full screen window will not attempt to change the mode, no matter what the requested size or refresh rate.
		//         - Screensaver inhibition requires the idle-inhibit protocol to be implemented in the user's compositor.
		static Scope<InternalWindow> CreateWindow(uint32_t width, uint32_t height, const std::string& title, InternalMonitor* monitor, const InternalWindow* share);
		//Sets the close flag of the specified window.
		static void SetWindowShouldClose(InternalWindow* window, bool value);
		//Sets the title of the specified window.
		static void SetWindowTitle(const InternalWindow* window, const std::string& title);
		//Retrieves the content scale for the specified monitor.
		static void GetMonitorContentScale(const InternalMonitor* monitor, float& xScale, float& yScale);
		//Destroys a cursor.
		static void DestroyCursor(Scope<InternalCursor> cursor);
		//Creates a custom cursor.
		static Scope<InternalCursor> CreateCursor(const Scope<Image>& image, int32_t xHotspot, int32_t yHotspot);
		//Creates a cursor with a standard shape.
		static Scope<InternalCursor> CreateStandardCursor(const CursorType& type);
		//Sets the cursor for the window.
		static void SetCursor(InternalWindow* window, InternalCursor* cursor);
		//Sets the icon for the specified window.
		//
		//Wayland: - There is no existing protocol to change an icon, the window will thus inherit the one defined in the
		//           application's desktop file.
		static void SetWindowIcon(InternalWindow* window, const Scope<Image>& image);
		//Sets the position of the content area of the specified window.
		//
		//Wayland: - There is no way for an application to set the global position of its windows.
		static void SetWindowPos(const InternalWindow* window, int32_t xPos, int32_t yPos);
		//Retrieves the position of the content area of the specified window.
		//
		//Wayland: - There is no way for an application to retrieve the global position of its windows.
		static void GetWindowPos(const InternalWindow* window, int32_t& xPos, int32_t& yPos);
		//Sets the size of the content area of the specified window.
		//
		//Wayland: - A full screen window will not attempt to change the mode, no matter what the requested size.
		static void SetWindowSize(InternalWindow* window, int32_t width, int32_t height);
		//Retrieves the size of the content area of the specified window.
		static void GetWindowSize(const InternalWindow* window, int32_t& width, int32_t& height);
		//Retrieves the size of the framebuffer of the specified window.
		static void GetFrameBufferSize(const InternalWindow* window, int32_t& width, int32_t& height);
		//Sets the opacity of the whole window.
		static void SetWindowOpacity(const InternalWindow* window, float opacity);
		//Returns the opacity of the whole window.
		static float GetWindowOpacity(const InternalWindow* window);
		//Retrieves the content scale for the specified window.
		static void GetWindowContentScale(const InternalWindow* window, float& xScale, float& yScale);
		//Sets an attribute for the specified window.
		static void SetWindowAttrib(InternalWindow* window, Hint hint, bool value);
		//Returns an attribute of the specified window.
		static bool GetWindowAttrib(const InternalWindow* window, Hint hint);
		//Sets the mode, monitor, video mode and placement of a window.
		//
		//Wayland: - The desired window position is ignored, as there is no way for an application to set this property.
		//         - Setting the window to full screen will not attempt to change the mode, no matter what the
		//           requested size or refresh rate.
		static void SetWindowMonitor(InternalWindow* window,
		                             InternalMonitor* monitor,
		                             int32_t xPos,
		                             int32_t yPos,
		                             int32_t width,
		                             int32_t height,
		                             int32_t refreshRate);
		//Sets the mode, monitor and placement of a window.
		static void SetWindowMonitorBorderless(InternalWindow* window, InternalMonitor* monitor);
		//Sets the user pointer of the specified window.
		static void SetWindowUserPointer(InternalWindow* window, void* pointer);
		//Returns the user pointer of the specified window.
		static void* GetWindowUserPointer(const InternalWindow* window);
		//Sets the error callback.
		static void SetErrorCallback(ErrorFunc callback);
		//Sets the monitor configuration callback.
		static void SetMonitorCallback(MonitorFunc callback);
		//Sets the position callback for the specified window.
		//
		//Wayland: - This callback will never be called, as there is no way for an application to know its global position.
		static void SetWindowPosCallback(InternalWindow* window, WindowPositionFunc callback);
		//Sets the size callback for the specified window.
		static void SetWindowSizeCallback(InternalWindow* window, WindowSizeFunc callback);
		//Sets the close callback for the specified window.
		static void SetWindowCloseCallback(InternalWindow* window, WindowCloseFunc callback);
		//Sets the focus callback for the specified window.
		static void SetWindowFocusCallback(InternalWindow* window, WindowFocusFunc callback);
		//Sets the framebuffer resize callback for the specified window.
		static void SetFrameBufferSizeCallback(InternalWindow* window, FrameBufferSizeFunc callback);
		//Sets the window content scale callback for the specified window.
		static void SetWindowContentScaleCallback(InternalWindow* window, WindowContentScaleFunc callback);
		//Sets the key callback.
		static void SetKeyCallback(InternalWindow* window, KeyFunc callback);
		//Sets the Unicode character callback.
		static void SetCharCallback(InternalWindow* window, CharFunc callback);
		//Sets the mouse button callback.
		static void SetMouseButtonCallback(InternalWindow* window, MouseButtonFunc callback);
		//Sets the cursor position callback.
		static void SetCursorPosCallback(InternalWindow* window, CursorPositionFunc callback);
		//Sets the cursor enter callback.
		static void SetCursorEnterCallback(InternalWindow* window, CursorEnterFunc callback);
		//Sets the scroll callback.
		static void SetScrollCallback(InternalWindow* window, ScrollFunc callback);
		//Sets the path drop callback.
		static void SetDropCallback(InternalWindow* window, DropFunc callback);
		//Gets the error callback.
		static ErrorFunc GetErrorCallback();
		//Gets the monitor configuration callback.
		static MonitorFunc GetMonitorCallback();
		//Gets the position callback for the specified window.
		static WindowPositionFunc GetWindowPosCallback(const InternalWindow* window);
		//Gets the size callback for the specified window.
		static WindowSizeFunc GetWindowSizeCallback(const InternalWindow* window);
		//Gets the close callback for the specified window.
		static WindowCloseFunc GetWindowCloseCallback(const InternalWindow* window);
		//Gets the focus callback for the specified window.
		static WindowFocusFunc GetWindowFocusCallback(const InternalWindow* window);
		//Gets the framebuffer resize callback for the specified window.
		static FrameBufferSizeFunc GetFrameBufferSizeCallback(const InternalWindow* window);
		//Gets the window content scale callback for the specified window.
		static WindowContentScaleFunc GetWindowContentScaleCallback(const InternalWindow* window);
		//Gets the key callback.
		static KeyFunc GetKeyCallback(const InternalWindow* window);
		//Gets the Unicode character callback.
		static CharFunc GetCharCallback(const InternalWindow* window);
		//Gets the mouse button callback.
		static MouseButtonFunc GetMouseButtonCallback(const InternalWindow* window);
		//Gets the cursor position callback.
		static CursorPositionFunc GetCursorPosCallback(const InternalWindow* window);
		//Gets the cursor enter callback.
		static CursorEnterFunc GetCursorEnterCallback(const InternalWindow* window);
		//Gets the scroll callback.
		static ScrollFunc GetScrollCallback(const InternalWindow* window);
		//Gets the path drop callback.
		static DropFunc GetDropCallback(const InternalWindow* window);
		//Processes all pending events.
		static void PollEvents();
		//Sets the cursor mode for the specified window.
		static void SetCursorMode(InternalWindow* window, CursorMode mode);
		//Retrieves the cursor mode for the specified window.
		static CursorMode GetCursorMode(const InternalWindow* window);
		//Returns whether raw mouse motion is supported.
		static bool RawMouseMotionSupported();
		//Sets the raw mouse motion mode for the specified window.
		static void SetRawMouseMotionMode(InternalWindow* window, bool enabled);
		//Retrvieves the raw mouse motion mode for the specified window.
		static bool GetRawMouseMotionMode(const InternalWindow* window);
		//Returns the layout-specific name of the specified printable key.
		static const char* GetKeyName(Input::Key key, int32_t scanCode);
		//Returns the last reported state of a keyboard key for the specified window.
		static bool GetKey(const InternalWindow* window, Input::Key key);
		//Returns the last reported state of a mouse button for the specified window.
		static bool GetMouseButton(const InternalWindow* window, Input::MouseButton button);
		//Sets the position of the cursor, relative to the content area of the window
		//
		//Wayland: - This function will only work when the cursor mode is Disabled, otherwise it will do nothing.
		static void SetCursorPos(InternalWindow* window, double xPos, double yPos);
		//Retrieves the position of the cursor relative to the content area of the window.
		static void GetCursorPos(const InternalWindow* window, double& xPos, double& yPos);
		//Returns the position of the monitor's viewport on the virtual screen.
		static void GetMonitorPos(const InternalMonitor* monitor, int32_t& xPos, int32_t& yPos);
		//Retrieves the work area of the monitor.
		static void GetMonitorWorkArea(const InternalMonitor* monitor, int32_t& xPos, int32_t& yPos, int32_t& width, int32_t& height);
		//Makes the specified window visible.
		static void ShowWindow(const InternalWindow* window);
		//Brings the specified window to front and sets input focus.
		//
		//Wayland: - It is not possible for an application to bring its windows to front.
		static void FocusWindow(const InternalWindow* window);
		//Maximizes the specified window.
		static void MaximizeWindow(const InternalWindow* window);
		//Minimizes the specified window.
		//
		//Wayland: - Once a window is minimized, RestoreWindow won't be able to restore it.
		//           This is a design decision of the xdg-shell protocol.
		static void MinimizeWindow(const InternalWindow* window);
		//Requests user attention to the specified window.
		static void RequestWindowAttention(const InternalWindow* window);
		//Hides the specified window.
		static void HideWindow(const InternalWindow* window);
		//Restores the specified window.
		static void RestoreWindow(const InternalWindow* window);
		//Sets the size limits of the specified window.
		//
		//Wayland: The size limits will not be applied until the window is actually resized, either by the user or by the compositor.
		static void SetWindowSizeLimits(InternalWindow* window, int32_t minWidth, int32_t minHeight, int32_t maxWidth, int32_t maxHeight);
		//Sets the clipboard to the specified string.
		static void SetClipboardString(const std::string& string);
		//Returns the contents of the clipboard as a string.
		static std::string GetClipboardString();
		//Returns the window whose context is current on the calling thread.
		static InternalWindow* GetCurrentContext();
		//Swaps the front and back buffers of the specified window.
		static void SwapBuffers(InternalWindow* window);
		//Sets the swap interval for the current context.
		static void SwapInterval(int32_t interval);
		//Returns whether the specified extension is available.
		static bool ExtensionSupported(const std::string& extension);
		//Returns the address of the specified function for the current context.
		static GLProcess GetProcAddress(const char* procName);
		//Returns whether the Vulkan loader and an ICD have been found.
		static bool VulkanSupported();
		//Returns the Vulkan instance extensions required by TRAP.
		static std::array<std::string, 2> GetRequiredInstanceExtensions();
		//Creates a Vulkan surface for the specified window.
		static VkResult CreateWindowSurface(VkInstance instance, const InternalWindow* window, const VkAllocationCallbacks* allocator, VkSurfaceKHR& surface);
#ifdef TRAP_PLATFORM_WINDOWS
		static HWND GetWin32Window(const InternalWindow* window);
#endif
		//-------//
		//Private//
		//-------//
	private:
		//Checks whether the desired context attributes are valid
		static bool IsValidContextConfig(const ContextConfig& CTXConfig);
		//Center the cursor in the content area of the specified window
		static void CenterCursorInContentArea(InternalWindow* window);
		//Notifies shared code of an error
		static void InputError(Error code, const std::string& str);		
		//-------------------------------------------------------------------------------------------------------------------//
		//Platform Specific Functions----------------------------------------------------------------------------------------//
		//-------------------------------------------------------------------------------------------------------------------//
		//Create key code translation tables
		static void CreateKeyTables();
		
		static VideoMode PlatformGetVideoMode(const InternalMonitor* monitor);
		static void PlatformGetWindowSize(const InternalWindow* window, int32_t& width, int32_t& height);
		static void PlatformSetWindowPos(const InternalWindow* window, int32_t xPos, int32_t yPos);
		static void PlatformGetWindowFrameSize(const InternalWindow* window,
			                                   int32_t& left, int32_t& top,
			                                   int32_t& right, int32_t& bottom);
		static void PlatformSetWindowMonitor(InternalWindow* window, InternalMonitor* monitor,
			                                 int32_t xPos, int32_t yPos, int32_t width, int32_t height, int32_t refreshRate);
		static void PlatformSetWindowMonitorBorderless(InternalWindow* window, InternalMonitor* monitor);
		static std::vector<VideoMode> PlatformGetVideoModes(const InternalMonitor* monitor);
		static bool PlatformInit();
		static bool PlatformCreateMutex(Mutex& mutex); 
		static bool PlatformCreateTLS(TLS& tls);
		static void PlatformSetTLS(TLS& tls, void* value);
		static void* PlatformGetTLS(TLS& tls);
		static void PlatformDestroyTLS(TLS& tls);
		static void PlatformDestroyMutex(Mutex& mutex);
		static void PlatformLockMutex(Mutex& mutex);
		static void PlatformUnlockMutex(Mutex& mutex);
		static void PlatformDestroyWindow(InternalWindow* window);
		static void PlatformShutdown();
		static void PlatformGetMonitorContentScale(const InternalMonitor* monitor, float& xScale, float& yScale);
		static void PlatformGetMonitorPos(const InternalMonitor* monitor, int32_t& xPos, int32_t& yPos);
		static void PlatformShowWindow(const InternalWindow* window);
		static void PlatformFocusWindow(const InternalWindow* window);
		static bool PlatformCreateWindow(InternalWindow* window,
			                             const WindowConfig& WNDConfig,
			                             const ContextConfig& CTXConfig,
			                             const FrameBufferConfig& FBConfig);
		static void PlatformSetWindowTitle(const InternalWindow* window, const std::string& title);
		static bool PlatformCreateCursor(InternalCursor* cursor, const Scope<Image>& image, int32_t xHotspot, int32_t yHotspot);
		static bool PlatformCreateStandardCursor(InternalCursor* cursor, const CursorType& type);
		static void PlatformDestroyCursor(InternalCursor* cursor);
		static void PlatformSetCursor(const InternalWindow* window, const InternalCursor* cursor);
		static void PlatformSetCursorMode(InternalWindow* window, CursorMode mode);
		static void PlatformSetCursorPos(InternalWindow* window, double xPos, double yPos);
		static void PlatformGetCursorPos(const InternalWindow* window, double& xPos, double& yPos);
		static void PlatformSetWindowIcon(InternalWindow* window, const Scope<Image>& image);
		static void PlatformGetWindowPos(const InternalWindow* window, int32_t& xPos, int32_t& yPos);
		static void PlatformSetWindowSize(InternalWindow* window, int32_t width, int32_t height);
		static void PlatformSetWindowResizable(const InternalWindow* window, bool enabled);
		static void PlatformSetWindowDecorated(const InternalWindow* window, bool enabled);
		static void PlatformSetWindowFloating(const InternalWindow* window, bool enabled);
		static void PlatformSetWindowOpacity(const InternalWindow* window, float opacity);
		static void PlatformSetWindowMousePassthrough(InternalWindow* window, bool enabled);
		static float PlatformGetWindowOpacity(const InternalWindow* window);
		static void PlatformGetFrameBufferSize(const InternalWindow* window, int32_t& width, int32_t& height);
		static void PlatformGetWindowContentScale(const InternalWindow* window, float& xScale, float& yScale);
		static void PlatformGetMonitorWorkArea(const InternalMonitor* monitor, int32_t& xPos, int32_t& yPos, int32_t& width, int32_t& height);
		static bool PlatformWindowVisible(const InternalWindow* window);
		static bool PlatformWindowMaximized(const InternalWindow* window);
		static bool PlatformWindowMinimized(const InternalWindow* window);
		static void PlatformPollEvents();
		static bool PlatformWindowFocused(const InternalWindow* window);
		static bool PlatformWindowHovered(const InternalWindow* window);
		static bool PlatformRawMouseMotionSupported();
		static void PlatformSetRawMouseMotion(const InternalWindow* window, bool enabled);
		static int32_t PlatformGetKeyScanCode(Input::Key key);
		static const char* PlatformGetScanCodeName(int32_t scanCode);
		static void PlatformSetClipboardString(const std::string& string);
		static std::string PlatformGetClipboardString();
		static void PlatformGetRequiredInstanceExtensions(std::array<std::string, 2>& extensions);
		static VkResult PlatformCreateWindowSurface(VkInstance instance, const InternalWindow* window,
			                                        const VkAllocationCallbacks* allocator, VkSurfaceKHR& surface);
		static void PlatformMaximizeWindow(const InternalWindow* window);
		static void PlatformMinimizeWindow(const InternalWindow* window);
		static void PlatformRequestWindowAttention(const InternalWindow* window);
		static void PlatformHideWindow(const InternalWindow* window);
		static void PlatformRestoreWindow(const InternalWindow* window);
		static void PlatformSetWindowSizeLimits(const InternalWindow* window, int32_t minWidth, int32_t minHeight, int32_t maxWidth, int32_t maxHeight);
		//-------------------------------------------------------------------------------------------------------------------//
		//Single Platform Functions------------------------------------------------------------------------------------------//
		//-------------------------------------------------------------------------------------------------------------------//
		//-------//
		//Windows//
		//-------//		
#ifdef TRAP_PLATFORM_WINDOWS
		//Replacement for IsWindowsVersionOrGreater as MinGW lacks versionhelpers.h
		static BOOL IsWindowsVersionOrGreaterWin32(WORD major, WORD minor, WORD sp);
		//Checks whether we are on at least the specified build of Windows 10
		static BOOL IsWindows10BuildOrGreaterWin32(WORD build);
		//Checks whether we are on at least Windows 10 Anniversary Update
		static BOOL IsWindows10AnniversaryUpdateOrGreaterWin32();
		//Checks whether we are on at least Windows 10 Creators Update
		static BOOL IsWindows10CreatorsUpdateOrGreaterWin32();
		//Checks whether we are on at least Windows 8.1
		static BOOL IsWindows8Point1OrGreaterWin32();
		//Checks whether we are on at least Windows 8
		static BOOL IsWindows8OrGreaterWin32();
		//Checks whether we are on at least Windows 7
		static BOOL IsWindows7OrGreaterWin32();
		//Checks whether we are on at least Windows Vista
		static BOOL IsWindowsVistaOrGreaterWin32();
		//Checks whether we are on at least Windows XP
		static BOOL IsWindowsXPOrGreaterWin32();
		//Returns an UTF-8 string version of the specified wide string
		static std::string CreateUTF8StringFromWideStringWin32(const std::wstring& wStr);
		//Returns a wide string string version of the specified UTF-8 string
		static std::wstring CreateWideStringFromUTF8StringWin32(const std::string& str);
		//Load necessary libraries (DLLs)
		static bool LoadLibraries();
		//Unload used libraries (DLLs)
		static void FreeLibraries();
		//Reports the specified error, appending information about the last Win32 error
		static void InputErrorWin32(Error error, std::string description);
		//Notifies shared code of a mouse button click event
		static void InputMouseClick(InternalWindow* window, Input::MouseButton button, bool pressed);
		//Notifies shared code that a window has lost or received input focus
		static void InputWindowFocus(InternalWindow* window, bool focused);
		//Notifies shared code of a Unicode codepoint input event
		//The 'plain' parameter determines whether to emit a regular character event
		static void InputChar(const InternalWindow* window, uint32_t codePoint);
		//Notifies shared code of a cursor motion event
		//The position is specified in content area relative screen coordinates
		static void InputCursorPos(InternalWindow* window, double xPos, double yPos);
		//Notified shared code of a cursor enter/leave event
		static void InputCursorEnter(InternalWindow* window, bool entered);
		//Notifies shared code of a scroll event
		static void InputScroll(const InternalWindow* window, double xOffset, double yOffset);
		//Notifies shared code that a window framebuffer has been resized
		//The size is specified in pixels
		static void InputFrameBufferSize(const InternalWindow* window, int32_t width, int32_t height); 
		//Notifies shared code that a window has been resized
		//The size is specified in screen coordinates
		static void InputWindowSize(const InternalWindow* window, int32_t width, int32_t height);
		//Notifies shared code that a window has moved
		//The position is specified in content area relative screen coordinates
		static void InputWindowPos(const InternalWindow* window, int32_t x, int32_t y);
		//Notifies shared code that a window content scale has changed
		//The scale is specified as the ratio between the current and default DPI
		static void InputWindowContentScale(const InternalWindow* window, float xScale, float yScale);
		//Notifies shared code of files or directories dropped on a window
		static void InputDrop(const InternalWindow* window, const std::vector<std::string>& paths);
		//Translates a Windows key to the corresponding TRAP key
		static Input::Key TranslateKey(WPARAM wParam, LPARAM lParam);
		//Updates key names according to the current keyboard layout
		static void UpdateKeyNamesWin32();
		//Window callback function (handles window messages)
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		//Registers the TRAP window class
		static bool RegisterWindowClassWin32();
		//Unregisters the TRAP window class
		static void UnregisterWindowClassWin32();
		//Callback for EnumDisplayMonitors in createMonitor
		static BOOL CALLBACK MonitorCallback(HMONITOR handle, HDC dc, RECT* rect, LPARAM data);
		//Create monitor from an adapter and (optionally) a display
		static Scope<InternalMonitor> CreateMonitor(DISPLAY_DEVICEW* adapter, DISPLAY_DEVICEW* display);
		//Notifies shared code of a monitor connection or disconnection
		static void InputMonitor(Scope<InternalMonitor> monitor, bool connected, uint32_t placement);
		//Notifies shared code of a monitor connection or disconnection
		static void InputMonitorDisconnect(uint32_t monitorIndex, uint32_t placement);
		//Poll for changes in the set of connected monitors
		static void PollMonitorsWin32();
		//Make the specified window and its video mode active on its monitor
		static void AcquireMonitor(InternalWindow* window);
		//Make the specified window active on its monitor
		static void AcquireMonitorBorderless(InternalWindow* window);
		//Remove the window and restore the original video mode
		static void ReleaseMonitor(const InternalWindow* window);
		static void FitToMonitor(const InternalWindow* window);
		//Lexically compare video modes, used by qsort
		static int32_t CompareVideoModes(const void* fp, const void* sp);
		//Retrieves the available modes for the specified monitor
		static bool RefreshVideoModes(InternalMonitor* monitor);
		//Chooses the video mode most closely matching the desired one
		static VideoMode* ChooseVideoMode(InternalMonitor* monitor, const VideoMode& desired);
		//Change the current video mode
		static void SetVideoModeWin32(InternalMonitor* monitor, const VideoMode& desired);
		static void GetMonitorContentScaleWin32(HMONITOR handle, float& xScale, float& yScale);
		//Splits a color depth into red, green and blue bit depths
		static void SplitBPP(int32_t bpp, int32_t& red, int32_t& green, int32_t& blue);
		//Returns the window style for the specified window
		static DWORD GetWindowStyle(const InternalWindow* window);
		//Returns the extended window style for the specified window
		static DWORD GetWindowExStyle(const InternalWindow* window);
		//Creates the TRAP window
		static int32_t CreateNativeWindow(InternalWindow* window,
			                              const WindowConfig& WNDConfig,
			                              const FrameBufferConfig& FBConfig);
		//Creates a dummy window for behind-the-scenes work
		static bool CreateHelperWindow();
		//Translate content area size to full window size according to styles and DPI
		static void GetFullWindowSize(DWORD style, DWORD exStyle,
			                          int32_t contentWidth, int32_t contentHeight,
			                          int32_t& fullWidth, int32_t& fullHeight,
			                          UINT dpi);		
		static bool InitWGL();
		//Shutdown WGL
		static void ShutdownWGL();
		static bool CreateContextWGL(InternalWindow* window,
			                         const ContextConfig& CTXConfig,
			                         const FrameBufferConfig& FBConfig);
		static void DestroyContextWGL( InternalWindow* window);
		static void MakeContextCurrentWGL(InternalWindow* window);
		static void SwapBuffersWGL(const InternalWindow* window);
		static void SwapIntervalWGL(int32_t interval);
		static GLProcess GetProcAddressWGL(const char* procName);
		static bool ExtensionSupportedWGL(const char* extension);		
		//Searches an extension string for the specified extension
		static bool StringInExtensionString(const char* string, const char* extensions);
		//Return the value corresponding to the specified attribute
		static int32_t FindPixelFormatAttribValue(const std::vector<int32_t>& attribs,
			                                      const std::vector<int32_t>& values,
			                                      int32_t attrib);
		//Chooses the framebuffer config that best matches the desired one
		static const FrameBufferConfig* ChooseFBConfig(const FrameBufferConfig& desired,
			                                           const std::vector<FrameBufferConfig>& alternatives);
		//Returns a list of available and usable framebuffer configs
		static int32_t ChoosePixelFormat(const InternalWindow* window,
			                             const ContextConfig& CTXConfig,
			                             const FrameBufferConfig& FBConfig);		
		static bool RefreshContextAttribs(InternalWindow* window,
			                              const ContextConfig& CTXConfig);
		//Returns whether the cursor is in the content area of the specified window
		static bool CursorInContentArea(const InternalWindow* window);
		//Updates the cursor image according to its cursor mode
		static void UpdateCursorImage(const InternalWindow* window);
		//Creates an RGBA icon or cursor
		static HICON CreateIcon(const Scope<Image>& image, int32_t xHot, int32_t yHot, bool icon);
		//Notifies shared code that the user wishes to close a window
		static void InputWindowCloseRequest(InternalWindow* window);
		//Notifies shared code of a physical key event
		static void InputKey(InternalWindow* window, Input::Key key, int32_t scancode, bool action);
		//Updates the cursor clip rect
		static void UpdateClipRect(const InternalWindow* window);
		//Enables WM_INPUT messages for the mouse for the specified window
		static void EnableRawMouseMotion(const InternalWindow* window);
		//Disables WM_INPUT messages for the mouse
		static void DisableRawMouseMotion(const InternalWindow* window);
		//Exit disabled cursor mode for the specified window
		static void EnableCursor(InternalWindow* window);
		//Apply disabled cursor mode to a focused window
		static void DisableCursor(InternalWindow* window);
		//Update native window styles to match attributes
		static void UpdateWindowStyles(const InternalWindow* window);
		static bool InitVulkan(uint32_t mode);
		static std::string GetVulkanResultString(VkResult result);
#endif
	};
}
#endif /*_TRAP_WINDOWINGAPI_H_*/