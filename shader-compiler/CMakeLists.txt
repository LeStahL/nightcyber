cmake_minimum_required(VERSION 3.11)
project(shader-compiler)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp "${CMAKE_CURRENT_SOURCE_DIR}/../GL/glext.h" "${CMAKE_CURRENT_SOURCE_DIR}/../GL/wgl.h" "${CMAKE_CURRENT_SOURCE_DIR}/../GL/wglext.h")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ENTRY:main /SUBSYSTEM:Console")
target_compile_options(${PROJECT_NAME} PRIVATE /MD)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/..")
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
target_link_libraries(${PROJECT_NAME} User32.lib Winmm.lib msvcrt.lib ucrt.lib vcruntime.lib)
