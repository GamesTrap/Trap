#ifndef _TRAP_CONTEXT_H_
#define _TRAP_CONTEXT_H_

namespace TRAP
{
	class Window;
}

namespace TRAP::Graphics::API
{
	enum class RenderAPI
	{
		NONE = 0,
		OpenGL,
		D3D12,
		Vulkan
	};

	class Context
	{
	public:
		Context() = default;
		virtual ~Context() = default;
		Context(const Context&) = default;
		Context& operator=(const Context&) = default;
		Context(Context&&) = default;
		Context& operator=(Context&&) = default;

		static void Create(Window* window);
		static void Shutdown();

		static void AutoSelectRenderAPI();
		static void CheckAllRenderAPIs();
		static RenderAPI GetRenderAPI();
		static void SetRenderAPI(RenderAPI api);
		static void SwitchRenderAPI(RenderAPI api);

		static bool IsSupported(RenderAPI api);
		static bool IsD3D12Capable();
		static bool IsVulkanCapable();
		static bool IsOpenGLCapable();

		static void SetVSyncInterval(uint32_t interval);

		static void Use(const std::unique_ptr<Window>& window);

		static RenderAPI s_newRenderAPI;
	protected:
		static Scope<Context> s_Context;
		static RenderAPI s_RenderAPI;

	private:
		virtual void SetVSyncIntervalInternal(uint32_t interval = 0) = 0;
		virtual void UseInternal(const std::unique_ptr<Window>& window) = 0;

		static bool s_isD3D12Capable;
		static bool s_isVulkanCapable;
		static bool s_isOpenGLCapable;
	};
}

//-------------------------------------------------------------------------------------------------------------------//

inline TRAP::Graphics::API::RenderAPI TRAP::Graphics::API::Context::GetRenderAPI()
{	
	return s_RenderAPI;
}

//-------------------------------------------------------------------------------------------------------------------//

inline void TRAP::Graphics::API::Context::SetVSyncInterval(const uint32_t interval)
{
	if (s_Context) s_Context->SetVSyncIntervalInternal(interval);
}

//-------------------------------------------------------------------------------------------------------------------//

inline void TRAP::Graphics::API::Context::Use(const std::unique_ptr<Window>& window)
{
	if (s_Context)
		if (window)
			s_Context->UseInternal(window);
}

//-------------------------------------------------------------------------------------------------------------------//

inline bool TRAP::Graphics::API::Context::IsD3D12Capable()
{
	return s_isD3D12Capable;
}

//-------------------------------------------------------------------------------------------------------------------//

inline bool TRAP::Graphics::API::Context::IsVulkanCapable()
{
	return s_isVulkanCapable;
}

//-------------------------------------------------------------------------------------------------------------------//

inline bool TRAP::Graphics::API::Context::IsOpenGLCapable()
{
	return s_isOpenGLCapable;
}

#endif /*_TRAP_CONTEXT_H_*/