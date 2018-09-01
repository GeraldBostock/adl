# ADL Game Engine

## 3D cross-platform game engine

ADL is a somewhat competent cross-platform 3D game engine.

### Build Instructions

**Windows**
**Prerequisites**
- [Cmake](https://cmake.org/download/)
- [Visual Studio 2017](https://visualstudio.microsoft.com/tr/downloads/)

Running build_scripts/Windows_visual_studio.bat generates a Visual Studio Solution file under build folder. If that failes most likely you are missing some dependencies. Check cmakes output for which ones you are missing and download them. 
Put include files under dependencies/[library_name]/include
Lib files under dependencies/[library_name]/lib
and dlls under dependencies/bin folder.

**Dependencies:**

- [Assimp](http://assimp.sourceforge.net/main_downloads.html)
- [Freetpye](https://www.freetype.org/download.html)
- [GLEW](http://glew.sourceforge.net/)
- [RapidJSON](https://github.com/Tencent/rapidjson)
- [SDL2](https://www.libsdl.org/download-2.0.php)
- [spdlog](https://github.com/gabime/spdlog)
- [stb](https://github.com/nothings/stb)
- [ImGui](https://github.com/ocornut/imgui)
