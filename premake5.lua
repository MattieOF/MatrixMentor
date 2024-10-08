require "cmake"
require "clion"

workspace "MatrixMentor"
	configurations { "Debug", "Release", "Dist" }
	platforms { "Win64" }
	startproject "MatrixMentor"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["spdlog"] = "MatrixMentor/Vendor/spdlog/include"
IncludeDir["PPK_ASSERT"] = "MatrixMentor/Vendor/PPK_ASSERT/Include"
IncludeDir["GLFW"] = "MatrixMentor/Vendor/GLFW/include"
IncludeDir["GLAD"] = "MatrixMentor/Vendor/GLAD/include"
IncludeDir["glm"] = "MatrixMentor/Vendor/glm/"
IncludeDir["imgui"] = "MatrixMentor/Vendor/imgui/"

group "Vendor"
	include "MatrixMentor/Vendor/glfw.lua"
	include "MatrixMentor/Vendor/glad.lua"
	include "MatrixMentor/Vendor/imgui.lua"
group ""

project "MatrixMentor"
	kind "ConsoleApp"
	staticruntime "On"
	language "C++"
	location "MatrixMentor"
	targetdir ("Build/%{prj.name}/" .. outputdir)
	objdir ("Build/%{prj.name}/Intermediates/" .. outputdir)

	usestandardpreprocessor 'On'

	pchheader(iif(_ACTION == "vs2022", "mmpch.h", "MatrixMentor/MatrixMentor/Include/mmpch.h"))
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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.PPK_ASSERT}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",

		"MatrixMentor/Include"
	}

	links 
	{
		"GLFW",
		"GLAD",
		"imgui",
		"opengl32.lib"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "configurations:Dist"
		postbuildcommands { "{COPYDIR} " .. path.getdirectory(".") .. "\"./MatrixMentor/Content/\" \"" .. path.getdirectory("path") .. "/../Build/%{prj.name}/" .. outputdir .. "/Content/\""}

os.mkdir("MatrixMentor/Source")
os.mkdir("MatrixMentor/Include")

filter "configurations:Debug"
	defines { "MM_DEBUG", "MM_ENABLE_ASSERTS", "MM_SHOW_GL_NOTIFICATIONS" }
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
	entrypoint "mainCRTStartup"
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
