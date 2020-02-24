#include "TRAPPCH.h"

#include "VulkanFrameBuffer2D.h"

TRAP::Graphics::API::VulkanFrameBuffer2D::VulkanFrameBuffer2D(const uint32_t width, const uint32_t height)
	: m_width(width), m_height(height), m_clearColor(0.1f, 0.1f, 0.1f, 1.0f), m_texture(nullptr)
{
	TP_PROFILE_FUNCTION();

	TP_WARN("[FrameBuffer2D][Vulkan] WIP");
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Graphics::API::VulkanFrameBuffer2D::~VulkanFrameBuffer2D()
{
	TP_PROFILE_FUNCTION();
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanFrameBuffer2D::Bind() const
{
	TP_PROFILE_FUNCTION();
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanFrameBuffer2D::Unbind() const
{
	TP_PROFILE_FUNCTION();
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanFrameBuffer2D::Clear()
{
	TP_PROFILE_FUNCTION();
}

//-------------------------------------------------------------------------------------------------------------------//

uint32_t TRAP::Graphics::API::VulkanFrameBuffer2D::GetWidth() const
{
	TP_PROFILE_FUNCTION();
	
	return m_width;
}

//-------------------------------------------------------------------------------------------------------------------//

uint32_t TRAP::Graphics::API::VulkanFrameBuffer2D::GetHeight() const
{
	TP_PROFILE_FUNCTION();

	return m_height;
}

//-------------------------------------------------------------------------------------------------------------------//

const TRAP::Scope<TRAP::Graphics::Texture>& TRAP::Graphics::API::VulkanFrameBuffer2D::GetTexture() const
{
	TP_PROFILE_FUNCTION();

	return dynamic_cast<const Scope<Texture>&>(m_texture);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanFrameBuffer2D::SetClearColor(const Math::Vec4& color)
{
	TP_PROFILE_FUNCTION();

	m_clearColor = color;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::VulkanFrameBuffer2D::Init()
{
}