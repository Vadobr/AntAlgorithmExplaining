# Ant Colony Optimization with Genetic Algorithm

This project demonstrates the combination of **Ant Colony Optimization (ACO)** with a **Genetic Algorithm (GA)**. The program provides an interactive visualization of how these two optimization techniques work together. The task set for the algorithm is: to travel the path with the maximum product of edge weights and return in N steps at most.

## Features
- **Ant Colony Optimization (ACO)**: Models the behavior of ants to find optimal solutions.
- **Genetic Algorithm (GA)**: Uses selection, crossover, and mutation to enhance the search process.
- **Multithreading without mutexes**: Efficient parallel processing without slow synchronization mechanisms. Including reading from a file.
- **Data generator**: A separate program for generating problems to solve.
- **Visualization with Qt**: The simulation is rendered using the **Qt** framework.
- **Cross-Platform Compatibility**: While tested on Windows, the code does not contain platform-specific dependencies.
- **Visual Studio Project Files**: The project includes **Visual Studio** solution and build files for easy setup.

## Requirements
- **C++**
- **Qt framework**
- **Visual Studio (recommended for build)**

## Installation & Usage
1. Clone the repository:
   ```sh
   git clone <repository-url>
   cd <project-directory>

2. Open the Visual Studio solution file (.sln).
   
3. Replace the Qt version with the one installed on your computer in the extension settings:
   
   3.1 Extentions  $\textcolor{blue}{→}$  Qt VS Tools _(or similar)_  $\textcolor{blue}{→}$  Qt version
   
   3.2 Project  $\textcolor{blue}{→}$  _\<project name\>_ Properties  $\textcolor{blue}{→}$  Qt Project Settins  $\textcolor{blue}{→}$  Qt Installation
   
5. Build and run the project

## Acknowledgments
- Qt for GUI development
- Various open-source references on ACO and GA techniques
