
#include "FXWindow.h"

RECT* ToWinRECT(RECT* rect, GFXRECT* grect)
{
	rect->top = grect->y;
	rect->left = grect->x;
	rect->right = grect->x + grect->width;
	rect->bottom = grect->y + grect->height;	
	return rect;
}

void AddCloseGadget(HDC hdc,PGFXRECT winRect)
{
    //OutputDebugStringA("AddCloseGadget...\n");
    RECT target;

    target.left   = winRect->x + winRect->width - (FXM_BORDERSIZE * 2) - 10;
    target.top    = winRect->y + FXM_BORDERSIZE + (FXM_TITLEHEIGHT / 2) - 5;
    target.right  = target.left + 10;
    target.bottom = target.top + 10;
    
    FrameRect(hdc, &target ,CreateSolidBrush(RGB(255,255,255)));
}

void AddMinGadget(HDC hdc, PGFXRECT winRect)
{
    //OutputDebugStringA("AddCloseGadget...\n");
    RECT target;

    for(int i = 0;i<3;i++)
    {
        target.left   = winRect->x + FXM_BORDERSIZE + 1;
        target.top    = winRect->y + (FXM_BORDERSIZE * 2) + (i*4);
        target.right  = winRect->x + winRect->width - (FXM_BORDERSIZE * 2) - 10 - 2;
        target.bottom = target.top + 4 ;
        
        FrameRect(hdc, &target ,CreateSolidBrush(RGB(255,255,255)));
    }
}

void AddTitleGadget(HDC hdc, PGFXRECT winRect)
{
    RECT target;

    ToWinRECT(&target, winRect);

    SetTextColor(hdc,((COLORREF)RGB(255,255,255)));
    SetBkColor(hdc,((COLORREF)winRect->renderColor));

    TextOutA(hdc,
                target.left + 1 + FXM_BORDERSIZE,
                target.top + FXM_BORDERSIZE,
                winRect->name,
                winRect->szname);	
}