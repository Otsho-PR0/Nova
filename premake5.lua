workspace "Nova"
	configurations { "Debug", "Release" }
	architecture "x64"

project "ImGui"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	targetdir "build/%{cfg.buildcfg}"

	files { "thirdparty/imgui/*.h*", "thirdparty/imgui/*.c*", "thirdparty/imgui/backends/imgui_impl_dx11.h", "thirdparty/imgui/backends/imgui_impl_dx11.cpp", "thirdparty/imgui/backends/imgui_impl_win32.h", "thirdparty/imgui/backends/imgui_impl_win32.cpp" }

	includedirs { "thirdparty/imgui/" }

	filter "action:vs*"
		defines { "IMGUI_API=__declspec(dllexport)" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

project "Nova"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	targetdir "build/%{cfg.buildcfg}"

	files { "Nova/include/**.h*", "Nova/src/**.c*" }
	
	defines { "NOVA_EXPORTS" }
	undefines { "UNICODE" }

	includedirs { "Nova/include/", "thirdparty/imgui/" }
	links { "d3d11.lib", "d3dcompiler.lib", "ImGui" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

project "Editor"
	kind "WindowedApp"
	language "C++"
	targetdir "build/%{cfg.buildcfg}"

	files { "Editor/include/**.h*", "Editor/src/**.c*" }

	includedirs { "Editor/include/", "Nova/include/", "thirdparty/imgui/" }
	links { "Nova", "ImGui" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"