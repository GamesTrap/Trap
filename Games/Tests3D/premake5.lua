project "Tests3D"
	location "."
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"
	cppdialect "C++17"
	systemversion "latest"
	vectorextensions "AVX2"

	targetdir ("../../bin/" .. outputdir .. "/%{prj.group}/%{prj.name}")
	objdir ("../../bin-int/" .. outputdir .. "/%{prj.group}/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"../../TRAP/src",
		"../../%{IncludeDir.IMGUI}",
		"../../%{IncludeDir.GLSLANG}",
		"../../%{IncludeDir.SPIRV}",
		"../../%{IncludeDir.VULKAN}/include/",
		"../../%{IncludeDir.SPIRVCROSS}",
		"../../%{IncludeDir.ENTT}",
		"../../%{IncludeDir.YAMLCPP}",
		"../../%{IncludeDir.MODERNFILEDIALOGS}"
	}

	links
	{
		"TRAP"
	}

	filter "system:linux"
		links
		{
			"ImGui",
			"YAMLCpp",
			"ModernFileDialogs",
			"GLSLang",
			"SPIRV",

			"dl",
			"pthread",
			"X11",
			"HLSL",
			"OGLCompiler",
			"OSDependent",
			"SPIRV-Cross-Core",
			"SPIRV-Cross-GLSL",
			"SPIRV-Cross-HLSL"
		}

	filter "configurations:Debug"
		defines "TRAP_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TRAP_RELEASE"
		runtime "Release"
		optimize "On"
		entrypoint "mainCRTStartup"
		kind "WindowedApp"

	filter "configurations:RelWithDebInfo"
		defines "TRAP_RELWITHDEBINFO"
		runtime "Release"
		optimize "On"