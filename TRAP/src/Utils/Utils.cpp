#include "TRAPPCH.h"

#include "Utils.h"

std::string TRAP::Utils::UUIDToString(const std::vector<uint8_t>& uuid)
{
	std::stringstream s;
	
	s << std::hex << std::setfill('0')
		<< std::setw(2) << static_cast<int32_t>(uuid[0])
		<< std::setw(2) << static_cast<int32_t>(uuid[1])
		<< std::setw(2) << static_cast<int32_t>(uuid[2])
		<< std::setw(2) << static_cast<int32_t>(uuid[3])
		<< '-'
		<< std::setw(2) << static_cast<int32_t>(uuid[4])
		<< std::setw(2) << static_cast<int32_t>(uuid[5])
		<< '-'
		<< std::setw(2) << static_cast<int32_t>(uuid[6])
		<< std::setw(2) << static_cast<int32_t>(uuid[7])
		<< '-'
		<< std::setw(2) << static_cast<int32_t>(uuid[8])
		<< std::setw(2) << static_cast<int32_t>(uuid[9])
		<< '-'
		<< std::setw(2) << static_cast<int32_t>(uuid[10])
		<< std::setw(2) << static_cast<int32_t>(uuid[11])
		<< std::setw(2) << static_cast<int32_t>(uuid[12])
		<< std::setw(2) << static_cast<int32_t>(uuid[13])
		<< std::setw(2) << static_cast<int32_t>(uuid[14])
		<< std::setw(2) << static_cast<int32_t>(uuid[15]);

	return s.str();
}

//-------------------------------------------------------------------------------------------------------------------//

std::vector<uint8_t> TRAP::Utils::UUIDFromString(const std::string& uuid)
{
	uint8_t digit = 0;
	bool firstDigit = true;
	std::size_t index = 0;

	if (uuid.empty())
		return {};
	
	std::vector<uint8_t> result;
	for (uint8_t i : uuid)
	{
		if (i == '-')
			continue;
		
		if (index >= 16 || !std::isxdigit(i))
			return {};

		if(firstDigit)
		{
			digit = i;
			firstDigit = false;
		}
		else
		{
			uint8_t charDigit;
			uint8_t uuidDigit;

			if (digit >= '0' && digit <= '9')
				charDigit = digit - '0';
			else if (digit >= 'a' && digit <= 'f')
				charDigit = 10 + digit - 'a';
			else if (digit >= 'A' && digit <= 'F')
				charDigit = 10 + digit - 'A';
			else
				charDigit = 0;

			if (i >= '0' && i <= '9')
				uuidDigit = i - '0';
			else if (i >= 'a' && i <= 'f')
				uuidDigit = 10 + i - 'a';
			else if (i >= 'A' && i <= 'F')
				uuidDigit = 10 + i - 'A';
			else
				uuidDigit = 0;
			
			result.emplace_back((charDigit << 4) | uuidDigit);
			index++;
			firstDigit = true;
		}
	}

	return result;
}