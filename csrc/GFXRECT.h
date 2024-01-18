#ifndef __GRECT__
#define __GRECT__

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "FXLIST.h"

#define FX_ATTR_HIDDEN		 0
#define FX_ATTR_VISIBLE		 2
#define FX_ATTR_CREATED		 4
#define FX_ATTR_MOVED        8
#define FX_ATTR_BACKGROUND   16
#define FX_ATTR_DESKTOP		 0x8000
#define FX_ATTR_INVALID		 0x4000
#define FX_ATTR_ERASE        0x2000
#define FX_ATTR_DELETE       0x1000

typedef struct _fx_rect_region
{
	int 	x;
	int 	y;
	int 	width;
	int 	height;
} GRECT;
typedef GRECT* PGRECT;

typedef struct _fx_rect
{
	const char* name;
	int 	x;
	int 	y;
	int 	width;
	int 	height;
	long    z;
	int 	color;
	int 	renderColor;
	int     attr;
	int   	orgX;
	int   	orgY;
	int     szname;
	PFXNODELIST      nonclientList;
	struct _fx_rect* parent;
	struct _fx_rect* clientRect;
	void*  			 wndProc;
	void*  			 wndData;
	int				 wndInit;    
} GFXRECT;
typedef GFXRECT* PGFXRECT;

PGFXRECT AllocRect(const char* name, int x,int y,int width,int height);
PGFXRECT AllocRectEx(const char* name, int x,int y,int width,int height,long z,int attr);
PGFXRECT fxCopyRect(PGFXRECT src);

PGFXRECT UpdateRect(PGFXRECT target,int x,int y,int width,int height);

long NextDepth();



#endif