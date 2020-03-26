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
IncludeDir["ImGui"] = "Cobalt/vendor/imgui"
IncludeDir["glm"] = "Cobalt/vendor/glm"
IncludeDir["stb_image"] = "Cobalt/vendor/stb_image"


include "Cobalt/vendor/GLFW"
include "Cobalt/vendor/GLAD"
include "Cobalt/vendor/imgui"


project "Cobalt"
    location "Cobalt"
    kind "StaticLib"
    language "C++"
    staticruntime "On"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "cbpc.h"
    pchsource "Cobalt/src/cbpc.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }
    defines{
        "_CRT_SECURE_NO_WARNINGS"
    }
    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }
    links{
        "GLFW",
        "GLAD",
        "ImGui",
        "opengl32.lib"
    }
    filter "system:windows"
        
        
        systemversion "latest"

        defines
        {
            "CB_PLATFORM_WINDOWS",
            "CB_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        filter "configurations:Debug"
            defines
            { 
                "CB_DEBUG",
                "CB_ENABLE_ASSERT"
            }
            symbols "On"

        filter "configurations:Release"
            defines "CB_RELEASE"
            optimize "On"

        filter "configurations:Dist"
            defines "CB_DIST"
            optimize "On"

project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

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
        "Cobalt/src",
        "%{IncludeDir.glm}",
        "Cobalt/vendor"
    }
    links{
        "ImGui"
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

        filter "configurations:Release"
            defines "CB_RELEASE"
            optimize "On"

        filter "configurations:Dist"
            defines "CB_DIST"
            optimize "On"
