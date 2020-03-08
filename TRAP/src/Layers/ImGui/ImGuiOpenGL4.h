/*The MIT License(MIT)

Copyright(c) 2014 - 2020 Omar Cornut

Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Modified by: Jan "GamesTrap" Schuerkamp
*/

#ifndef _TRAP_IMGUI_OPENGL3_H_
#define _TRAP_IMGUI_OPENGL3_H_

//Backend API
IMGUI_IMPL_API bool ImGuiOpenGL4Init();
IMGUI_IMPL_API void ImGuiOpenGL4Shutdown();
IMGUI_IMPL_API void ImGuiOpenGL4NewFrame();
IMGUI_IMPL_API void ImGuiOpenGL4RenderDrawData(ImDrawData* drawData);

//(Optional) Called by Init/NewFrame/Shutdown
IMGUI_IMPL_API bool ImGuiOpenGL4CreateFontsTexture();
IMGUI_IMPL_API void ImGuiOpenGL4DestroyFontsTexture();
IMGUI_IMPL_API bool ImGuiOpenGL4CreateDeviceObjects();
IMGUI_IMPL_API void ImGuiOpenGL4DestroyDeviceObjects();

#endif /*_TRAP_IMGUI_OPENGL3_H_*/