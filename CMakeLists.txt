cmake_minimum_required(VERSION 3.1)
project(HopsonCraft)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

file(GLOB src_files
    Source/*.cpp
    Source/Entity/*.cpp
	Source/GUI/*.cpp
    Source/HUD/*.cpp
	Source/Input/*.cpp
	Source/Maths/*.cpp
	Source/Physics/*.cpp
	Source/Player/*.cpp
	Source/Renderer/*.cpp
    Source/Resource_Managers/*.cpp
	Source/Shaders/*.cpp
	Source/States/*cpp
	Source/Texture/*.cpp
    Source/Util/*.cpp
	Source/World/*.cpp
	Source/World/Block/Block_Types/*.cpp
	Source/World/Block/*.cpp
	Source/World/Chunk/*.cpp
	Source/World/Generators/*.cpp
	)

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

find_package(Threads REQUIRED)
if (THREADS_FOUND)
    link_libraries(Threads::Threads)
endif()

add_executable(game ${src_files})

set_target_properties(game PROPERTIES POSITION_INDEPENDENT_CODE ON)
