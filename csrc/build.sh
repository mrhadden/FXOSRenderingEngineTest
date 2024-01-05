#!/bin/bash
# Proper header for a Bash script.
# This is run from WSL term to keep things honest
# Need x86_64-w64-mingw32-g++ installed in Ubuntu 
x86_64-w64-mingw32-g++ -municode winmain.c Point.cpp GFXRECT.cpp GFXRECTP.c List.c FXWindow.c pgm.c -lgdi32
