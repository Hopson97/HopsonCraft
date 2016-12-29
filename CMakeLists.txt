cmake_minimum_required(VERSION 3.1)
project(MattCraft)

set (CMAKE_CXX_STANDARD 14)
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

file(GLOB src_files
    Source/Game_States/*.cpp
    Source/GUI/*.cpp
    Source/Input/*.cpp
    Source/Inventory/*.cpp
    Source/Item/*.cpp
    Source/Maths/*.cpp
    Source/Model/*.cpp
    Source/Mob/*.cpp
    Source/OpenGL/*.cpp
    Source/PostFX/*.cpp
    Source/Renderer/*.cpp
    Source/Shaders/*.cpp
    Source/Texture/*.cpp
    Source/World/*.cpp
    Source/Util/*.cpp
    Source/*.cpp
    Source/World/Chunk/*.cpp
    Source/World/Block/*.cpp
    Source/World/Block/Block_Type/*.cpp
    Source/World/Block/Updateable/*.cpp
    Source/World/Gen/*.cpp)

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
