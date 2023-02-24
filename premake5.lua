workspace "Mint"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Mint/vendor/GLFW/include"
IncludeDir["Glad"] = "Mint/vendor/Glad/include"
IncludeDir["ImGui"] = "Mint/vendor/ImGui"

group "Dependencies"
	include "Mint/vendor/GLFW"
	include "Mint/vendor/Glad"
	include "Mint/vendor/Imgui"
group ""

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Mint/vendor/spdlog/include",
		"Mint/src"
	}

	links
	{
		"Mint"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"MT_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "MINT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MINT_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "MINT_DIST"
		runtime "Release"
		optimize "On"

project "Mint"
	location "Mint" 
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mtpch.h"
	pchsource "Mint/src/mtpch.cpp" -- required for MSVC

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"Glad",
		"ImGui"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"MT_PLATFORM_WINDOWS",
			"MINT_BUILD_DLL",
			"GLFW_INCLUDE_NONE", -- use Glad with GLFW
			"MGUI_IMPL_OPENGL_LOADER_CUSTOM" -- use Glad with ImGui
		}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
	}

	filter "configurations:Debug"
		defines "MINT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MINT_RELEASE"
		runtime "Release"
		symbols "On"
		optimize "On"

	filter "configurations:Dist"
		defines "MINT_DIST"
		runtime "Release"
		optimize "On"
