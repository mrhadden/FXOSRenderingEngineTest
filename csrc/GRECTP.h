#ifndef __GRECTP_H__
#define __GRECTP_H__

#include "Point.h"
#include "GRECT.h"

class GRECTP
{
public:
	Point* topLeft;
	Point* bottomRight;
	
	GRECTP(int left,int top, int right,int bottom);
	GRECTP();
	GRECT* toRECT(char* name);
	static GRECTP* toRECTP(GRECT* r);
};

#endif