# Providence - PC-64k-Intro by Team210 at Vortex 2k19
# Copyright (C) 2019 Alexander Kraus <nr4@z10.info>
# Copyright (C) 2019 DaDummy <c.anselm@paindevs.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.12)

project(nightcyber)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configurables
# Set the module path to custom path where qt is
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:/Qt/5.15.0/msvc2019_64")
set(MINIFY_64K ON CACHE BOOL "Compress the executable using kkrunchy7 (disables hybrid graphics dGPU exports)")

# Tell CMake to run qt tools when necessary (For Qt5 GUIs among other things)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find the right python interpreter version
find_package(Python3 REQUIRED COMPONENTS Interpreter)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(Qt5 COMPONENTS Core Widgets Gui Multimedia OpenGL)

set(COMMON_HEADERS config_types.h config.h GL/glext.h GL/wgl.h GL/wglext.h engine/platform.h engine/renderer.h engine/shader.h engine/loader.h engine/orchestrator.h engine/midi.h engine/debug.h)
set(SFX_SHADER sfx.frag)
file(GLOB SHADER_FILES LIST_DIRECTORIES false RELATIVE "${PROJECT_SOURCE_DIR}" "gfx/*.frag" "msx/*.comp")
set(SHADER_SYMBOLS_PATH gfx/symbols)
file(GLOB SHADER_SYMBOLS_FILES LIST_DIRECTORIES false RELATIVE "${PROJECT_SOURCE_DIR}" "${SHADER_SYMBOLS_PATH}/*.frag")
set(STRINGS_FILE font/strings.txt)

#################################
# Shader compiler executable
#################################
add_subdirectory(cmake)
add_custom_target(verify_shaders
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    SOURCES ${SHADER_FILES} ${SHADER_SYMBOLS_FILES}
    COMMAND scomp ${SHADER_FILES} ${SHADER_SYMBOLS_FILES}
)

#################################
# Demo executable
#################################

set(DEMO_HEADERS common.h draw.h scenes.h pal_linux.h pal_win32.h sequence.h)

set(SFX_HEADER sfx.h)
add_custom_target(minify_sfx
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/minification/
    COMMAND "${Python3_EXECUTABLE}" shader-compressor.py -o "${PROJECT_SOURCE_DIR}/${SFX_HEADER}" "${PROJECT_SOURCE_DIR}/${SFX_SHADER}" --no-minification
    SOURCES minification/shader-compressor.py ${SFX_SHADER}
    BYPRODUCTS ${SFX_HEADER}
)

set(SHADER_HEADER shaders.gen.h)
add_custom_target(minify_shaders
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/
    COMMAND "${Python3_EXECUTABLE}" minification/symbolize.py ${SHADER_FILES} -s ${SHADER_SYMBOLS_PATH} -o ${SHADER_HEADER}
    SOURCES minification/symbolize.py minification/Rule.py minification/Token.py ${SHADER_FILES}
    BYPRODUCTS ${SHADER_HEADER}
)

set(FONT_HEADER font/font.h)
add_custom_target(texture_packing
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/font/
    COMMAND "${Python3_EXECUTABLE}" pack.py
    SOURCES font/pack.py ${STRINGS_FILE}
    BYPRODUCTS ${FONT_HEADER}
)

add_executable(${PROJECT_NAME}
    ls.cpp
    ${COMMON_HEADERS}
    ${DEMO_HEADERS}
    ${SFX_SHADER}
    ${STRINGS_FILE}
    ${FRAGMENT_SHADERS}
    ${SHADER_FILES}
)
add_dependencies(${PROJECT_NAME} minify_sfx)
add_dependencies(${PROJECT_NAME} minify_shaders)
add_dependencies(${PROJECT_NAME} texture_packing)
add_dependencies(${PROJECT_NAME} scomp)
add_dependencies(${PROJECT_NAME} verify_shaders)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE "${OPENGL_INCLUDE_DIR}")

target_link_libraries(${PROJECT_NAME} OpenGL::GL)

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ENTRY:demo /SUBSYSTEM:Windows /OPT:REF /OPT:ICF=10 /VERBOSE /NODEFAULTLIB")
    target_compile_options(${PROJECT_NAME} PRIVATE /Gy /fp:fast /GR- /GS- /MT)

    if (MSVC_VERSION GREATER_EQUAL 1910) # VS2017
        target_link_libraries(${PROJECT_NAME} User32.lib Winmm.lib ucrt.lib msvcrt.lib vcruntime.lib Vfw32.lib)
    else()
        # for debug output: User32.lib ucrt.lib msvcrt.lib
        target_link_libraries(${PROJECT_NAME} User32.lib Winmm.lib ucrt.lib msvcrt.lib)
    endif()

    if (CMAKE_SIZEOF_VOID_P EQUAL 4 AND MINIFY_64K AND (MSVC_IDE OR CMAKE_BUILD_TYPE STREQUAL "Release"))
        target_compile_options(${PROJECT_NAME} PRIVATE /O1)
        target_compile_definitions(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELEASE>:MINIFY_64K>")
        find_program(KKRUNCHY_K7 kkrunchy_k7.exe HINTS "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/bin")
        add_custom_command(TARGET ${PROJECT_NAME} COMMAND "$<$<CONFIG:RELEASE>:${KKRUNCHY_K7}>" ARGS --best "$<TARGET_FILE:${PROJECT_NAME}>" --out "$<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}c.exe" POST_BUILD)
    endif()
else()
    find_package(SDL2 REQUIRED)
    target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/minimp3")

#################################
# Studio executable
#################################

add_executable(studio
    studio/studio.cpp
    studio/mainwindow.cpp
    studio/mainwindow.ui
    studio/demoapi.cpp
    studio/renderviewwidget.cpp
    
    ${COMMON_HEADERS}
    
    studio/nanokontrol2.ui
    studio/nanokontrol2Widget.cpp
    
    studio/apc40mk2widget.ui
    studio/apc40mk2widget.cpp
)

add_dependencies(studio minify_sfx)
add_dependencies(studio minify_shaders)
add_dependencies(studio texture_packing)

target_link_libraries(studio Qt5::Widgets)
target_link_libraries(studio OpenGL::GL)

if(WIN32)
    target_link_libraries(studio Winmm.lib)

    get_filename_component(_qt_bin_dir "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
    find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt.exe HINTS "${_qt_bin_dir}")
    message("Found windeployqt executable: ${WINDEPLOYQT_EXECUTABLE}")
    message("Binary is in: $<TARGET_FILE_DIR:studio>")
    add_custom_command(TARGET studio COMMAND ${WINDEPLOYQT_EXECUTABLE} "$<TARGET_FILE:studio>")
endif()

# Copy music and sounds to target folder
add_custom_command(TARGET ${PROJECT_NAME} COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/msx" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/msx")

# Add target for release packing
add_custom_target(create_release_archive
    WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/Team210.nfo" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Team210.nfo"
    COMMAND ${CMAKE_COMMAND} -E tar "cfv" "${PROJECT_NAME}-Team210.zip" --format=zip
    "$<TARGET_FILE:${PROJECT_NAME}>"
       "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Team210.nfo"
)
