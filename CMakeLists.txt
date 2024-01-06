cmake_minimum_required(VERSION 3.0.0)
project(simulator VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(CTest)
enable_testing()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug/Shaders/)
add_executable(simulator main.cpp glad.c FPSCamera.hpp FPSCamera.cpp Mesh.hpp Mesh.cpp
 Model.hpp Model.cpp Shader.hpp Shader.cpp stb_image.cpp Utils.hpp Utils.cpp Object.hpp Object.cpp Earth.hpp Earth.cpp 
 SkyBox.hpp SkyBox.cpp ImGui/imgui_impl_glfw.h ImGui/imgui_impl_glfw.cpp ImGui/imgui_impl_opengl3.h ImGui/imgui_impl_opengl3.cpp 
 ImGui/imconfig.h ImGui/imgui_impl_opengl3_loader.h ImGui/imgui_demo.cpp ImGui/imgui.cpp ImGui/imgui_draw.cpp ImGui/imgui_widgets.cpp 
 ImGui/imgui.h ImGui/imgui_internal.h ImGui/imstb_rectpack.h ImGui/imstb_textedit.h ImGui/imstb_truetype.h ImGui/imgui_tables.cpp 
 Sun.hpp Sun.cpp Mercury.hpp Mercury.cpp Venus.hpp Venus.cpp Moon.hpp Moon.cpp Mars.hpp Mars.cpp Jupiter.hpp Jupiter.cpp Saturn.hpp Saturn.cpp
 Uranus.hpp Uranus.cpp Neptune.hpp Neptune.cpp Rock.hpp Rock.cpp)
link_directories(D:/opengl/Libs)
find_library(DLL_LIBRARY NAMES assimp-vc143-mtd.dll PATHS D:/opengl/Libs)
target_link_libraries(simulator PRIVATE D:/opengl/Libs/glfw3.lib D:/opengl/Libs/assimp-vc143-mtd.lib)
include_directories( 
    D:/opengl/Include       
)  
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
