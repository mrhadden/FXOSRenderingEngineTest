
#include "GFXRECTP.h"

PGFXRECTP AllocRectP(int left,int top, int right,int bottom)
{
	PGFXRECTP p = (PGFXRECTP)malloc(sizeof(GFXRECTP));
	if(p)
	{
		memset(p,0,sizeof(GFXRECTP));
		
		p->topLeft = AllocPoint(left,top);
		p->bottomRight = AllocPoint(right,bottom);
	}
	return p;
}

PGFXRECT ToRECT(PGFXRECTP src,const char* rectName)
{
	return AllocRect(rectName,
	                 src->topLeft->x,
					 src->topLeft->y,
					 src->bottomRight->x - src->topLeft->x,
	                 src->bottomRight->y - src->topLeft->y);
}

PGFXRECTP ToRECTP(PGFXRECT r)
{
	return AllocRectP(r->x,r->y,r->x + r->width,r->y+r->height);
}

