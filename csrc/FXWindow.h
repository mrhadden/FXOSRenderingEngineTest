#ifndef _FX_WINDOW
#define _FX_WINDOW

#include "GFXRECT.h"
#include "GFXRECTP.h"
#include "List.h"

typedef struct _fx_metrics
{
    int metric;
} FXMETRICS;

typedef struct _fx_environment
{
    PFXNODELIST knownRects;
    PFXNODELIST renderList;

    PFXNODELIST recNodes     ;
    PFXNODELIST hitlist      ;
    PFXNODELIST interlist    ;
    PGFXRECT    currentFocus ;
    PGFXRECT    desktop      ;
    PGFXRECT  	hoverFocus   ;
} FXUIENV;
typedef FXUIENV* PFXUIENV;

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


PGFXRECT GetSelectedRect(PFXNODELIST objList,int mx,int my,int whichAttr);
PFXPOINT RectToPoint(PGFXRECT r,int whichPoint);
BOOL IsOverlappedPoints(PFXPOINT l1, PFXPOINT r1, PFXPOINT l2, PFXPOINT r2);
BOOL IsOverlappedRects(PGFXRECT r1,PGFXRECT r2);
PFXNODELIST GetOverLappedRect(PGFXRECT r,PFXNODELIST objList);
PGFXRECT Intersection( PGFXRECT r, PGFXRECT rhs );



#endif