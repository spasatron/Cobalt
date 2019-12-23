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
        "%{prj.name}/src"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "CB_PLATFORM_WINDOWS",
            "CB_BUILD_DLL"
        }

        postbuildcommands
        {
            "{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
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

        filter "configurations:Release"
            defines "CB_RELEASE"
            optimize "On"

        filter "configurations:Dist"
            defines "CB_DIST"
            optimize "On"
