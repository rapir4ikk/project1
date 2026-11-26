#Минимальная версия CMake
cmake_minimum_required(VERSION 3.26)
project(project1 LANGUAGES CXX)
include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 3.0.2
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(imgui
 GIT_REPOSITORY https://github.com/ocornut/imgui.git
 GIT_TAG v1.91.9b
)
FetchContent_MakeAvailable(imgui)

set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "" FORCE)

FetchContent_Declare(imgui-sfml
 GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
 GIT_TAG master
)
FetchContent_MakeAvailable(imgui-sfml)

add_executable(project1
 main.cpp NPC.cpp characterfactory.cpp evil.cpp
 paladin.cpp player.cpp warrior.cpp wizard.cpp
)
target_compile_features(project1 PRIVATE cxx_std_17)
target_link_libraries(project1 PRIVATE ImGui-SFML::ImGui-SFML

if(MSVC)
 target_compile_options(project1 PRIVATE
 /source-charset:utf-8
 /execution-charset:.1251
 )
endif()
