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

include "Mint/vendor/GLFW"
include "Mint/vendor/Glad"
include "Mint/vendor/Imgui"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MT_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "MINT_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MINT_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "MINT_DIST"
		buildoptions "/MD"
		optimize "On"

project "Mint"
	location "Mint" 
	kind "SharedLib"
	language "C++"

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
		staticruntime "On" 
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
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
	}

	filter "configurations:Debug"
		defines
		{
			"MINT_DEBUG",
			"MINT_ENABLE_ASSERT"
		}
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MINT_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "MINT_DIST"
		buildoptions "/MD"
		optimize "On"
