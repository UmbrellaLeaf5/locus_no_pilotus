# Locus No Pilotus: Trajectory Calculator

**Project of four first grade MIPT DAFE/RSE students (for engineering practical work in the second semester) in Qt C++**

## [Documentation](https://umbrellaleaf5.github.io/locus_no_pilotus/index.html)
Project's [documentation](https://umbrellaleaf5.github.io/locus_no_pilotus/index.html) generated with Doxygen with [convenient CSS theme](#used-libs-and-packages).

# Contents
  * [Description](#description)
  * [Installation and configuring](#installation-and-configuring "with using MSYS")
  * [Used libs and packages](#used-libs-and-packages "we are using GitHub submodules feature 😎")
  * [Authors](#authors "the best guys")

## Description

In this project, we are developing an application that calculates the trajectory of a flying delivery robot that collects valuable cargo from control points: **Targets**. 
On its way, it may encounter high mountains that it cannot fly over: **Hills**; or elliptical territories that are impossible to visit due to climate conditions: **TrappyCircles**. 
Also, through some control points, the robot is simply unable to move, as the cargo may not be ready for transportation at that time, these are **TrappyLines**. 

The robot's trajectory is calculated using several mathematical algorithms: [...]. 
The graphical interface for constructing the trajectory was created using [Qt](#used-libs-and-packages) and [QCustomPlot](#used-libs-and-packages). 

In the application, you can add objects using window forms, interact with the trajectory calculation plot using the mouse cursor, create and open files in ```.json``` format with a specific style for this application. Editing objects can also be done with cursors or using a special dynamic input field with tables, opened in a separate window mode or embedded in the main one. 

*We strongly recommend that you install our application using the instructions below and try it out!*

## Installation and configuring

#### On Windows 64 bit system
1) Install **[MSYS2](https://www.msys2.org/)** to any convenient folder as compiler setup
> *P.S. of course you can try install all the libs and packages used in repo manually, but our team got pain and tears trying to install Boost on MINGW in this way, so we recommend to install MSYS (besides, it is an excellent tool for compiling any other C++ and etc. projects)*

2) Open ```MSYS2 MSYS``` console, copy the command below and paste it with ```Shift+Ins``` or ```RBM and 'Paste'``` to download all the packages used in our project
```
  pacman -S mingw-w64-x86_64-gcc
  pacman -S mingw-w64-x86_64-gdb
  pacman -S mingw-w64-x86_64-gdb-multiarch
  pacman -S mingw-w64-x86_64-libgccjit 
  pacman -S mingw-w64-x86_64-libmangle-git 
  pacman -S mingw-w64-x86_64-make
  pacman -S mingw-w64-x86_64-ninja
  pacman -S mingw-w64-x86_64-pkgconf
  pacman -S mingw-w64-x86_64-boost
  pacman -S mingw-w64-x86_64-qt-creator
  pacman -S mingw-w64-x86_64-qt6-3d
  pacman -S mingw-w64-x86_64-qt6-activeqt
  pacman -S mingw-w64-x86_64-qt6-charts 
  pacman -S mingw-w64-x86_64-qt6-connectivity 
  pacman -S mingw-w64-x86_64-qt6-datavis3d
  pacman -S mingw-w64-x86_64-qt6-doc 
  pacman -S mingw-w64-x86_64-qt6-grpc 
  pacman -S mingw-w64-x86_64-qt6-httpserver 
  pacman -S mingw-w64-x86_64-qt6-imageformats 
  pacman -S mingw-w64-x86_64-qt6-languageserver
  pacman -S mingw-w64-x86_64-qt6-location 
  pacman -S mingw-w64-x86_64-qt6-lottie 
  pacman -S mingw-w64-x86_64-qt6-multimedia 
  pacman -S mingw-w64-x86_64-qt6-networkauth 
  pacman -S mingw-w64-x86_64-qt6-quick3dphysics 
  pacman -S mingw-w64-x86_64-qt6-quickeffectmaker 
  pacman -S mingw-w64-x86_64-qt6-quicktimeline 
  pacman -S mingw-w64-x86_64-qt6-remoteobjects 
  pacman -S mingw-w64-x86_64-qt6-scxml
  pacman -S mingw-w64-x86_64-qt6-sensors 
  pacman -S mingw-w64-x86_64-qt6-serialbus 
  pacman -S mingw-w64-x86_64-qt6-speech 
  pacman -S mingw-w64-x86_64-qt6-virtual keyboard 
  pacman -S mingw-w64-x86_64-qt6-webchannel 
  pacman -S mingw-w64-x86_64-qt6-webview 
  pacman -S mingw-w64-x86_64-tools-git
  pacman -S mingw-w64-x86_64-cmake
```

3) Install **[Git Bash](https://gitforwindows.org/)** to any convenient folder (if you haven't get it yet) 

4) Open ```Git Bash``` and use command like ```cd C:/CodeFolder``` to go to the folder where you usually save the code

5) Clone our repo with including submodules to such folder:
``` 
  git clone --recurse-submodules https://github.com/UmbrellaLeaf5/locus_no_pilotus 
```

6) Open the MSYS bin folder in path like ```C:\YourPathToMsys\msys64\mingw64\bin``` than find and start ```qtcreator.exe```

7) In folder with our project clone find ***CMakeLists.txt*** and open it with QtCreator

8) Set the compiler that allow *CMake* configuration in the kits list and click ```Configure Project```

9) To use the full working version: **Build** (hammer button in the lower left corner) the project, and after ending process with error use ***Build > Run CMake*** in the top menu to reconfigure and fix error with including QCustomPlot
> *P.S. because of using QCustomPlot as GitHib submodule with repo author's solution to include QCustomPlot files to extra *lib* folder, we have problem with Qt autogen files (was fixed by using regex in extra cmake_scripts and the need to reconfigure the project after building)*

10) Now you can use full working project with **Run** (green triangle button in the lower left corner)!

#### On Linux system

*Coming soon...*

> Much respect and help for this installation method to [George Sukhanov](https://github.com/TheFueRr "our colleague with an equally interesting project on processing experimental data")!

## Used libs and packages
* [CMake](https://cmake.org/): main project build system
* [Qt](https://www.qt.io/): main project library for full-working program
* [QCustomPlot](https://www.qcustomplot.com/): library for drawing all objects on same place with autoscaling ([submodule](https://github.com/legerch/QCustomPlot-library "reference for submodule with lib in GitHub"))
* [IceCream-Cpp](https://github.com/renatoGarcia/icecream-cpp): library for simple code debugging (we really recommend to use it in C++ projects)
* [Doxygen](https://www.doxygen.nl/): full documentation generation
* [Doxygen Awesome](https://github.com/jothepro/doxygen-awesome-css): convenient CSS theme for Doxygen HTML documentation (it is really awesome)
* [Flaticon](https://www.flaticon.com/): perfect icons source
* [GeoGebra](https://www.geogebra.org/): best platform for geometry calculations

## Authors
**[Romanov Fedor](https://github.com/Romanov-Fedor "math greatest gigachad (Desmos proger)")**

**[Rybalkin Ilya](https://github.com/Stargazer2005 "traveling salesman problem and Dijkstra algos enjoyer")**

**[Akramov Nikita](https://github.com/MrWh1teF0x "jsons, gui forms and cursors hero")**

**[Krivoruchko Dmitry](https://github.com/UmbrellaLeaf5 "repo manager and gui guy")**
