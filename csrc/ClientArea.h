#include "GRECT.h"

class ClientArea : public GRECT
{
public:	
	GRECT* parent;
public:
	ClientArea(GRECT* parent,const char* name,int x,int y,int width,int height);
	static const char *MakeChildName(const char* parentName, const char* childName);
};
