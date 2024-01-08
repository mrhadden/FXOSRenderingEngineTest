#!/usr/bin/env bash
# Proper header for a Bash script.
# This is run from WSL term to keep things honest
# Need x86_64-w64-mingw32-g++ installed in Ubuntu 
set -x
x86_64-w64-mingw32-g++ -municode x86_64-w64-mingw32-g++ -municode winmain.c FXPOINT.c GFXRECT.c GFXRECTP.c FXLIST.c FXWindow.c pgm.c FXDrivers.c WindowsVideoDriver.c WindowsHAL.c -lgdi32 
