workspace "plengine_common"
    configurations { "Debug", "Release" }
    platforms { "x64" }
    targetdir "../bin/%{cfg.buildcfg}"
    language "C++"
    includedirs {
        "..",
        "../../../deps/include",
    }
    flags {
        "C++11",
        "StaticRuntime",
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
    
    defines {
        "BOOST_PYTHON_STATIC_LIB",
        "Py_NO_ENABLE_SHARED",
        "ENABLE_PLENGINE_PYTHON",
    }
	
    if os.is("windows") then
        objdir "obj/win/%{cfg.platform}/%{cfg.buildcfg}"
        defines {
            "WIN32",
            "_WIN32_WINNT=0x0601",
        }
        includedirs {
            "../../../deps/include/python/win",
        }
        libdirs {
            "../../../deps/lib_win",
        }
        filter "configurations:Debug"
        libdirs {
            "../../../deps/lib_win/debug",
        }
        filter "configurations:Release"
        libdirs {
            "../../../deps/lib_win/release",
        }
        filter { }
    end
	
    if os.is("linux") then
        objdir "obj/linux/%{cfg.platform}/%{cfg.buildcfg}"
        defines {
        }
        includedirs {
            "../../../deps/include/python/linux",
        }
        linkoptions { "-static-libgcc -static-libstdc++ -Xlinker -export-dynamic" }
        libdirs {
            "../../../deps/lib_linux",
        }
        filter "configurations:Debug"
        libdirs {
            "../../../deps/lib_linux/debug",
        }
        filter "configurations:Release"
        libdirs {
            "../../../deps/lib_linux/release",
        }
        filter { }
        links {
        }
    end
    
    
project "plengine_common"
    kind "StaticLib"
    if os.is("linux") then
        buildoptions { "-fPIC" }
    end
    files {
        "../*.h",
        "../detail/**",
    }
    configuration "windows"
        prebuildcommands  { "get_version.bat" }
        postbuildcommands { "copy_lib.bat" }
    configuration "linux"
        prebuildcommands  { "./get_version.sh" }
        postbuildcommands { "./copy_lib.sh" }
