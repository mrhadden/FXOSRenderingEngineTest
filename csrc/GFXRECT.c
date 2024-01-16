#include "GFXRECT.h"

long nextDepth = 1;
int  scaler    = 1;

long NextDepth()
{
	return ++nextDepth;
}

PGFXRECT UpdateRect(PGFXRECT target,int x,int y,int width,int height)
{
	if(!target)
		return NULL;
	
	target->x = x;
	target->y = y;
	target->width = width;
	target->height = height;
	
	return target;
}

PGFXRECT AllocRect(const char* name, int x,int y,int width,int height)
{

	return AllocRectEx(name,x,y,width,height,-1,0);
}

PGFXRECT AllocRectEx(const char* name, int x,int y,int width,int height,long z,int attr)
{
	PGFXRECT p = (PGFXRECT)malloc(sizeof(GFXRECT));	
	if(p)
	{
		memset(p,0,sizeof(GFXRECT));
		
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
		p->renderColor = p->color;
		p->attr = attr;
		p->nonclientList = NULL;
		p->clientRect  = NULL;
	}
	return p;
}

PGFXRECT fxCopyRect(PGFXRECT src)
{
	PGFXRECT p = (PGFXRECT)malloc(sizeof(GFXRECT));	
	if(p)
	{
		char* name = NULL;
		if(src->name)
		{
			char* nname = (char*)malloc(64);
			strcpy(nname,src->name);
			name = nname;
		}
		
		p->name = (const char*)name;
		p->x = src->x;
		p->y = src->y;
		p->width = src->width;
		p->height = src->height;
		p->z = src->z;
		
		p->color = src->color;
		p->renderColor = src->renderColor;
		p->attr = src->attr;

		p->clientRect = src->clientRect;
	}
	return p;	
}
