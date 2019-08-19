#include "TRAPPCH.h"
#include "DefaultImage.h"

TRAP::INTERNAL::DefaultImage::DefaultImage(std::string filepath)
	: m_filepath(std::move(filepath))
{
}

//-------------------------------------------------------------------------------------------------------------------//

void* TRAP::INTERNAL::DefaultImage::GetPixelData()
{
	return defaultImageData.data();
}

//-------------------------------------------------------------------------------------------------------------------//

uint32_t TRAP::INTERNAL::DefaultImage::GetPixelDataSize() const
{
	return static_cast<uint32_t>(defaultImageData.size());
}

//-------------------------------------------------------------------------------------------------------------------//

uint32_t TRAP::INTERNAL::DefaultImage::GetBitsPerPixel() const
{
	return 32;
}

//-------------------------------------------------------------------------------------------------------------------//

uint32_t TRAP::INTERNAL::DefaultImage::GetBytesPerPixel() const
{
	return 4;
}

//-------------------------------------------------------------------------------------------------------------------//

uint32_t TRAP::INTERNAL::DefaultImage::GetWidth() const
{
	return 32;
}

//-------------------------------------------------------------------------------------------------------------------//

uint32_t TRAP::INTERNAL::DefaultImage::GetHeight() const
{
	return 32;
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::INTERNAL::DefaultImage::HasAlphaChannel() const
{
	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::INTERNAL::DefaultImage::IsImageCompressed() const
{
	return false;
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::INTERNAL::DefaultImage::IsImageGrayScale() const
{
	return false;
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::INTERNAL::DefaultImage::IsImageColored() const
{
	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

bool TRAP::INTERNAL::DefaultImage::IsHDR() const
{
	return false;
}

//-------------------------------------------------------------------------------------------------------------------//

std::string TRAP::INTERNAL::DefaultImage::GetFilePath() const
{
	return m_filepath;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::ImageFormat TRAP::INTERNAL::DefaultImage::GetFormat() const
{
	return ImageFormat::RGBA;
}