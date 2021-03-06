#include "TRAPPCH.h"
#include "Context.h"

#include "OpenGL/OpenGLContext.h"
#include "Vulkan/VulkanContext.h"
#include "Utils/Dialogs/MsgBox.h"

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Scope<TRAP::Graphics::API::Context> TRAP::Graphics::API::Context::s_Context = nullptr;
TRAP::Graphics::API::RenderAPI TRAP::Graphics::API::Context::s_RenderAPI = RenderAPI::NONE;
TRAP::Graphics::API::RenderAPI TRAP::Graphics::API::Context::s_newRenderAPI = RenderAPI::NONE;

bool TRAP::Graphics::API::Context::s_isVulkanCapable = false;
bool TRAP::Graphics::API::Context::s_isOpenGLCapable = false;

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::Context::Create(Window* window)
{
	TP_PROFILE_FUNCTION();

	switch (GetRenderAPI())
	{
	case RenderAPI::OpenGL:
		TP_INFO(Log::ContextOpenGLPrefix, "Initializing Context");
		s_Context = MakeScope<OpenGLContext>(window);
		break;

	case RenderAPI::Vulkan:
		TP_INFO(Log::ContextVulkanPrefix, "Initializing Context");
		s_Context = MakeScope<VulkanContext>(window);
		break;

	default:
		//This should never be reached.
		TP_CRITICAL(Log::EnginePrefix, "Unsupported Device!");
		Utils::Dialogs::MsgBox::Show("Device is unsupported!\nNo RenderAPI selected!", "Unsupported Device", Utils::Dialogs::MsgBox::Style::Error, Utils::Dialogs::MsgBox::Buttons::Quit);
		exit(-1);
	}
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::Context::Shutdown()
{
	TP_PROFILE_FUNCTION();

	s_Context.reset();
	s_Context = nullptr;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::Context::AutoSelectRenderAPI()
{
	TP_PROFILE_FUNCTION();
	
	TP_INFO(Log::ContextPrefix, "Auto selecting RenderAPI");

	//Check if Vulkan capable
	if (s_isVulkanCapable)
	{
		SetRenderAPI(RenderAPI::Vulkan);
		return;
	}
	TP_DEBUG(Log::ContextVulkanPrefix, "Device isn't Vulkan 1.2 capable!");


	if (s_isOpenGLCapable)
	{
		SetRenderAPI(RenderAPI::OpenGL);
		return;
	}
	TP_DEBUG(Log::ContextOpenGLPrefix, "Device isn't OpenGL 4.6 capable!");

	SetRenderAPI(RenderAPI::NONE);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::Context::CheckAllRenderAPIs()
{
	TP_PROFILE_FUNCTION();

	//Check if Vulkan 1.2 capable
	s_isVulkanCapable = VulkanContext::IsVulkanCapable();

	//Check if OpenGL 4.6 capable
	s_isOpenGLCapable = OpenGLContext::IsOpenGLCapable();
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Graphics::API::RenderAPI TRAP::Graphics::API::Context::GetRenderAPI()
{
	TP_PROFILE_FUNCTION();

	return s_RenderAPI;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::Context::SetRenderAPI(const RenderAPI api)
{
	TP_PROFILE_FUNCTION();

	s_RenderAPI = api;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::Context::SwitchRenderAPI(const RenderAPI api)
{
	TP_PROFILE_FUNCTION();
	
	if (api != s_RenderAPI)
	{
		if (api == RenderAPI::Vulkan)
		{
			if (s_isVulkanCapable)
			{
				TP_WARN(Log::ContextPrefix, "Switching RenderAPI to Vulkan 1.2");
				s_newRenderAPI = RenderAPI::Vulkan;

				return;
			}

			TP_ERROR(Log::ContextVulkanPrefix, "This device doesn't support Vulkan 1.2!");
			if (s_isOpenGLCapable)
			{
				SwitchRenderAPI(RenderAPI::OpenGL);
				return;
			}

			return;
		}

		if (api == RenderAPI::OpenGL)
		{
			if (s_isOpenGLCapable)
			{
				TP_WARN(Log::ContextPrefix, "Switching RenderAPI to OpenGL 4.6");
				s_newRenderAPI = RenderAPI::OpenGL;

				return;
			}

			TP_ERROR(Log::ContextOpenGLPrefix, "This device doesn't support OpenGL 4.6!");
			if (s_isVulkanCapable)
				SwitchRenderAPI(RenderAPI::Vulkan);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::Graphics::API::Context::IsSupported(const RenderAPI api)
{
	TP_PROFILE_FUNCTION();

	if (api == RenderAPI::Vulkan)
		if (s_isVulkanCapable)
			return true;

	if (api == RenderAPI::OpenGL)
		if (s_isOpenGLCapable)
			return true;

	return false;
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::Graphics::API::Context::IsVulkanCapable()
{
	TP_PROFILE_FUNCTION();

	return s_isVulkanCapable;
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::Graphics::API::Context::IsOpenGLCapable()
{
	TP_PROFILE_FUNCTION();

	return s_isOpenGLCapable;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::Context::SetVSyncInterval(const uint32_t interval)
{
	TP_PROFILE_FUNCTION();

	if (s_Context) 
		s_Context->SetVSyncIntervalInternal(interval);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::Context::Use(Window* window)
{
	TP_PROFILE_FUNCTION();

	if (s_Context && window)
		s_Context->UseInternal(window);
}