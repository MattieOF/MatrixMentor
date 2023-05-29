workspace "MatrixMentor"
	configurations { "Debug", "Release", "Dist" }
	platforms { "Win64" }
	startproject "MatrixMentor"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["spdlog"] = "MatrixMentor/Vendor/spdlog/include"
IncludeDir["PPK_ASSERT"] = "MatrixMentor/Vendor/PPK_ASSERT/Include"

project "MatrixMentor"
	kind "ConsoleApp"
	staticruntime "On"
	language "C++"
	location "MatrixMentor"
	targetdir ("Build/%{prj.name}/" .. outputdir)
	objdir ("Build/%{prj.name}/Intermediates/" .. outputdir)

	pchheader "mmpch.h"
	pchsource "MatrixMentor/Source/mmpch.cpp"

	vpaths {
		["Include"] = {"MatrixMentor/Include/**.h", "MatrixMentor/Include/**.hpp"},
		["Source"] = {"MatrixMentor/Source/**.cpp", "MatrixMentor/Source/**.c"},
	}

	files { 
		"MatrixMentor/Include/**.h", "MatrixMentor/Include/**.hpp", 
		"MatrixMentor/Source/**.cpp", "MatrixMentor/Source/**.c",

		"MatrixMentor/Vendor/PPK_ASSERT/Source/*.cpp"
	}

	includedirs 
	{ 
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.PPK_ASSERT}",

		"MatrixMentor/Include"
	}

	links 
	{
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

os.mkdir("MatrixMentor/Source")
os.mkdir("MatrixMentor/Include")

filter "configurations:Debug"
	defines { "MM_DEBUG", "MM_ENABLE_ASSERTS" }
	symbols "On"
	runtime "Debug"

filter "configurations:Release"
	defines { "MM_RELEASE", "MM_ENABLE_ASSERTS" }
	optimize "On"
	symbols "On"
	runtime "Release"

filter "configurations:Dist"
	defines { "MM_DIST" }
	kind "WindowedApp"
	optimize "On"
	symbols "Off"
	runtime "Release"

filter "system:windows"
	cppdialect "C++17"
	systemversion "latest"
	defines { "MM_PLATFORM_WINDOWS" }

filter "platforms:Win64"
	system "Windows"
	architecture "x64"
