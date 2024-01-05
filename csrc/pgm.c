

#include "pgm.h"
#include "FXWindow.h"

HFXFONT hEnvious = LoadFont("font/Hourglass.fnt");

BOOL clientProc(HDC hdc, PGFXRECT winRect)
{
    RECT target;

	//const char* caption = "Client Text\0";
	const char* caption = "Client Workbench\0";

    ToWinRECT(&target, winRect);

	fxRenderText(hdc,caption,
	             target.left + 1 + FXM_BORDERSIZE,
			     target.top  + 1 + FXM_BORDERSIZE,
			     hEnvious, 
			     (COLORREF)RGB(0,0,0));

	fxRenderText(hdc,GetFontName(hEnvious),
	             target.left + 1 + FXM_BORDERSIZE,
			     target.top  + 1 + FXM_BORDERSIZE + 10,
			     hEnvious, 
			     (COLORREF)RGB(0,0,0));
			  
	for(int x=0;x<200;x++)
		SetPixel(hdc,
				 target.left + 1 + FXM_BORDERSIZE + x,
				 target.top  + 1 + FXM_BORDERSIZE + 30,
				 ((COLORREF)RGB(255,0,0)));

	return TRUE;
}
