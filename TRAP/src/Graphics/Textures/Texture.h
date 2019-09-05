#ifndef _TRAP_TEXTURE_H_
#define _TRAP_TEXTURE_H_

#include "ImageLoader/Image.h"

namespace TRAP::Graphics
{
	enum class TextureWrap
	{
		NONE = 0,
		Repeat,
		Mirrored_Repeat,
		Clamp_To_Edge,
		Clamp_To_Border
	};

	enum class TextureFilter
	{
		None = 0,
		Linear,
		Nearest
	};

	enum class TextureType
	{
		Texture2D,
		TextureCube
	};

	struct TextureParameters
	{
		TextureFilter Filter;
		TextureWrap Wrap;

		TextureParameters()
			: Filter(TextureFilter::Nearest), Wrap(TextureWrap::Clamp_To_Edge)
		{
		}
		explicit TextureParameters(const TextureFilter filter)
			: Filter(filter), Wrap(TextureWrap::Clamp_To_Edge)
		{
		}
		TextureParameters(const TextureFilter filter, const TextureWrap wrap)
			: Filter(filter), Wrap(wrap)
		{
		}
	};

	class Texture
	{
	public:
		Texture() = default;
		virtual ~Texture() = default;
		Texture(const Texture&) = default;
		Texture& operator=(const Texture&) = default;
		Texture(Texture&&) = default;
		Texture& operator=(Texture&&) = default;

		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual void Unbind(uint32_t slot = 0) const = 0;

		virtual std::string GetName() const = 0;
		virtual TextureType GetType() const = 0;
		virtual Image* GetImage() = 0;
		virtual TextureParameters GetParameters() = 0;

		virtual void SetWrap(TextureWrap wrap) = 0;
		virtual void SetFilter(TextureFilter filter) = 0;

		static uint8_t GetStrideFromFormat(ImageFormat format);

		static uint32_t TRAPImageFormatToOpenGL(ImageFormat format);
		static uint32_t TRAPImageFormatToOpenGLPrecise(ImageFormat format, uint32_t bytesPerPixel);
		static uint32_t TRAPTextureWrapToOpenGL(TextureWrap wrap);
	};
}

#endif /*_TRAP_TEXTURE_H_*/