#ifndef _TRAP_PPMIMAGE_H_
#define _TRAP_PPMIMAGE_H_

#include "ImageLoader/Image.h"

namespace TRAP::INTERNAL
{
	class PPMImage final : public Image
	{
	public:
		/// <summary>
		/// Constructor.
		/// </summary>
		/// <param name="filepath">File path of the Image to load.</param>
		explicit PPMImage(std::string filepath);
		/// <summary>
		/// Default Copy Constructor.
		/// </summary>
		PPMImage(const PPMImage&) = default;
		/// <summary>
		/// Default Copy Assignment Operator.
		/// </summary>
		PPMImage& operator=(const PPMImage&) = default;
		/// <summary>
		/// Default Move Constructor.
		/// </summary>
		PPMImage(PPMImage&&) = default;
		/// <summary>
		/// Default Move Assignment Operator.
		/// </summary>
		PPMImage& operator=(PPMImage&&) = default;
		/// <summary>
		/// Default Destructor.
		/// </summary>
		~PPMImage() = default;

		/// <summary>
		/// Retrieve the raw pixel data of the Image.
		/// </summary>
		/// <returns>Constant pointer to the raw pixel data.</returns>
		const void* GetPixelData() const override;
		/// <summary>
		/// Retrieve the size of the raw pixel data of the Image.
		/// </summary>
		/// <returns>Size of the raw pixel data in bytes.</returns>
		uint64_t GetPixelDataSize() const override;

	private:
		std::vector<uint8_t> m_data;
		std::vector<uint16_t> m_data2Byte;
	};
}

#endif /*_TRAP_PPMIMAGE_H_*/