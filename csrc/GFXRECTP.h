#ifndef __GRECTP__
#define __GRECTP__

#include "Point.h"
#include "GFXRECT.h"

#define RECTMAX(a,b) ((a) > (b) ? (a) : (b))
#define RECTMIN(a,b) ((a) < (b) ? (a) : (b))

typedef struct _fx_rectp
{
	PFXPOINT topLeft;
	PFXPOINT bottomRight;
} GFXRECTP;
typedef GFXRECTP* PGFXRECTP;
                   
	
PGFXRECTP AllocRectP(int left,int top, int right,int bottom);
PGFXRECT  ToRECT(PGFXRECTP src,const char* rectName);
PGFXRECTP ToRECTP(PGFXRECT r);

#endif