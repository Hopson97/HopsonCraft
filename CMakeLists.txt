cmake_minimum_required(VERSION 3.1)
project(MattCraft)

set (CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
file(GLOB src_files Source/Game_States/*.cpp Source/Input/*.cpp Source/Maths/*.cpp Source/Model/*.cpp Source/OpenGL/*.cpp Source/Player/*.cpp Source/PostFX/*.cpp Source/Renderer/*.cpp Source/Shaders/*.cpp Source/Texture/*.cpp Source/World/*.cpp Source/Util/*.cpp Source/*.cpp Source/World/Chunk/*.cpp Source/World/Block/*.cpp Source/World/Gen/*.cpp)

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
	include_directories(${OPENGL_INCLUDE_DIRS})
	link_libraries(${OPENGL_LIBRARIES})
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIRS})
    link_libraries(${SFML_LIBRARIES})
endif()

add_executable(game ${src_files})