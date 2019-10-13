#include "TRAPPCH.h"
#include "D3D12Texture2D.h"

#include "VFS/VFS.h"

TRAP::Graphics::API::D3D12Texture2D::D3D12Texture2D(const TextureParameters parameters)
	: /*m_image(Image::LoadFallback()),*/ m_name("Fallback"), m_parameters(parameters), m_handle(0)
{
	TP_WARN("[Texture2D][D3D12] WIP");
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Graphics::API::D3D12Texture2D::D3D12Texture2D(const ImageFormat format, const uint32_t width, const uint32_t height, const TextureParameters parameters)
	: /*m_image(Image::CreateEmpty(format, width, height)),*/ m_name("Empty"), m_parameters(parameters), m_handle(0)
{
	TP_WARN("[Texture2D][D3D12] WIP");
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Graphics::API::D3D12Texture2D::D3D12Texture2D(std::string name, const std::string& filepath, const TextureParameters parameters)
	: m_filePath(VFS::MakeVirtualPathCompatible(filepath)), m_name(std::move(name)), m_parameters(parameters), m_handle(0)
{
	TP_WARN("[Texture2D][D3D12] WIP");
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Graphics::API::D3D12Texture2D::~D3D12Texture2D() = default;

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::D3D12Texture2D::Bind(const uint32_t slot) const
{
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::D3D12Texture2D::Unbind(const uint32_t slot) const
{
}

//-------------------------------------------------------------------------------------------------------------------//

std::string TRAP::Graphics::API::D3D12Texture2D::GetName() const
{
	return m_name;
}

//-------------------------------------------------------------------------------------------------------------------//

/*TRAP::Image* TRAP::Graphics::API::D3D12Texture2D::GetImage()
{
	return m_image.get();
}*/

std::string TRAP::Graphics::API::D3D12Texture2D::GetFilePath() const
{
	return m_filePath;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Graphics::TextureParameters TRAP::Graphics::API::D3D12Texture2D::GetParameters()
{
	return m_parameters;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::D3D12Texture2D::SetWrap(const TextureWrap wrap)
{
	m_parameters.Wrap = wrap;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::Graphics::API::D3D12Texture2D::SetFilter(const TextureFilter filter)
{
	m_parameters.Filter = filter;
}