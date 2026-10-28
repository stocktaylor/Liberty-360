# liberty - ReXGlue Recompiled Project
#
# SDK boilerplate lives in generated/rexglue.cmake.

cmake_minimum_required(VERSION 3.25)
project(liberty LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(generated/rexglue.cmake)

# The launch menu and in-game menu (../rexlauncher). OFF for builds where it
# can't run, such as WebAssembly (it restarts the process with execv).
option(LIBERTY_LAUNCHER "Build with the rexlauncher menus" ON)

# Sources
set(LIBERTY_SOURCES
    src/main.cpp
)

if(WIN32)
    add_executable(liberty WIN32 ${LIBERTY_SOURCES})
else()
    add_executable(liberty ${LIBERTY_SOURCES})
endif()

target_compile_definitions(liberty PRIVATE LIBERTY_LAUNCHER=$<BOOL:${LIBERTY_LAUNCHER}>)

rexglue_setup_target(liberty GPU_PLUGINS xenos)

# In-window launch menu shared by the recomp projects (../rexlauncher).
if(LIBERTY_LAUNCHER)
    add_subdirectory(../rexlauncher rexlauncher)
    target_link_libraries(liberty PRIVATE rexlauncher)
endif()
