#ifndef __FXPOINT_H__
#define __FXPOINT_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct fx_point
{
	int x;
	int y;
} FXPOINT;
typedef FXPOINT* PFXPOINT;

PFXPOINT AllocPoint(int x, int y);

#endif