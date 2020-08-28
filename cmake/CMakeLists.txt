cmake_minimum_required(VERSION 3.11)
project(scomp)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)

add_executable(scomp scomp.cpp "${CMAKE_SOURCE_DIR}/GL/glext.h" "${CMAKE_SOURCE_DIR}/GL/wgl.h" "${CMAKE_SOURCE_DIR}/GL/wglext.h")
set_target_properties(scomp PROPERTIES LINK_FLAGS "/ENTRY:main /SUBSYSTEM:Console")
target_compile_options(scomp PRIVATE /MD)
target_include_directories(scomp PRIVATE "${CMAKE_SOURCE_DIR}")
target_link_libraries(scomp OpenGL::GL)
target_link_libraries(scomp User32.lib Winmm.lib msvcrt.lib ucrt.lib vcruntime.lib)
