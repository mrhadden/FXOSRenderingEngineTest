
#ifndef __PGM_H
#define __PGM_H

#include <windows.h>
#include "GFXRECT.h"

typedef struct _pgm_data
{
	int nIndex;
	const char* caption;
}
PGMDATA;

typedef struct _ctl_data
{
	char text[512];
	int background;
}
CTLDATA;


BOOL clientProc1(HDC hdc, int msgId, int wParam, int lParam, PGFXRECT winRect);
BOOL clientProc2(HDC hdc, int msgId, int wParam, int lParam, PGFXRECT winRect);
BOOL clientProc3(HDC hdc, int msgId, int wParam, int lParam, PGFXRECT winRect);

BOOL controlProc(HDC hdc, int msgId, int wParam, int lParam, PGFXRECT winRect);

#endif
