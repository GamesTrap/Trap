#pragma once

#ifdef TRAP_PLATFORM_WINDOWS
extern "C"
{
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; //Utilize NVIDIA GPU
	_declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1; //Utilize AMD GPU

}
#endif

#include "Application.h"

inline std::unique_ptr<TRAP::Log> logger = std::make_unique<TRAP::Log>();

extern std::unique_ptr<TRAP::Application> TRAP::CreateApplication();

int main()
{
	const auto app = TRAP::CreateApplication();
	app->Run();
}