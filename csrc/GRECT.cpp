
#include "GRECT.h"

long GRECT::nextDepth = 1;
int  GRECT::scaler    = 1;

GRECT::GRECT(const char* name, int x,int y,int width,int height)
{
	GRECT(name,x,y,width,height,-1,0);
}

GRECT::GRECT(const char* name, int x,int y,int width,int height,long z,int attr)
{
	if(!name)
	{
		char* nname = (char*)malloc(64);
		sprintf(nname,"P:%p",(void*)this);
		name = (const char*)nname;
	}
	
	this->name = name;
	this->x = x * scaler;
	this->y = y * scaler;
	this->width = width * scaler;
	this->height = height * scaler;
	if(z == -1)
		this->z = nextDepth++;
	else
		this->z = z;
	
	this->color = 0;
	this->attr = attr;
}
