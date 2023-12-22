#include "GRECTP.h"

GRECTP::GRECTP(int left,int top, int right,int bottom)
{
	GRECTP();
	topLeft->x = left;
	topLeft->y = top;
	
	bottomRight->x = right;
	bottomRight->y = bottom;		
}
	
GRECTP::GRECTP()
{
	topLeft = new Point(0,0);
	bottomRight = new Point(0,0);
}

GRECT* GRECTP::toRECT(char* name)
{
	return new GRECT(name,topLeft->x,topLeft->y,bottomRight->x - topLeft->x,bottomRight->y - topLeft->y);
}

GRECTP* GRECTP::toRECTP(GRECT* r)
{
	return new GRECTP(r->x,r->y,r->x + r->width,r->y+r->height);
}

