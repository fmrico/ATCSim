ATCSim
======

Air Traffic Control Simulator

Author: Francisco Martín Rico fmrico@gmail.com

## Introduction

  This project contains a set of C++ folders and scripts that make an Air Simulator based on landing maneuvering.

## System Pre-requirements

  - Ubuntu 18.04 LTS (You can check your Ubuntu version through this command in your system terminal: cat /etc/issue)

  The downloadable file can be found here: https://www.ubuntu.com/download/desktop

## Language Pre-requirements

  C/C++/Java compilators must be installed. They can be downloaded from the computer terminal through the following command:

      - sudo apt-get install build-essential

## Libraries Pre/Minimum-requirements

  Some Ice and Glut communication libraries must be installed.
  Whether are installed or not, these libraries can be checked on your computer terminal:

    - dpkg -l| grep freeglut3
    - dpkg -l| grep libice

  If they are not installed, they can be downloaded and installed from the computer terminal through the following commands:

    - sudo apt-get install freeglut3
    - sudo apt-get install freeglut3-dev

    - sudo apt-get install libice6
    - sudo apt-get install libice-dev
    - sudo apt-get install libzeroc-ice-dev
    - sudo apt-get install libzeroc-ice-dev:i386

  NOTE: you can install the latest version of Ice with the following command:

    - sudo apt-get install libzeroc-ice3.7

## Compilation

  To compilate ATCSim you must proceed the following steps:

    - First, go to your workspace folder and clone the repository:

      - git clone https://github.com/fmrico/ATCSim.git

    - Then, create a building folder and compilate:

      - cd ATCSim
      - mkdir build
      - cd build
      - cmake ..
      - make

  This commands will deliver two executables: ATCSim and cppgui.

## Execution

  To execute ATCSim, you must have opened two system terminals for ATCSim and cppgui executables.
  The path of both files is the same: $ ../ATCSim/build
  To execute ATCSim:

    - First, launch the ATCSim executable: $ ../ATCSim/build/ATCSim

    - Then, in the other system terminal launch the cppgui executable: $ ../ATCSim/build/cppgui
