#ifndef _TRAP_ENTRYPOINT_H_
#define _TRAP_ENTRYPOINT_H_

#include "Application.h"

#ifdef TRAP_PLATFORM_WINDOWS
extern "C"
{
	inline _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;		  //Utilize NVIDIA GPU
	inline _declspec(dllexport) int32_t AmdPowerXpressRequestHighPerformance = 1; //Utilize AMD GPU
}
#endif

/// <summary>
/// This function will be called by TRAP Engines main function to initialize the engine.<br>
/// IT MUST BE IMPLEMENTED BY ANY CLIENT!
/// </summary>
/// <returns>A unique pointer containing a TRAP::Application</returns>
extern std::unique_ptr<TRAP::Application> TRAP::CreateApplication();

int main();

#endif /*_TRAP_ENTRYPOINT_H_*/