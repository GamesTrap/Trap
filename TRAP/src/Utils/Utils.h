#ifndef _TRAP_UTILS_H_
#define _TRAP_UTILS_H_

namespace TRAP::Utils
{
	//Determines if a function can be resolved @ compile time or not
	constexpr bool IsConstantEvaluated()
	{
	#if __cpp_lib_constant_evaluated >= 201811
		return std::is_constant_evaluated();
	#endif

		//Compiler doesnt support std::is_constant_evaluated()
		return false;
	}

	std::string UUIDToString(const std::vector<uint8_t>& uuid);
	std::vector<uint8_t> UUIDFromString(std::string_view uuid);
}

#endif /*_TRAP_UTILS_H_*/