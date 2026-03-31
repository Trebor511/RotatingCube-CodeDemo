Rotating Cube Demo (C++ Graphics Project)
Overview

This project is a simple 3D rendering demonstration written in C++. It renders a rotating cube using custom math, transformation, and projection logic without relying on a full game engine.

The goal of this project was to build a deeper understanding of the fundamental graphics pipeline, including 3D transformations, camera projection, and rendering from first principles.

Features
Custom 3D vector and matrix math
Manual model transformation (rotation, translation)
Perspective projection from 3D → 2D screen space
Line-based cube rendering
Real-time rotation update loop
No game engine dependencies
Technical Breakdown
1. Transformation Pipeline

The cube’s vertices are transformed using standard 3D transformation steps:

Model Space → World Space
Rotation matrices applied per frame
World Space → View Space
Camera positioning (if applicable)
View Space → Projection
Perspective projection applied manually

This pipeline is implemented entirely in C++ to reinforce understanding of how engines handle transformations internally.

2. Rotation System

The cube rotates continuously over time using rotation matrices.

Rotation is applied incrementally each frame
Supports rotation on multiple axes (X, Y, Z)
Uses trigonometric functions (sin, cos) for matrix construction
3. Projection

A custom perspective projection converts 3D coordinates into 2D screen space.

Simulates depth by scaling based on distance from the camera
Demonstrates how 3D scenes are flattened onto a 2D display
4. Rendering

The cube is rendered using line drawing between projected vertices.

Edges are defined by vertex index pairs
Lines are drawn to represent cube geometry
Focus is on clarity and correctness rather than visual fidelity
Design Goals

This project was built with the following goals:

Reinforce understanding of core graphics concepts
Practice C++ math-heavy programming
Build systems without relying on engine abstractions
Maintain clear and readable code structure
What I Learned
How transformation matrices affect object positioning and rotation
The relationship between 3D coordinates and 2D screen projection
Structuring math-heavy code for clarity and correctness
Debugging visual output by validating transformation steps
Possible Improvements

If extended further, I would:

Add a proper camera system with configurable position and rotation
Implement back-face culling
Introduce depth buffering (Z-buffer)
Render filled triangles instead of wireframe lines
Optimize math operations using SIMD or more efficient structures
How to Run
Clone the repository
Open the project in Visual Studio
Build and run the solution
