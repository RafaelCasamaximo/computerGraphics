cmake_minimum_required(VERSION 2.8)
project(main)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(QT_USE_QTOPENGL TRUE)
set(imgui_sources
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
    imgui/imgui_impl_opengl2.cpp
    imgui/imgui_impl_opengl2.h
    imgui/imgui_impl_glut.cpp
    imgui/imgui_impl_glut.h
)
set(sources

)
find_package( OpenGL REQUIRED )
find_package( GLUT REQUIRED )
find_package( GLU REQUIRED )
add_executable( main main.cpp ${imgui_sources} ${sources} )
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} GLU GLUT::GLUT)

