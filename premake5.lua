workspace "hopsoncraft"
    configurations {"Debug", "Release"}

project "hopsoncraft"
    kind "WindowedApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    cppdialect "C++17"
    links {os.findlib("sfml")}
    links {"sfml-audio", "sfml-network", "sfml-graphics", "sfml-window", "sfml-system", "pthread", "dl", "stdc++fs"}



    files {"./Source/**.cpp", "./Source/**.c", "./Source/**.h"}


filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

 filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
