# Rotating Cube Demo (C++)

## Overview
This project is a **C++ software rendering demo** that displays a rotating 3D cube without using a game engine or graphics API.

The goal was to better understand how 3D graphics work by building a small rendering pipeline from scratch, including transformations, projection, and rasterization.

---

## Features
- Custom **matrix and vector math system**
- **World, View, and Projection transformations**
- Perspective projection from 3D space to screen space
- **Triangle rasterization using barycentric coordinates**
- **Depth buffer (Z-buffer)** for correct rendering order
- Basic **vertex and pixel shader system**
- Real-time cube rotation using a timer

---

## Highlights

### Custom Rendering Pipeline
The project implements a simplified version of the graphics pipeline:
- Vertex transformation (World → View → Projection)
- Perspective divide
- Conversion to screen space

---

### Triangle Rasterization
Triangles are drawn using a **bounding box approach** and tested with barycentric coordinates to determine if a pixel is inside the triangle.

---

### Depth Buffering
A depth buffer is used to ensure that closer pixels overwrite farther ones, preventing visual overlap issues.

---

### Shader System
A simple shader system is implemented using function pointers:
- Vertex shader handles transformations
- Pixel shader controls final color output

---

## What I Learned
- How 3D transformations and projection work
- How triangles are rasterized on the CPU
- How depth buffering affects rendering order
- How to structure math-heavy systems in C++

---

## How to Run
1. Clone the repository  
2. Open in **Visual Studio**  
3. Build and run
   OR
1. Download the .zip file and extract
2. Run PooreRobert_Assignment2.exe
