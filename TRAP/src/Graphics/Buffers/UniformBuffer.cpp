#include "TRAPPCH.h"
#include "UniformBuffer.h"

#include "Graphics/API/Context.h"
#include "Graphics/API/Vulkan/Buffers/VulkanUniformBuffer.h"
#include "Graphics/API/OpenGL/Buffers/OpenGLUniformBuffer.h"

TRAP::Scope<TRAP::Graphics::UniformBuffer> TRAP::Graphics::UniformBuffer::Create(const char* name, uint32_t size, BufferUsage usage)
{
	TP_PROFILE_FUNCTION();

	switch (API::Context::GetRenderAPI())
	{
	case API::RenderAPI::Vulkan:
		return MakeScope<API::VulkanUniformBuffer>(name, size, usage);

	case API::RenderAPI::OpenGL:
		return MakeScope<API::OpenGLUniformBuffer>(name, size, usage);

	default:
		//Shouldn't be reached
		return nullptr;
	}
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Scope<TRAP::Graphics::UniformBuffer> TRAP::Graphics::UniformBuffer::Create(const char* name, void* data, uint32_t size, BufferUsage usage)
{
	TP_PROFILE_FUNCTION();

	switch (API::Context::GetRenderAPI())
	{

	case API::RenderAPI::Vulkan:
		return MakeScope<API::VulkanUniformBuffer>(name, data, size, usage);

	case API::RenderAPI::OpenGL:
		return MakeScope<API::OpenGLUniformBuffer>(name, data, size, usage);

	default:
		//Shouldn't be reached
		return nullptr;
	}
}