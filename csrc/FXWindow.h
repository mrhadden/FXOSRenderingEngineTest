#ifndef _FX_WINDOW
#define _FX_WINDOW

#include "GFXRECT.h"
#include "List.h"

typedef struct _fx_metrics
{
    int metric;
} FXMETRICS;

#define FXM_BORDERSIZE      2
#define FXM_TRIMWIDTH       4
#define FXM_TITLEHEIGHT     16
#define FXM_TRIMHEIGHT      16

typedef void (*ApplyWindowAttr)(HDC hdc,PGFXRECT winRect);

typedef void (*FXWndProc)(HDC hdc,PGFXRECT winRect);

RECT* ToWinRECT(RECT* rect, GFXRECT* grect);

void AddCloseGadget(HDC hdc,PGFXRECT winRect);
void AddMinGadget(HDC hdc,PGFXRECT winRect);
void AddTitleGadget(HDC hdc,PGFXRECT winRect);

typedef struct _fx_window
{
    PGFXRECT    winRect;
    PFXNODELIST chromeList;
} FXWINDOW;


#endif