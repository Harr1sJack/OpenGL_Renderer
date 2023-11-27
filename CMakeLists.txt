cmake_minimum_required(VERSION 3.12)
project(OpenGL)

# Find OpenGL package
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 20) 

# Include directories
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/libraries/include)

set(SOURCE_FILES 
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${CMAKE_SOURCE_DIR}/glad.c
    ${CMAKE_SOURCE_DIR}/ShaderClass.cpp
    ${CMAKE_SOURCE_DIR}/Camera.cpp
    ${CMAKE_SOURCE_DIR}/Model.cpp
    ${CMAKE_SOURCE_DIR}/ EBO.cpp
    ${CMAKE_SOURCE_DIR}/VAO.cpp
    ${CMAKE_SOURCE_DIR}/VBO.cpp
    ${CMAKE_SOURCE_DIR}/Texture.cpp
    ${CMAKE_SOURCE_DIR}/stb.cpp
    ${CMAKE_SOURCE_DIR}/Mesh.cpp
)
# Create the executable
add_executable(OpenGL ${SOURCE_FILES} main.cpp)

# Include directories for the target
target_include_directories(OpenGL PRIVATE ${CMAKE_SOURCE_DIR}/libraries/include)

# Link the executable with the OpenGL libraries
target_link_libraries(OpenGL ${OPENGL_LIBRARIES} ${CMAKE_SOURCE_DIR}/libraries/libs/glfw3.lib)
