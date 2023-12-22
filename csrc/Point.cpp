#include "Point.h"

PFXPOINT AllocPoint(int x, int y)
{
	PFXPOINT p = (PFXPOINT)malloc(sizeof(FXPOINT));
	if(p)
	{
		memset(p,0,sizeof(FXPOINT));
		p->x =x;
		p->y = y;
	}
	return p;
}