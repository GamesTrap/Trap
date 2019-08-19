#ifndef _TRAP_TGAIMAGE_H_
#define _TRAP_TGAIMAGE_H_

#include "TRAPPCH.h"
#include "ImageLoader/Image.h"

namespace TRAP::INTERNAL
{
	class TGAImage final : public Image
	{
	public:
		explicit TGAImage(std::string filepath);

		void* GetPixelData() override;
		uint32_t GetPixelDataSize() const override;
		uint32_t GetBitsPerPixel() const override;
		uint32_t GetBytesPerPixel() const override;
		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;
		bool HasAlphaChannel() const override;
		bool IsImageCompressed() const override;
		bool IsImageGrayScale() const override;
		bool IsImageColored() const override;
		bool IsHDR() const override; //TGA Spec???
		std::string GetFilePath() const override;
		ImageFormat GetFormat() const override;

	private:
		std::string m_filepath;
		uint32_t m_bitsPerPixel;
		uint32_t m_width;
		uint32_t m_height;
		bool m_isImageGrayScale;
		bool m_isImageColored;
		bool m_isImageCompressed;
		bool m_hasAlphaChannel;
		ImageFormat m_imageFormat;
		std::vector<uint8_t> m_data;
	};
}

#endif /*_TRAP_TGAIMAGE_H_*/