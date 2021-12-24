--Arrow Dependencies--

--Include directories relative to root folder--
IncludeDir = {}
IncludeDir["GLFW"] = "Arrow/vendor/GLFW/include"
IncludeDir["Glad"] = "Arrow/vendor/Glad/include"
IncludeDir["glm"] = "Arrow/vendor/glm"
IncludeDir["ImGui"] = "Arrow/vendor/ImGui"
IncludeDir["spdlog"] = "Arrow/vendor/spdlog/include"
IncludeDir["stb_image"] = "Arrow/vendor/stb_image"

workspace "Arrow"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"

    project "GLFW"
        location "Arrow/vendor/GLFW"
        kind "StaticLib"
        language "C"
        staticruntime "on"

        targetdir ("%{prj.location}/bin/" .. outputdir .. "/%{prj.name}")
        objdir ("%{prj.location}/bin-int/" .. outputdir .. "/%{prj.name}")

        files {
            "%{prj.location}/include/GLFW/glfw3.h",
            "%{prj.location}include/GLFW/glfw3native.h",
            "%{prj.location}/src/glfw_config.h",
            "%{prj.location}/src/context.c",
            "%{prj.location}/src/init.c",
            "%{prj.location}/src/input.c",
            "%{prj.location}/src/monitor.c",
            "%{prj.location}/src/vulkan.c",
            "%{prj.location}/src/window.c"
        }

        filter "system:windows"
            systemversion "latest"

            files {
                "%{prj.location}/src/win32_init.c",
                "%{prj.location}/src/win32_joystick.c",
                "%{prj.location}/src/win32_monitor.c",
                "%{prj.location}/src/win32_time.c",
                "%{prj.location}/src/win32_thread.c",
                "%{prj.location}/src/win32_window.c",
                "%{prj.location}/src/wgl_context.c",
                "%{prj.location}/src/egl_context.c",
                "%{prj.location}/src/osmesa_context.c"
            }

            links {
                "Dwmapi.lib"
            }

            defines { 
                "_GLFW_WIN32",
                "_CRT_SECURE_NO_WARNINGS"
            }



        filter "configurations:Debug"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            runtime "Release"
            optimize "on"

    project "ImGui"
        location "Arrow/vendor/ImGui"
        kind "StaticLib"
        language "C++"
        staticruntime "on"
        
        targetdir ("%{prj.location}/bin/" .. outputdir .. "/%{prj.name}")
        objdir ("%{prj.location}/bin-int/" .. outputdir .. "/%{prj.name}")
        
        files {
            "%{prj.location}/imconfig.h",
            "%{prj.location}/imgui.h",
            "%{prj.location}/imgui.cpp",
            "%{prj.location}/imgui_draw.cpp",
            "%{prj.location}/imgui_internal.h",
            "%{prj.location}/imgui_tables.cpp",
            "%{prj.location}/imgui_widgets.cpp",
            "%{prj.location}/imstb_rectpack.h",
            "%{prj.location}/imstb_textedit.h",
            "%{prj.location}/imstb_truetype.h",
            "%{prj.location}/imgui_demo.cpp",
            "%{prj.location}/backends/imgui_impl_glfw.h",
            "%{prj.location}/backends/imgui_impl_glfw.cpp",
            "%{prj.location}/backends/imgui_impl_opengl3.h",
            "%{prj.location}/backends/imgui_impl_opengl3.cpp"
        }

        includedirs {
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.ImGui}"
        }
        
        filter "system:windows"
            systemversion "latest"
            cppdialect "C++17"
        
            filter "configurations:Debug"
                runtime "Debug"
                symbols "on"
        
            filter "configurations:Release"
                runtime "Release"
                optimize "on"

    project "Glad"
        location "Arrow/vendor/Glad"
        kind "StaticLib"
        language "C"
        staticruntime "On"

        targetdir ("%{prj.location}/bin/" .. outputdir .. "/%{prj.name}")
        objdir ("%{prj.location}/bin-int/" .. outputdir .. "/%{prj.name}")

        files {
            "%{prj.location}/include/glad/glad.h",
            "%{prj.location}/include/KHR/khrplatform.h",
            "%{prj.location}/src/glad.c"
        }

        includedirs {
            "%{prj.location}/include"
        }

        filter "system:windows"
            systemversion "latest"

            filter "configurations:Debug"
                runtime "Debug"
                symbols "on"

            filter "configurations:Release"
            runtime "Release"
            optimize "on"
