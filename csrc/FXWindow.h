#ifndef _FX_WINDOW
#define _FX_WINDOW

#include <windows.h>
#include <stdint.h>

#include "FXDevices.h"
#include "GFXRECT.h"
#include "GFXRECTP.h"
#include "FXPOINT.h"
#include "FXLIST.h"

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
    void* 	        driverData;
    BOOL            isNonClient;
    PGFXRECT        focusCurrent;
    PGFXRECT  	    focusHover;
    struct timeval  leftClickTime;
    struct timeval  rightClickTime;
} FXUISTATE;
typedef FXUISTATE* PFXUISTATE;

typedef BOOL(*FXEvtProc)(void* pEnv, int eventId,int wParm, long lParm);

typedef struct _fx_environment
{
    PFXNODELIST knownRects;
    PFXNODELIST renderList;
    PFXNODELIST intersectionList;
	PFXUISTATE  state;
    PFXDEVDRV   devdrv;
    FXEvtProc   evtHandler;
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

typedef const char* HFXRES;
typedef const char* HFXFONT;

#define FXM_BORDERSIZE      2
#define FXM_TRIMWIDTH       4
#define FXM_TITLEHEIGHT     18
#define FXM_TRIMHEIGHT      16

//typedef PGFXRECT (*ApplyWindowAttr)(HDC hdc,PGFXRECT winRect);
typedef PGFXRECT (*ApplyWindowAttr)(HDC hdc,PGFXRECT winRect, PGFXRECT gadget);

typedef BOOL (*FXWndProc)(HDC hdc,int msgId, int wParam, int lParam,PGFXRECT winRect);

RECT* ToWinRECT(RECT* rect, GFXRECT* grect);
PGFXRECT FromWinRECT(RECT* rect);
//
//  Standard Gadget Functions
//
PGFXRECT AddCloseGadget(HDC hdc,PGFXRECT winRect,PGFXRECT);
PGFXRECT AddTitleBarGadget(HDC hdc,PGFXRECT winRect,PGFXRECT);
PGFXRECT AddTitleGadget(HDC hdc,PGFXRECT winRect,PGFXRECT);
PGFXRECT AddSizerGadget(HDC hdc,PGFXRECT winRect,PGFXRECT);
//
//
typedef struct _fx_window
{
    PGFXRECT    winRect;
    PFXNODELIST chromeList;
} FXWINDOW;

PFXUIENV InitUIEnvironment(int drvDataSize);
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

#define FX_RES_SIG "FXRZ"
VOID fxInvalidateWindow(PGFXRECT r, int bBackground);
void fxSetWindowTitle(PGFXRECT fxRect, const char* title);

HFXFONT LoadFont(const char* fontName);
HFXRES  LoadResIndirect(const char* type, int width, int height, const char* resName, const char* data, int size);
const char* GetFontName(HFXFONT hFont);
void  UnloadFont(HFXFONT hFont);
void fxRenderText(HDC hdc,const char* message, int dx, int dy,HFXFONT hFont, COLORREF color);
void fxRenderChars(HDC hdc,const char* message,int length ,int dx, int dy,HFXFONT hFont, COLORREF color);

void MoveFXWindow(HWND hWnd,PFXUIENV pEnv, PGFXRECT p, int xPos, int yPos);

void FXTextOut(HDC hdc, const char* message, int dx, int dy,const unsigned char* font, COLORREF color);
void FXTextOutEx(HDC hdc, const char* message, int dx, int dy,const unsigned char* font, int scale, COLORREF color, COLORREF bkcolor);

int gettimeofday(struct timeval * tp, struct timezone * tzp);

PGFXRECT AddRect(const char* name, int xPos, int yPos, int width, int height, void* wndProc);
PGFXRECT AddRectV2(const char* name, int xPos, int yPos, int width, int height, void* wndProc);



void DebugNode(PFXNODE p);
void __Unhighlight(PFXNODE p);
void Unhighlight(PFXNODELIST renderList);


int PointInList(PFXNODELIST pList,int x, int y);
int PointInListEx(PFXNODELIST pList, int x, int y, PGFXRECT* pFound);

void RedrawScreen(HWND hWnd, BOOL bBackground);
void RedrawRect(HWND hWnd,PFXNODE p);
void RedrawInvalid(HWND hWnd, PFXNODE p);
void RedrawVisible(PFXNODE p);

int HasInvalidAttr(PFXNODE p, void* ctx);
int IsInvalidRects();

VOID DrawRectangles(HDC hdc, PFXNODELIST renderList);
VOID DrawRectanglesV2(HDC hdc, PFXNODELIST renderList);
BOOL OnClick(int xPos, int yPos);
BOOL OnCtlClick(int xPos, int yPos);
BOOL OnMove(int xPos, int yPos);






#endif