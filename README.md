# Portal-Simulator-Non-Euclidean-Spaces
OpenGL simulation of portals and non-euclidean spaces in C++. Created by Alfred Sporre &amp; Mattias Beming as part of the computer graphics course TSBK07 at Linköping University.

---
## Setup
For setting up the project follow these steps:
1. Clone project
2. Download visual studio code (at least version 1.56)

### Configuring Windows workspace

The following libraries are required for the project to work.
Get at least these versions: 
- MinGW (x64-native)
- C++17 (GCC 7 or higher) (Currently running GCC 9.2.0)
- GLFW3 (3.3) 
- GLM (0.9.9.6)

We used a MinGW distribution, which contains all the listed libraries and can be found [here](https://nuwen.net/mingw.html "NUWEN").
Note: If the libraries are gathered from other sources - modifications to `CmakeLists.txt` are most likely required. 

### Configuring Linux workspace
install GLFW3 and GLM from your package manager. 
Make sure that your GCC has support for C++17. 

---
## How to run the project
We have added build-task instructions in the workspace for visual studio code where we use `CTRL + SHIFT + B` to **Build &amp; Run** the project. 
This is a default keybind which can be modified in file `tasks.json`.

