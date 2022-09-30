cmake_minimum_required(VERSION 2.8)
project(main)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(sources
    imgui/imconfig.h
    imgui/imgui.cpp
    imgui/imgui.h
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_internal.h
    imgui/imgui_widgets.cpp
    imgui/imstb_rectpack.h
    imgui/imstb_textedit.h
    imgui/imstb_truetype.h
    imgui/imgui_impl_sdlrenderer.cpp
    imgui/imgui_impl_sdlrenderer.h
    imgui/imgui_impl_sdl.cpp
    imgui/imgui_impl_sdl.h
)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
find_package( OpenCV REQUIRED )
add_executable( main main.cpp ${sources} )
target_link_libraries( main ${OpenCV_LIBS} ${SDL2_LIBRARIES} )
