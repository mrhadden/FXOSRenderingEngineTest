#ifndef __GRECT__
#define __GRECT__

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class GRECT
{
public:
	static long nextDepth;
	static int  scaler;

public:	
	GRECT(const char* name, int x,int y,int width,int height);
	GRECT(const char* name, int x,int y,int width,int height,long z,int attr);
	
	const char* name = NULL;
	int 	 x;
	int 	 y;
	int 	 width;
	int 	 height;
	long     z;
	int 	 color ;
	int      attr;

	int   orgX = 0;
	int   orgY = 0;
	
	GRECT* clientRect = NULL;
};

#endif