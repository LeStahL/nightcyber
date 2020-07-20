cmake_minimum_required(VERSION 3.11)
project(scomp)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)

add_executable(scomp scomp.cpp)
set_target_properties(scomp PROPERTIES LINK_FLAGS "/ENTRY:main /SUBSYSTEM:Console")
target_compile_options(scomp PRIVATE /MD /MT )
target_include_directories(scomp PRIVATE "${CMAKE_SOURCE_DIR}")
target_link_libraries(scomp OpenGL::GL)
target_link_libraries(scomp User32.lib Winmm.lib ucrt.lib msvcrt.lib User32.lib ucrt.lib msvcrt.lib)
