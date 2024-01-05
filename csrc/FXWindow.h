#ifndef _FX_WINDOW
#define _FX_WINDOW

#include <stdint.h>

#include "GFXRECT.h"
#include "GFXRECTP.h"
#include "List.h"

#include "Hourglass.h"

typedef struct _fx_metrics
{
    int metric;
} FXMETRICS;

typedef struct _fx_ui_state
{
	PGFXRECT	    desktop;
	BOOL 		    dragOn;
	FXPOINT 	    dragStart; 
    FXPOINT 	    dragEnd; 
	FXPOINT 	    dragOffset; 
    void* 	        dragArea;
    BOOL            isNonClient;
    PGFXRECT        focusCurrent;
    PGFXRECT  	    focusHover;
    struct timeval  leftClickTime;
    struct timeval  rightClickTime;
} FXUISTATE;
typedef FXUISTATE* PFXUISTATE;

typedef struct _fx_environment
{
    PFXNODELIST knownRects;
    PFXNODELIST renderList;
    PFXNODELIST intersectionList;
	PFXUISTATE  state;
} FXUIENV;
typedef FXUIENV* PFXUIENV;


typedef struct _fx_resheader
{
	char sig[4];
	char type[4];
    char width;
	char height;
    char fontName[32];
	char data;
}HFXRESH;
typedef HFXRESH* PHFXRESH;

typedef const char* HFXFONT;

#define FXM_BORDERSIZE      2
#define FXM_TRIMWIDTH       4
#define FXM_TITLEHEIGHT     18
#define FXM_TRIMHEIGHT      16

typedef PGFXRECT (*ApplyWindowAttr)(HDC hdc,PGFXRECT winRect);

typedef BOOL (*FXWndProc)(HDC hdc,PGFXRECT winRect);

RECT* ToWinRECT(RECT* rect, GFXRECT* grect);
PGFXRECT FromWinRECT(RECT* rect);

PGFXRECT AddCloseGadget(HDC hdc,PGFXRECT winRect);
PGFXRECT AddTitleBarGadget(HDC hdc,PGFXRECT winRect);
PGFXRECT AddTitleGadget(HDC hdc,PGFXRECT winRect);

typedef struct _fx_window
{
    PGFXRECT    winRect;
    PFXNODELIST chromeList;
} FXWINDOW;

PFXUIENV InitUIEnvironment();
BOOL PointInRect(PGFXRECT r,int mx,int my);
PGFXRECT GetSelectedRect(PFXNODELIST objList,int mx,int my,int whichAttr);
PFXPOINT RectToPoint(PGFXRECT r,int whichPoint);
BOOL IsOverlappedPoints(PFXPOINT l1, PFXPOINT r1, PFXPOINT l2, PFXPOINT r2);
BOOL IsOverlappedRects(PGFXRECT r1,PGFXRECT r2);
PFXNODELIST GetOverLappedRect(PGFXRECT r,PFXNODELIST objList);
PGFXRECT Intersection( PGFXRECT r, PGFXRECT rhs );
//
//
//
BOOL DragStart(PFXUIENV pguiEnv, int xPos, int  yPos);
BOOL DragEnd(PFXUIENV pguiEnv, int xPos, int yPos);
BOOL IsDragging(PFXUIENV pguiEnv);
BOOL IsDblClick(PFXUIENV pguiEnv);
//
//
//
BOOL MoveRect(PGFXRECT r, int xPos, int yPos);

HFXFONT LoadFont(const char* fontName);
const char* GetFontName(HFXFONT hFont);
void  UnloadFont(HFXFONT hFont);
void fxRenderText(HDC hdc,const char* message, int dx, int dy,HFXFONT hFont, COLORREF color);


void FXTextOut(HDC hdc, const char* message, int dx, int dy,const unsigned char* font, COLORREF color);
void FXTextOutEx(HDC hdc, const char* message, int dx, int dy,const unsigned char* font, int scale, COLORREF color, COLORREF bkcolor);

int gettimeofday(struct timeval * tp, struct timezone * tzp);

#endif