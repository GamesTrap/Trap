#ifndef _TRAP_PNGIMAGE_H_
#define _TRAP_PNGIMAGE_H_

#include "ImageLoader/Image.h"

namespace TRAP::INTERNAL
{
	class PNGImage final : public Image
	{
	public:
		/// <summary>
		/// Constructor.
		/// </summary>
		/// <param name="filepath">File path of the Image to load.</param>
		explicit PNGImage(std::string filepath);
		/// <summary>
		/// Default Copy Constructor.
		/// </summary>
		PNGImage(const PNGImage&) = default;
		/// <summary>
		/// Default Copy Assignment Operator.
		/// </summary>
		PNGImage& operator=(const PNGImage&) = default;
		/// <summary>
		/// Default Move Constructor.
		/// </summary>
		PNGImage(PNGImage&&) = default;
		/// <summary>
		/// Default Move Assignment Operator.
		/// </summary>
		PNGImage& operator=(PNGImage&&) = default;
		/// <summary>
		/// Default Destructor.
		/// </summary>
		~PNGImage() = default;

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
		struct RGBA
		{
			uint8_t Red = 0;
			uint8_t Green = 0;
			uint8_t Blue = 0;
			uint8_t Alpha = 255;
		};
		struct Data
		{
			uint32_t Width = 0;
			uint32_t Height = 0;
			uint8_t BitDepth = 0;
			uint8_t ColorType = 0;
			uint8_t CompressionMethod = 0; //Always 0 others are unsupported extensions!
			uint8_t FilterMethod = 0; //Always 0 others are unsupported extensions!
			uint8_t InterlaceMethod = 0; //Always 0 or 1 others are unsupported extensions!
			std::vector<RGBA> Palette{};
			std::vector<uint8_t> CompressedData{};
		};
		struct AlreadyLoaded
		{
			bool IHDR = false;
			bool cHRM = false;
			bool gAMA = false;
			bool iCCP = false;
			bool sBIT = false;
			bool sRGB = false;
			bool bKGD = false;
			bool hIST = false;
			bool tRNS = false;
			bool pHYs = false;
			bool tIME = false;
			bool PLTE = false;
			bool IDAT = false;
			bool eXIf = false;
		};

		struct NextChunk
		{
			uint32_t Length = 0;
			std::array<uint8_t, 4> MagicNumber{};
		} nextChunk;

		static bool ProcessChunk(NextChunk& nextChunk, std::ifstream& file, Data& data, AlreadyLoaded& alreadyLoaded, bool needSwap);

		struct IHDRChunk
		{
			uint32_t Width = 0;
			uint32_t Height = 0;
			uint8_t BitDepth = 0;
			uint8_t ColorType = 0;
			uint8_t CompressionMethod = 0;
			uint8_t FilterMethod = 0;
			uint8_t InterlaceMethod = 0;
			std::array<uint8_t, 4> CRC{};
		};
		struct tIMEChunk
		{
			uint16_t Year = 0;
			uint8_t Month = 0;
			uint8_t Day = 0;
			uint8_t Hour = 0;
			uint8_t Minute = 0;
			uint8_t Second = 0;
		};

		static bool ProcessIHDR(std::ifstream& file, Data& data, bool needSwap);
		static bool ProcesscHRM(std::ifstream& file);
		static bool ProcessgAMA(std::ifstream& file);
		static bool ProcessiCCP(std::ifstream& file, uint32_t length);
		static bool ProcesssBIT(std::ifstream& file, const Data& date);
		static bool ProcesssRGB(std::ifstream& file);
		static bool ProcessbKGD(std::ifstream& file, const Data& data, bool needSwap);
		static bool ProcesshIST(std::ifstream& file, uint32_t length);
		static bool ProcesstRNS(std::ifstream& file, uint32_t length, Data& data);
		static bool ProcesspHYs(std::ifstream& file);
		static bool ProcesssPLT(std::ifstream& file, uint32_t length);
		static bool ProcesstIME(std::ifstream& file, bool needSwap);
		static bool ProcessiTXt(std::ifstream& file, uint32_t length);
		static bool ProcesstEXt(std::ifstream& file, uint32_t length);
		static bool ProcesszTXt(std::ifstream& file, uint32_t length);
		static bool ProcessPLTE(std::ifstream& file, Data& data, uint32_t length);
		static bool ProcessIDAT(std::ifstream& file, Data& data, uint32_t length);
		static bool ProcesseXIf(std::ifstream& file, uint32_t length);
		static bool IHDRCheck(const IHDRChunk& ihdrChunk);
		static bool tIMECheck(const tIMEChunk& timeChunk);

		std::vector<uint8_t> m_data;
		std::vector<uint16_t> m_data2Byte;

		static bool DecompressData(uint8_t* source, int sourceLength, uint8_t* destination, int destinationLength, bool needSwap);
		static bool UnFilterScanline(uint8_t* recon, const uint8_t* scanline, const uint8_t* precon, std::size_t byteWidth, uint8_t filterType, std::size_t length);
		static bool UnFilter(uint8_t* out, const uint8_t* in, uint32_t width, uint32_t height, uint32_t bitsPerPixel);
		static uint8_t PaethPredictor(uint16_t a, uint16_t b, uint16_t c);
		static std::size_t GetRawSizeIDAT(uint32_t width, uint32_t height, uint32_t bitsPerPixel);
		static std::size_t GetRawSize(uint32_t width, uint32_t height, uint32_t bitsPerPixel);
		static bool PostProcessScanlines(uint8_t* out, uint8_t* in, uint32_t width, uint32_t height, uint32_t bitsPerPixel, uint8_t interlaceMethod);
		static void Adam7GetPassValues(std::array<uint32_t, 7>& passW,
		                               std::array<uint32_t, 7>& passH,
		                               std::array<std::size_t, 8>& filterPassStart,
		                               std::array<std::size_t, 8>& paddedPassStart,
		                               std::array<std::size_t, 8>& passStart,
		                               uint32_t width,
		                               uint32_t height,
		                               uint32_t bitsPerPixel);
		static void Adam7DeInterlace(uint8_t* out, const uint8_t* in, uint32_t width, uint32_t height, uint32_t bitsPerPixel);
		static std::vector<uint16_t> ConvertTo2Byte(std::vector<uint8_t>& raw);
		static std::vector<uint8_t> ResolveIndexed(std::vector<uint8_t>& raw, uint32_t width, uint32_t height, const Data& data);
	};
}

#endif /*_TRAP_PNGIMAGE_H_*/