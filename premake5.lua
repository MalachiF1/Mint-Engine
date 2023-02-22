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

project	"Sandbox"
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
		symbols "On"

	filter "configurations:Release"
		defines "MINT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MINT_DIST"
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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MT_PLATFORM_WINDOWS",
			"MINT_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "MINT_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MINT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MINT_DIST"
		optimize "On"


