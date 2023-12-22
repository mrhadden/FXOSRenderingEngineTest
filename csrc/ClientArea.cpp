#include "ClientArea.h"

const char *ClientArea::MakeChildName(const char* parentName, const char* childName)
{
	char* newName = new char(128);
	strcpy_s(newName, 64, parentName);
	strcat_s(newName, 64, childName);
	return newName;
}

ClientArea::ClientArea(GRECT* parent,const char* name,int x,int y,int width,int height) :
GRECT(MakeChildName(parent->name,"-child"), x , y, width, height)
{
	this->parent = parent;
}
