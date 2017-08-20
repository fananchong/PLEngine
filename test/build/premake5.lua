workspace "plengine_test"
    configurations { "Debug", "Release" }
    platforms { "x64" }
    targetdir "../../bin/%{cfg.buildcfg}"
    language "C++"
    includedirs {
        "..",
        "../../deps/include",
    }
    flags {
        "C++11",
        "StaticRuntime",
    }
    links {
        "plengine",
    }

    filter "configurations:Debug"
    defines { "_DEBUG" }
    symbols "On"
    libdirs { }
    filter "configurations:Release"
    defines { "NDEBUG" }
    libdirs { }
    optimize "On"
    filter { }
    
    if os.is("windows") then
        objdir "obj/win/%{cfg.platform}/%{cfg.buildcfg}"
        defines {
            "WIN32",
        }
        includedirs {
        }
        libdirs {
            "../../deps/lib_win",
        }
        filter "configurations:Debug"
        libdirs {
            "../../deps/lib_win/debug",
        }
        linkoptions { '/NODEFAULTLIB:"python36.lib"' }
        filter "configurations:Release"
        libdirs {
            "../../deps/lib_win/release",
        }
        filter { }
        linkoptions { "/ignore:4049", "/ignore:4217" }
    end
	
    if os.is("linux") then
        objdir "obj/linux/%{cfg.platform}/%{cfg.buildcfg}"
        defines {
        }
        includedirs {
        }
        linkoptions { "-static-libgcc -static-libstdc++ -Xlinker -export-dynamic" }
        libdirs {
            "../../deps/lib_linux",
        }
        filter "configurations:Debug"
        libdirs {
            "../../deps/lib_linux/debug",
        }
        filter "configurations:Release"
        libdirs {
            "../../deps/lib_linux/release",
        }
        filter { }
        links {
            "boost_program_options",
            "boost_python3",
            "boost_log_setup",
            "boost_log",
            "boost_serialization",
            "boost_thread",
            "boost_filesystem",
            "boost_regex",
            "boost_system",
            "fmt",
            "python3.6m",
            "pthread",
            "dl",
            "util"
        }
    end
    
    
project "test_log"
    kind "ConsoleApp"
    files {
        "../test_log/**",
    }
    
project "test_random"
    kind "ConsoleApp"
    files {
        "../test_random/**",
    }
    
project "test_timer"
    kind "ConsoleApp"
    files {
        "../test_timer/**",
    }
    
project "test_program_options"
    kind "ConsoleApp"
    files {
        "../test_program_options/**",
    }
