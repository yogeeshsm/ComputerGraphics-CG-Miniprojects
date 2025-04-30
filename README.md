# ✈️ 3D Airport Model using OpenGL

This mini-project is a 3D graphical representation of an airport using **OpenGL** and **GLUT**. It showcases key elements such as runways, airplanes, terminals, control towers, and dynamic animations like plane takeoff and landing.

## 📌 Project Overview

The 3D Airport Model aims to demonstrate basic to intermediate OpenGL concepts such as:

- 3D transformations
- Object modeling
- Camera positioning
- Lighting and shading
- Animation and movement
- User interaction (keyboard controls)

## 🚀 Features

- ✈️ Airplanes moving on the runway and taking off
- 🏢 Airport terminal building and control tower
- 🌴 Trees and scenery elements
- ☁️ Sky simulation with a simple day-night toggle
- 🔧 User-interactive controls for viewing angles

## 🛠️ Technologies Used

- **OpenGL**
- **GLUT (OpenGL Utility Toolkit)**
- **C/C++**

## 🎮 Controls

| Key | Action |
|-----|--------|
| `w` | Move camera forward |
| `s` | Move camera backward |
| `a` | Rotate view left |
| `d` | Rotate view right |
| `r` | Reset camera |
| `t` | Toggle takeoff/landing animation |
| `n` | Toggle day/night mode |
| `Esc` | Exit the application |

## 🔧 How to Run

1. **Install required tools:**
   - C++ Compiler (GCC/G++)
   - OpenGL and GLUT libraries

2. **Compile the code:**

   On **Linux/macOS**:
   ```bash
   g++ airport.cpp -o airport -lGL -lGLU -lglut
   ./airport
