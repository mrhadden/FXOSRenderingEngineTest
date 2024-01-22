#
#
#
set -x
x86_64-w64-mingw32-g++ -municode \
FXPOINT.c \
GFXRECT.c \
GFXRECTP.c \
FXLIST.c \
FXWindow.c \
pgm.c \
FXDrivers.c \
WindowsVideoDriver.c \
WindowsHAL.c \
FXHAL.c \
console.c \
conmain.c \
-lgdi32 -o console.exe

