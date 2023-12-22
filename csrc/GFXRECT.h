#ifndef __GRECT__
#define __GRECT__

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _fx_rect
{
	const char* name;
	int 	x;
	int 	y;
	int 	width;
	int 	height;
	long    z;
	int 	color ;
	int     attr;

	int   	orgX = 0;
	int   	orgY = 0;
	
	struct _fx_rect* 	clientRect;
} GFXRECT;
typedef GFXRECT* PGFXRECT;

PGFXRECT AllocRect(const char* name, int x,int y,int width,int height);
PGFXRECT AllocRectEx(const char* name, int x,int y,int width,int height,long z,int attr);




#endif