workspace "Cobalt"
    architecture "x64"
    startproject "Sandbox"
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
-- Include Directories releative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Cobalt/vendor/GLFW/include"
IncludeDir["GLAD"] = "Cobalt/vendor/GLAD/include"

include "Cobalt/vendor/GLFW"
include "Cobalt/vendor/GLAD"


project "Cobalt"
    location "Cobalt"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "cbpc.h"
    pchsource "Cobalt/src/cbpc.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}"
    }
    links{
        "GLFW",
        "GLAD",
        "opengl32.lib"
    }
    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "CB_PLATFORM_WINDOWS",
            "CB_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }
        postbuildcommands
        {
            "{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
        }


        filter "configurations:Debug"
            defines
            { 
                "CB_DEBUG",
                "CB_ENABLE_ASSERT"
            }
            buildoptions "/MDd"
            symbols "On"

        filter "configurations:Release"
            defines "CB_RELEASE"
            buildoptions "/MD"
            optimize "On"

        filter "configurations:Dist"
            defines "CB_DIST"
            buildoptions "/MD"
            optimize "On"

project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Cobalt/vendor/spdlog/include",
        "Cobalt/src"
    }

    filter "system:windows"
        
        systemversion "latest"

        defines
        {
            "CB_PLATFORM_WINDOWS"
        }
        links
        {
            "Cobalt"
        }

        filter "configurations:Debug"
            defines "CB_DEBUG"
            symbols "On"
            buildoptions "/MDd"

        filter "configurations:Release"
            defines "CB_RELEASE"
            optimize "On"
            buildoptions "/MD"

        filter "configurations:Dist"
            defines "CB_DIST"
            optimize "On"
            buildoptions "/MD"
