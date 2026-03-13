# OpenGL 3D Renderer
A cross-platform desktop application developed in C++ using the OpenGL API to explore graphics pipeline architecture and memory management.

## Technical Implementation
* Graphics Pipeline: Developed custom Vertex and Fragment shaders using GLSL to handle lighting and material properties.
* Coordinate Systems: Implemented the complete MVP (Model-View-Projection) matrix transformation flow.
* Camera System: Engineered a 3D fly-through camera using GLM for matrix mathematics, supporting real-time user input.
* Asset Management: Integrated a .gltf loader to parse and render 3D meshes with texture mapping.
* Build Automation: Configured CMake for cross-platform build support and dependency management (GLFW, Glad).

## Environment and Dependencies
* Language: C++17
* Libraries: GLFW, Glad, GLM
* Tools: CMake, VS Code
