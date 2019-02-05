function includeGLFW()
    includedirs "Libraries/GLFW/Include"
end

function includeSFML()
    includedirs "Libraries/SFML/include"
end

function includeGLEW()
    includedirs "Libraries/glew/include"
end

function includeAssimp()
    includedirs "Libraries/assimp/include"
end

function includeGLM()
    includedirs "Libraries/glm"
end

function includeExtras()
    includedirs "Libraries/extras"
end

function linkGLFW()
    libdirs "Libraries/GLFW/Lib"

    filter "kind:not StaticLib"
        links "glfw3"

    filter {}
end

function linkSFML()
    libdirs "Libraries/SFML/lib"
    defines {"SFML_STATIC"}

    configuration "Debug"
        links {
            "sfml-window-s-d",
            "sfml-system-s-d",
            "sfml-audio-s-d",
            "sfml-network-s-d",
            "sfml-graphics-s-d",
            "opengl32",
            "freetype",
            "winmm",
            "gdi32",
            "openal32",
            "flac",
            "vorbisenc",
            "vorbisfile",
            "vorbis",
            "ogg",
            "ws2_32"
        }

    configuration "Release"
        links {
            "sfml-window-s",
            "sfml-system-s",
            "sfml-audio-s",
            "sfml-network-s",
            "sfml-graphics-s",
            "opengl32",
            "freetype",
            "winmm",
            "gdi32",
            "openal32",
            "flac",
            "vorbisenc",
            "vorbisfile",
            "vorbis",
            "ogg",
            "ws2_32"
        }
    
    filter{}
end

function linkGLEW()
    libdirs "Libraries/glew/lib"
    defines {"GLEW_STATIC"}

    configuration "Debug"
        links "glew32s"

    configuration "Release"
        links "glew32s"

    filter {}
end

function linkAssimp()
    libdirs "Libraries/assimp/lib"

    configuration "Debug"
        links "assimp"

    configuration "Release"
        links "assimp"

    filter {}
end

workspace "OpenGL-SFML"
    location "Projects"
    language "C++"
    architecture "x86_64"

    configurations {"Debug", "Release"}

    filter{"configurations:Debug"}
        symbols "On"
    
    filter{"configurations:Release"}
        optimize "On"

    filter{}

    targetdir("Build/Bin/%{prj.name}/%{cfg.longname}")
    objdir("Build/Obj/%{prj.name}/%{cfg.longname}")

project "App"
    location "Projects/App"
    kind "ConsoleApp"

    files "Projects/App/*.cpp"
    files "Projects/App/*.h"
  
    includeSFML()
    linkSFML()

    includeGLEW()
    linkGLEW()

    includeAssimp()
    linkAssimp()

    includeGLM()
    includeExtras() 