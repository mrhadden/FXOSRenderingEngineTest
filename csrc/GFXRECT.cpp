
#include "GFXRECT.h"

long nextDepth = 1;
int  scaler    = 1;

PGFXRECT AllocRect(const char* name, int x,int y,int width,int height)
{
	return AllocRectEx(name,x,y,width,height,-1,0);
}

PGFXRECT AllocRectEx(const char* name, int x,int y,int width,int height,long z,int attr)
{
	PGFXRECT p = (PGFXRECT)malloc(sizeof(GFXRECT));	
	if(p)
	{
		if(!name)
		{
			char* nname = (char*)malloc(64);
			sprintf(nname,"P:%p",(void*)p);
			name = (const char*)nname;
		}
		
		p->name = name;
		p->x = x * scaler;
		p->y = y * scaler;
		p->width = width * scaler;
		p->height = height * scaler;
		if(z == -1)
			p->z = nextDepth++;
		else
			p->z = z;
		
		p->color = 0;
		p->attr = attr;
	}
	return p;
}

public RECT toRECT(String name)
{
	return new RECT(name,topLeft.x,topLeft.y,bottomRight.x - topLeft.x,bottomRight.y - topLeft.y);
}

static public RECTP toRECTP(RECT r)
{
	return new RECTP(r.x,r.y,r.x + r.width,r.y+r.height);
}
