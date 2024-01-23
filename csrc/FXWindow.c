
#include "FXWindow.h"
#include "FXDevices.h"
#include <windowsx.h>
#include "pgm.h"
#include "WindowsHAL.h"

HBRUSH CONST_WHITE = NULL;
HBRUSH CONST_BLACK = NULL;
HBRUSH CONST_DESK  = NULL;

RECT dragRect;

char __fx_debugOut[256];

PFXUIENV __fx_penv = NULL;

ApplyWindowAttr fApplyChrome[] = {AddCloseGadget,AddTitleBarGadget,AddTitleGadget,AddSizerGadget,NULL};

PFXUIENV InitUIEnvironment(int drvDataSize)
{
	CONST_WHITE = CreateSolidBrush(RGB(255, 255, 255));
	CONST_BLACK = CreateSolidBrush(RGB(0, 0, 0));
	CONST_DESK  = CreateSolidBrush(RGB(64, 64, 64));


    PFXUIENV env = (PFXUIENV)malloc(sizeof(FXUIENV));
	if(env)
	{
		memset(env,0,sizeof(FXUIENV));
		env->state = (PFXUISTATE)malloc(sizeof(FXUISTATE));
		if (env->state)
		{
			memset(env->state, 0, sizeof(FXUISTATE));

			env->state->driverData = malloc(drvDataSize);

			env->knownRects = AllocNamedList("__known_rects");
			env->renderList = AllocNamedList("__render_rects");

			env->intersectionList = AllocNamedList("__intersections");

			env->state->desktop = AllocRectEx("desktop", 0, 0, 65000, 65000, 0, FX_ATTR_DESKTOP);
			env->state->desktop->color = RGB(64, 64, 64);

			ListAddStart(env->renderList, env->state->desktop);
		}
		
		//env->evtHandler = __irqEventHandler;
	}

	__fx_penv = env;

	return env;
}


RECT* ToWinRECT(RECT* rect, GFXRECT* grect)
{
	rect->top = grect->y;
	rect->left = grect->x;
	rect->right = grect->x + grect->width;
	rect->bottom = grect->y + grect->height;	
	return rect;
}

PGFXRECT FromWinRECT(RECT* rect)
{
	return AllocRect(NULL,rect->left,rect->top,rect->right - rect->left,rect->bottom - rect->top);
}


PGFXRECT AddSizerGadget(HDC hdc,PGFXRECT winRect,PGFXRECT gadget)
{
	RECT target;
	
	if(!hdc)
	{
		winRect->gadgets[FX_GADGET_SIZE] =  AllocRect(NULL, 
		                 target.right - FXM_BORDERSIZE,
		                 target.top   - FXM_BORDERSIZE,
						 FXM_BORDERSIZE,
						 FXM_BORDERSIZE );
		return winRect->gadgets[FX_GADGET_SIZE];
	}
	else
	{
		UpdateRect(winRect->gadgets[FX_GADGET_SIZE],
		           target.left,target.top,
				   target.right - target.left,target.bottom - target.top);
	}

	return NULL;
}

PGFXRECT AddCloseGadget(HDC hdc,PGFXRECT winRect,PGFXRECT gadget)
{
    //OutputDebugStringA("AddCloseGadget...\n");
    RECT target;

    target.left   = winRect->x + winRect->width - (FXM_BORDERSIZE * 2) - 10;
    target.top    = winRect->y + FXM_BORDERSIZE + (FXM_TITLEHEIGHT / 2) - 6;
    target.right  = target.left + 10;
    target.bottom = target.top  + 10;
    
	if(!hdc)
	{
		winRect->gadgets[FX_GADGET_CLOSE] = AllocRect(NULL, target.left,target.top,target.right - target.left ,target.bottom - target.top );
		return winRect->gadgets[FX_GADGET_CLOSE];
		//return AllocRect(NULL, target.left,target.top,target.right - target.left ,target.bottom - target.top );
	}
	else
	{
		UpdateRect(winRect->gadgets[FX_GADGET_CLOSE],
		           target.left,target.top,
				   target.right - target.left,target.bottom - target.top);

		/*
		// hack method
		UpdateRect((PGFXRECT)winRect->nonclientList->head->data,
		           target.left,target.top,
				   target.right - target.left,target.bottom - target.top);
		*/
	}
	/*
    sprintf(debugOut,"NON-CLIENT CLICK x: %d y: %d w: %d h: %d \n", 
    winRect->nonclientRect.x,
    winRect->nonclientRect.y,
    winRect->nonclientRect.width,
    winRect->nonclientRect.height);
    OutputDebugStringA(debugOut);
	*/
    //FrameRect(hdc, &target, CreateSolidBrush(RGB(255,255,255)));
    FrameRect(hdc, &target, CONST_WHITE);

    target.left   = target.left + 2;
    target.top    = target.top + 2;
    target.right  = target.right - 2;
    target.bottom = target.bottom - 2;
    
    //FrameRect(hdc, &target, CreateSolidBrush(RGB(255,255,255)));
    FrameRect(hdc, &target, CONST_WHITE);


    return NULL;
}

PGFXRECT AddTitleBarGadget(HDC hdc, PGFXRECT winRect,PGFXRECT gadget)
{
    //OutputDebugStringA("AddCloseGadget...\n");
    RECT target;

    for(int i = 0;i<4;i++)
    {
        target.left   = winRect->x + FXM_BORDERSIZE ;
        //target.top    = winRect->y + (FXM_BORDERSIZE * 2) + (i*4);
		target.top    = winRect->y + FXM_BORDERSIZE + (i*4);
        target.right  = winRect->x + winRect->width - (FXM_BORDERSIZE * 2) - 10 - 2;
        target.bottom = target.top + 4 ;
        
        //FrameRect(hdc, &target,CreateSolidBrush(RGB(255,255,255)));
        FrameRect(hdc, &target, CONST_WHITE);
    }

    return NULL;
}

PGFXRECT AddTitleGadget(HDC hdc, PGFXRECT winRect,PGFXRECT gadget)
{
    RECT target;
	RECT title;

	int sFont = 8;

    ToWinRECT(&target, winRect);
	
	/*
    SetTextColor(hdc,((COLORREF)RGB(255,255,255)));
    SetBkColor(hdc,((COLORREF)winRect->renderColor));

    TextOutA(hdc,
                target.left + 1 + FXM_BORDERSIZE,
                target.top + FXM_BORDERSIZE,
                winRect->name,
                winRect->szname);	
				*/
	title.left   = target.left + FXM_BORDERSIZE;
	title.top    = target.top  + FXM_BORDERSIZE;
	title.right  = title.left  + (sFont * strlen(winRect->name)) + FXM_BORDERSIZE + FXM_BORDERSIZE;
	title.bottom = title.top   + FXM_TITLEHEIGHT - FXM_BORDERSIZE;
	
	//FillRect(hdc,&title, CreateSolidBrush((COLORREF)RGB(255,255,255)));			
	FillRect(hdc,&title, CreateSolidBrush(winRect->renderColor));			
				
	FXTextOutEx(hdc,
	          winRect->name,
	          target.left + 1 + FXM_BORDERSIZE,
			  target.top  + FXM_BORDERSIZE + (FXM_TITLEHEIGHT/2) - 4,
			  (const unsigned char*)FONT_HOURGLASS_BITMAP,
			  1,             			  
			  (COLORREF)RGB(255,255,255),
			  winRect->renderColor			  
			  );	

	return NULL;			
}


PGFXRECT GetSelectedRect(PFXNODELIST objList,int mx,int my,int whichAttr)
{
	PGFXRECT highRect = NULL;
	
	if(!objList)
		return NULL;
	
	PFXNODE p = objList->head;
	while(p != NULL)
	{
		PGFXRECT r = (PGFXRECT)(p->data);
		if((r && r->attr & whichAttr) || (whichAttr == -1))
		{
			if(r->x < mx && (r->x + r->width) > mx)
			{
				if(r->y < my && (r->y + r->height) > my)
				{
					if(highRect == NULL)
					{
						highRect = r;
					}
					else						
					{
						if(highRect->z < r->z)
							highRect = r;
					}
				}
			}	
		}
		p = p->next;
	}
	return highRect;
}

BOOL PointInRect(PGFXRECT r,int mx,int my)
{
    BOOL bRet = FALSE;

    if(r)
    {
        if(r->x < mx && (r->x + r->width) > mx)
        {
            if(r->y < my && (r->y + r->height) > my)
            {
                bRet = TRUE;
            }
        }	
    }

	return bRet;
}

PFXPOINT RectToPoint(PGFXRECT r,int whichPoint)
{
	switch(whichPoint)
	{
	case 1:
		return AllocPoint(r->x,r->y);
	case 2:
		return AllocPoint(r->x + r->width,r->y);
	case 3:
		return AllocPoint(r->x + r->width,r->y + r->height);
	case 4:
		return AllocPoint(r->x,r->y + r->height);
	}
	return NULL;
}

BOOL IsOverlappedPoints(PFXPOINT l1, PFXPOINT r1, PFXPOINT l2, PFXPOINT r2) 
{ 
	if(l1 &&  r1 && l2 && r2)
	{
		if (l1->x >= r2->x || l2->x >= r1->x) 
		{ 
			return FALSE; 
		} 

		// If one rectangle is above other  
		if (l1->y >= r2->y || l2->y >= r1->y) 
		{ 
			return FALSE; 
		} 
		
		return TRUE; 
	}
	return FALSE;
} 

BOOL IsOverlappedRects(PGFXRECT r1,PGFXRECT r2) 
{
	return IsOverlappedPoints(RectToPoint(r1,1), RectToPoint(r1,3), RectToPoint(r2,1), RectToPoint(r2,3)) ;
}


PFXNODELIST GetOverLappedRect(PGFXRECT r,PFXNODELIST objList)
{
	PFXNODELIST rects = AllocList();

	PFXNODE p = objList->head;
	while(p != NULL)
	{
		PGFXRECT r2 = (PGFXRECT)(p->data);
		if(r!=r2 && IsOverlappedRects(r,r2))
		{
			ListAddStart(rects,r2);
		}
		
		p = p->next;
	}
	return rects;
}

PGFXRECT Intersection( PGFXRECT r, PGFXRECT rhs )
{
	if(r == NULL || rhs == NULL)
		return NULL;
	
	PGFXRECTP rectTemp = AllocRectP(0,0,0,0);

	PGFXRECTP rp   = ToRECTP(r);
	PGFXRECTP rhsp = ToRECTP(rhs);

	rectTemp->topLeft->x       = RECTMAX( rhsp->topLeft->x, rp->topLeft->x );
	rectTemp->bottomRight->x   = RECTMIN( rhsp->bottomRight->x, rp->bottomRight->x );
	rectTemp->topLeft->y       = RECTMAX( rhsp->topLeft->y, rp->topLeft->y );
	rectTemp->bottomRight->y   = RECTMIN( rhsp->bottomRight->y, rp->bottomRight->y );


	if ( rectTemp->topLeft->x > rectTemp->bottomRight->x )
	{
		return NULL;
	}
	if ( rectTemp->topLeft->y > rectTemp->bottomRight->y )
	{
	return NULL;
	}

	return ToRECT(rectTemp, NULL);
}

BOOL DragStart(PFXUIENV pguiEnv, int xPos, int yPos)
{
    if(pguiEnv)
    {
        pguiEnv->state->dragOn = TRUE;
        pguiEnv->state->dragStart.x = xPos;
        pguiEnv->state->dragStart.y = yPos;
		
        pguiEnv->state->dragOffset.x = xPos - pguiEnv->state->focusCurrent->x;
        pguiEnv->state->dragOffset.y = yPos - pguiEnv->state->focusCurrent->y;
		
        return TRUE;
    }

    return FALSE;
}

BOOL DragEnd(PFXUIENV pguiEnv, int xPos, int yPos)
{
    if(pguiEnv)
    {
        pguiEnv->state->dragOn = FALSE;
        pguiEnv->state->dragEnd.x = xPos;
        pguiEnv->state->dragEnd.y = yPos;
        return TRUE;
    }
    return FALSE;
}

BOOL IsDragging(PFXUIENV pguiEnv)
{
    if(pguiEnv)
    {
       return pguiEnv->state->dragOn;
    }
    return FALSE;
}

BOOL IsDblClick(PFXUIENV pguiEnv)
{
	BOOL bRet = FALSE;

	struct timeval now;

	gettimeofday(&now, NULL);

	unsigned long duration = (now.tv_sec - pguiEnv->state->leftClickTime.tv_sec) * 1000000 + now.tv_usec - pguiEnv->state->leftClickTime.tv_usec;

	memcpy(&pguiEnv->state->leftClickTime,&now,sizeof(struct timeval));

	if(duration < 180000L)
	{
		bRet = TRUE;
	}	

	return bRet;
}

BOOL MoveRect(PGFXRECT r, int xPos, int yPos )
{
    r->y = yPos;
    r->x = xPos;
    if(r->clientRect)
    {
        r->clientRect->x = xPos + FXM_BORDERSIZE;
		r->clientRect->y = yPos + (FXM_BORDERSIZE + FXM_TITLEHEIGHT); 
		r->clientRect->attr|=FX_ATTR_MOVED;
    }
    r->attr|=FX_ATTR_INVALID;
	r->attr|=FX_ATTR_MOVED;

	fxInvalidateWindow(r,1);
    //r->attr|=FX_ATTR_ERASE;

    return TRUE;
}

HFXFONT LoadFont(const char* fontName)
{
	char debugOut[128];
	PHFXRESH hFontHeader = NULL;

	//OutputDebugStringA("LoadFont enter...\n");

	FILE* ff = fopen(fontName,"rb");
	if(ff)
	{
		char *hFont = (char*)malloc(768 + sizeof(HFXRESH));
		int size = fread(hFont,768 + sizeof(HFXRESH),1,ff);
		fclose(ff);
		OutputDebugStringA("LoadFont loaded...\n");
		hFontHeader = (PHFXRESH)hFont;
	}
	else
	{
		hFontHeader = (PHFXRESH)LoadResIndirect((const char*)FX_RES_SIG, 8, 8, (const char*)"System\0", (const char*)FONT_HOURGLASS_BITMAP, 768);
	}
	/*
	sprintf(debugOut,"LoadFont name:%.32s sig:%.4s rtype:%.4s w:%d h:%d \n", 
    hFontHeader->fontName,
	hFontHeader->sig,
    hFontHeader->type,
    hFontHeader->width,
    hFontHeader->height);
    OutputDebugStringA(debugOut);
	*/
	//OutputDebugStringA("LoadFont Exit...\n");
	
	return (HFXFONT)(hFontHeader);
}

HFXRES  LoadResIndirect(const char* type, int width, int height, const char* resName, const char* data, int size)
{
	char debugOut[128];
	char* hFont = (char*)malloc(768 + 42);

	PHFXRESH hFontHeader = (PHFXRESH)(hFont);

	if(hFont)
	{
		OutputDebugStringA("LoadResIndirect...");
		strcpy(hFontHeader->sig, FX_RES_SIG);
		strcpy(hFontHeader->type, "FONT");
		hFontHeader->width = width;
		hFontHeader->height = height;
		strcpy(hFontHeader->fontName, resName);
		memcpy(&hFontHeader->data, data, size);
	}

	sprintf(debugOut, "LoadFont name:%.32s sig:%.4s type:%.4s w:%d h:%d \n",
		hFontHeader->fontName,
		hFontHeader->sig,
		hFontHeader->type,
		hFontHeader->width,
		hFontHeader->height);
	OutputDebugStringA(debugOut);


	return (HFXFONT)(hFontHeader);
}

const char* GetFontName(HFXFONT hFont)
{
	return ((PHFXRESH)hFont)->fontName;
}

void UnloadFont(HFXFONT hFont)
{
	if(hFont)
		free((char*)hFont);
}

void fxRenderChars(HDC hdc,const char* message,int length ,int dx, int dy,HFXFONT hFont, COLORREF color, COLORREF background)
{
    int c = 0;
	
	PHFXRESH header = (PHFXRESH)hFont;
	
	/*
	sprintf(__fx_debugOut,"fxRenderText %p name:%.32s  w:%d h:%d text: %p\n",
	(void*)hFont,
    header->fontName,
    header->width,
    header->height,
	message);
    OutputDebugStringA(__fx_debugOut);
	*/
	
	
	const unsigned char* font = (const unsigned char*)&header->data;
	
    while(*message && length--)
    {
        //const unsigned char* fchar = &font[(*message - 32)*header->width];
		const unsigned char* fchar = &font[(*message - 32)*header->width];
		
		if(*message == 0x0D)
		{
			OutputDebugStringA("Encoded RETURN DETECTED!");
			dy+=(header->height + 1);
			c = 0;
		}
		else
		{
			for(int y=0;y<header->height;y++)
			{
				for(int x=0;x<header->width;x++)
				{
					if(((fchar[y]) >> x) & 1)
						SetPixelV(hdc,dx + c + (header->width - x),dy + y,color);
					//else
				//		SetPixelV(hdc, dx + c + (header->width - x), dy + y, background);
				}
			}
			c+=header->width;
		}        
        message++;
    }
}

void fxRenderText(HDC hdc,const char* message, int dx, int dy,HFXFONT hFont, COLORREF color)
{
    int c = 0;
	
	PHFXRESH header = (PHFXRESH)hFont;
	
	/*
	sprintf(__fx_debugOut,"fxRenderText %p name:%.32s  w:%d h:%d text: %p\n",
	(void*)hFont,
    header->fontName,
    header->width,
    header->height,
	message);
    OutputDebugStringA(__fx_debugOut);
	*/
	
	
	const unsigned char* font = (const unsigned char*)&header->data;
	
    while(*message)
    {
        //const unsigned char* fchar = &font[(*message - 32)*header->width];
		const unsigned char* fchar = &font[(*message - 32)*header->width];
		
		if(*message == 0x0D)
		{
			OutputDebugStringA("Encoded RETURN DETECTED!");
			dy+=(header->height + 1);
			c = 0;
		}
		else
		{
			for(int y=0;y<header->height;y++)
			{
				for(int x=0;x<header->width;x++)
				{
					if(((fchar[y]) >> x) & 1)
						SetPixelV(hdc,dx + c + (header->width - x),dy + y,color);
				}
			}
			c+=header->width;
		}        
        message++;
    }
}

void FXTextOut(HDC hdc,const char* message, int dx, int dy,const unsigned char* font, COLORREF color)
{
    int c = 0;
    while(*message)
    {
        const unsigned char* fchar = &font[(*message - 32)*8];

        for(int y=0;y<8;y++)
        {
            for(int x=0;x<8;x++)
            {
                if(((fchar[y]) >> x) & 1)
                    SetPixelV(hdc,dx + c + (8 - x),dy + y,color);
            }
        }
        c+=9;
        message++;
    }
}

void FXTextOutEx(HDC hdc,const char* message, int px, int py,
                 const unsigned char* font, int scale, 
				 COLORREF color,
				 COLORREF bkcolor)
{
	int fsize = 8;
    int c     = 0;
	
	//int dx = 0;
	int dy = 0;

	HPEN hb  = CreatePen(PS_SOLID, 1,color);
	HPEN hbb = CreatePen(PS_SOLID, 1,bkcolor);
	HGDIOBJ hbo = SelectObject(hdc,(HGDIOBJ)hb);

	
    while(*message)
    {
		dy = 0;
        const unsigned char* fchar = &font[(*message - 32)*fsize];


        for(int y=0;y<fsize;y++)
        {
			int row = fchar[y];			
			for(int sy=0;sy<scale;sy++)
			{
				for(int x=0;x<fsize;x++)
				{
					if(((row) >> x) & 1)
					{
						SelectObject(hdc,(HGDIOBJ)hb);
						MoveToEx(hdc, px + c + ((fsize * scale) - (x * scale)),py + dy, (LPPOINT) NULL); 
						LineTo(hdc, px + c + ((fsize * scale) - (x * scale - scale)),py + dy); 
					}
					else
					{
						SelectObject(hdc,(HGDIOBJ)hbb);
						MoveToEx(hdc, px + c + ((fsize * scale) - (x * scale)),py + dy, (LPPOINT) NULL); 
						LineTo(hdc, px + c + ((fsize * scale) - (x * scale - scale)),py + dy);					
					}
				}
				dy++;
			}			
        }
        c+=(fsize * scale);
        message++;
    }
	
	SelectObject(hdc,hbo);
	DeleteObject(hb);
}

/*


*/
int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970 
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}


void DebugNode(struct node* p)
{
	GFXRECT* g = (GFXRECT*)p->data;

	sprintf(__fx_debugOut, "%s[%d]: %d %d %d %d %x\n", g->name, g->z, g->x, g->y, g->width, g->height, g->attr);
	OutputDebugStringA(__fx_debugOut);
}

void __Unhighlight(PFXNODE p)
{
	GFXRECT* g = (GFXRECT*)p->data;
	OutputDebugStringA("__Unhighlight\n");
	g->renderColor = g->color;
}

void Unhighlight(PFXNODELIST renderList)
{
	VisitList(renderList, __Unhighlight);
}

void MoveFXWindow(HWND hWnd,PFXUIENV pEnv, PGFXRECT p, int xPos, int yPos)
{
	HDC hdc = GetDC(hWnd);
	if (hdc)
	{
		RECT target;

		DrawFocusRect(hdc, &dragRect);

		PFXNODE t = ListRemove(pEnv->renderList, p);
		//sprintf(debugOut,"ListRemove %p\n",t);	
		//OutputDebugStringA(debugOut);

		PGFXRECT g = (PGFXRECT)(t->data);
		//sprintf(debugOut,"RECT %s\n",g->name);	
		//OutputDebugStringA(debugOut);

		PFXNODELIST overlaps = GetOverLappedRect(g, pEnv->renderList);
		if (overlaps != NULL)
		{
			//OutputDebugStringA("MoveFXWindow::OVERLAPS:\n");
			PFXNODE node = overlaps->head;
			while (node != NULL)
			{
				PGFXRECT ol = (PGFXRECT)(node->data);
				if (ol && ((ol->attr & FX_ATTR_DESKTOP) != FX_ATTR_DESKTOP))
				{
					ol->attr |= FX_ATTR_INVALID;
					fxInvalidateWindow(ol, 1);
				}
				node = node->next;
			}
			DeallocList(overlaps);
		}

		FillRect(hdc, ToWinRECT(&target, g), CreateSolidBrush((COLORREF)RGB(64, 64, 64)));
		MoveRect(g, xPos, yPos);

		fxInvalidateWindow(pEnv->state->focusCurrent,1);

		pEnv->state->focusCurrent = NULL;

		ListAddEnd(pEnv->renderList, g);

		RedrawScreen(hWnd, FALSE);
	}
}

void RedrawRect(HWND hWnd,PFXNODE p)
{
	RECT target;

	PGFXRECT r = (PGFXRECT)p->data;
	if (r->attr & FX_ATTR_VISIBLE)
	{
		HDC hdc = GetDC(hWnd);

		FillRect(hdc, ToWinRECT(&target, r), CreateSolidBrush((COLORREF)RGB(0, 0, 0)));
		ReleaseDC(hWnd, hdc);
	}
}

void RedrawInvalid(HWND hWnd, PFXNODE p)
{
	RECT target;

	PGFXRECT r = (PGFXRECT)p->data;
	if (r->attr & FX_ATTR_VISIBLE && (r->attr & FX_ATTR_INVALID))
	{
		HDC hdc = GetDC(hWnd);

		FillRect(hdc, ToWinRECT(&target, r), CreateSolidBrush((COLORREF)RGB(64, 64, 64)));
		ReleaseDC(hWnd, hdc);

		r->attr &= (~FX_ATTR_INVALID);
	}
}

void RedrawVisible(PFXNODE p)
{
	PGFXRECT r = (PGFXRECT)p->data;

	/*
	if (r->attr & FX_ATTR_VISIBLE)
	{
		r->attr |= (FX_ATTR_INVALID);
		r->attr |= (FX_ATTR_BACKGROUND);
	}
	*/
	fxInvalidateWindow(r,1);
}


int HasInvalidAttr(PFXNODE p, void* ctx)
{
	PGFXRECT r = (PGFXRECT)p->data;
	
	if(r->clientRect && ((r->clientRect->attr & FX_ATTR_INVALID) > 0))
		return TRUE;

	return ((r->attr & FX_ATTR_INVALID) > 0);
}


int IsInvalidRects()
{
	return VisitListCtx(__fx_penv->renderList,HasInvalidAttr, NULL);
}

int __PointInList(PFXNODE p, void* ctx)
{
	return PointInRect((PGFXRECT)p->data,((PFXPOINT)ctx)->x,((PFXPOINT)ctx)->y);
}

int __PointInListEx(PFXNODE p, void* ctx)
{
	BOOL bRet = PointInRect((PGFXRECT)p->data,((PGRECTHIT)ctx)->dx,((PGRECTHIT)ctx)->dy);

	if(bRet)
		((PGRECTHIT)ctx)->pRect = (PGFXRECT)p->data;

	return bRet;
}


int PointInList(PFXNODELIST pList,int x, int y)
{
	FXPOINT point;
	point.x = x ;
	point.y = y;
	return VisitListCtx(pList,__PointInList, &point);
}

int PointInListEx(PFXNODELIST pList, int x, int y, PGFXRECT* pFound)
{
	GRECTHIT hit;
	hit.dx = x ;
	hit.dy = y;
	
	BOOL bRet = VisitListCtx(pList,__PointInListEx, &hit);
	if(bRet && pFound)
		*pFound = hit.pRect;
	
	return bRet;
}


void fxSetWindowTitle(PGFXRECT fxRect, const char* title)
{
	if(title && fxRect)
		fxRect->name = title;
}

PGFXRECT AddRect(const char* name, int xPos, int yPos, int width, int height,void* wndProc)
{
	OutputDebugStringA("AddRect...\n");

	PGFXRECT r = AllocRectEx(name, xPos, yPos, width, height, -1, FX_ATTR_VISIBLE);
	r->szname = strlen(r->name);
	r->color = RGB(125, 125, 125);
	r->renderColor = RGB(52, 146, 235);
	r->attr |= FX_ATTR_INVALID;
	r->attr |= FX_ATTR_MOVED;

	r->clientRect = AllocRectEx(name,
		xPos + FXM_BORDERSIZE,
		yPos + (FXM_BORDERSIZE + FXM_TITLEHEIGHT),
		width - (FXM_BORDERSIZE * 2),
		height - (FXM_BORDERSIZE + FXM_TITLEHEIGHT + FXM_BORDERSIZE),
		-1,
		FX_ATTR_VISIBLE);

	r->parent = NULL;
	r->clientRect->parent = r;
	r->wndProc = (void*)(wndProc);
	r->wndData = NULL;
	r->wndInit = 0;

	if(r->wndProc)
		((FXWndProc)r->wndProc)(NULL,1,0,0,r);


	//VisitList(renderList,Unhighlight);
	Unhighlight(__fx_penv->renderList);

	ListAddStart(__fx_penv->knownRects, r);
	ListAddEnd(__fx_penv->renderList, r);

	//VisitList(renderList,DebugNode);
	if (__fx_penv->state->focusCurrent)
		__fx_penv->state->focusCurrent->attr |= FX_ATTR_INVALID;

	__fx_penv->state->focusCurrent = r;

	return r;
}

PGFXRECT AddRectV2(const char* name, int xPos, int yPos, int width, int height,void* wndProc)
{
	OutputDebugStringA("AddRect...\n");

	PGFXRECT r = AllocRectEx(name, xPos, yPos, width, height, -1, FX_ATTR_VISIBLE);
	r->szname = strlen(r->name);
	r->color = RGB(125, 125, 125);
	r->renderColor = RGB(52, 146, 235);
	r->attr |= FX_ATTR_INVALID;
	r->attr |= FX_ATTR_MOVED;

	r->clientRect = AllocRectEx(name,
		xPos + FXM_BORDERSIZE,
		yPos + (FXM_BORDERSIZE + FXM_TITLEHEIGHT),
		width - (FXM_BORDERSIZE * 2),
		height - (FXM_BORDERSIZE + FXM_TITLEHEIGHT + FXM_BORDERSIZE),
		-1,
		FX_ATTR_VISIBLE);

	r->parent = NULL;
	r->clientRect->parent = r;
	r->wndProc = (void*)(wndProc);
	r->wndData = NULL;
	r->wndInit = 0;

	if(r->wndProc)
		((FXWndProc)r->wndProc)(NULL,1,0,0,r);


	//VisitList(renderList,Unhighlight);
	Unhighlight(__fx_penv->renderList);

	ListAddStart(__fx_penv->knownRects, r);
	ListAddEnd(__fx_penv->renderList, r);

	//VisitList(renderList,DebugNode);
	if (__fx_penv->state->focusCurrent)
	{
		//__fx_penv->state->focusCurrent->attr |= FX_ATTR_INVALID;
		fxInvalidateWindow(__fx_penv->state->focusCurrent, 1);
	}
	__fx_penv->state->focusCurrent = r;

	return r;
}

VOID DrawRectangles(HDC hdc, PFXNODELIST renderList)
{
	RECT target;

	PFXNODE p = renderList->head;
	while (p != NULL)
	{
		PGFXRECT r = (PGFXRECT)p->data;
		if (!r)
			break;

		if ((r->attr & FX_ATTR_VISIBLE) && (r->attr & FX_ATTR_INVALID))
		{
			FillRect(hdc, ToWinRECT(&target, r), CreateSolidBrush((COLORREF)r->renderColor));

			int i = 0;

			if (!r->nonclientList)
			{
				r->nonclientList = AllocList();
				while (fApplyChrome[i])
				{
					PGFXRECT rc = fApplyChrome[i++](NULL, r, NULL);
					if (rc)
					{
						ListAddStart(r->nonclientList, rc);
					}
				}
			}

			i = 0;
			while (fApplyChrome[i])
			{
				PGFXRECT rc = fApplyChrome[i++](hdc, r, NULL);
			}

			if (r->clientRect)
			{
				//FillRect(hdc, ToWinRECT(&target, r->clientRect), CreateSolidBrush((COLORREF)RGB(255, 255, 255)));
				((FXWndProc)r->wndProc)(hdc, 0,0,0,r->clientRect);
			}

			r->attr &= (~FX_ATTR_INVALID);
		}
		else if (r->attr & FX_ATTR_ERASE)
		{
			FillRect(hdc, ToWinRECT(&target, r), CreateSolidBrush((COLORREF)r->renderColor));
			r->attr &= (~FX_ATTR_ERASE);
		}
		p = p->next;
	}
}


VOID fxInvalidateWindow(PGFXRECT r, int bBackground)
{
	r->attr |= (FX_ATTR_INVALID);
	if(r->clientRect)
		r->clientRect->attr |= (FX_ATTR_INVALID);
	
	if(bBackground)
	{
		r->attr |= (FX_ATTR_BACKGROUND);
		if(r->clientRect)
			r->clientRect->attr |= (FX_ATTR_BACKGROUND);
	}
}

VOID DrawRectanglesV2(HDC hdc, PFXNODELIST compatible)
{
	RECT target;

	PFXUIENV pguiEnv = __fx_penv;

	PFXNODELIST renderList = pguiEnv->renderList; 

	PGFXRECT currentFocus = pguiEnv->state->focusCurrent;

	PFXNODE p = renderList->head;
	while (p != NULL)
	{
		PGFXRECT r = (PGFXRECT)p->data;
		if (!r)
			break;
		
		if ((r->attr & FX_ATTR_VISIBLE) && (r->attr & FX_ATTR_INVALID) && ((r->attr & FX_ATTR_BACKGROUND) == 0) &&  (r == currentFocus) && r->wndInit)
		{
			OutputDebugStringA("CURRENT FOCUS UPDATE");
			if (r->clientRect)
			{
				//FillRect(hdc, ToWinRECT(&target, r->clientRect), CreateSolidBrush((COLORREF)RGB(255, 255, 255)));
				((FXWndProc)r->wndProc)(hdc, 0,0,0,r->clientRect);
				r->clientRect->attr &= (~FX_ATTR_INVALID);
			}

			r->attr &= (~FX_ATTR_INVALID);		
		}
		else
		{
			if ((r->attr & FX_ATTR_VISIBLE) && (r->attr & FX_ATTR_INVALID))
			{
				FillRect(hdc, ToWinRECT(&target, r), CreateSolidBrush((COLORREF)r->renderColor));

				int i = 0;

				if (!r->nonclientList)
				{
					r->nonclientList = AllocList();
					while (fApplyChrome[i])
					{
						PGFXRECT rc = fApplyChrome[i++](NULL, r, NULL);
						if (rc)
						{
							ListAddStart(r->nonclientList, rc);
						}
					}
				}

				i = 0;
				while (fApplyChrome[i])
				{
					PGFXRECT rc = fApplyChrome[i++](hdc, r, NULL);
				}

				if (r->clientRect)
				{
					//FillRect(hdc, ToWinRECT(&target, r->clientRect), CreateSolidBrush((COLORREF)RGB(255, 255, 255)));
					((FXWndProc)r->wndProc)(hdc, 0,0,0,r->clientRect);
					r->clientRect->attr &= (~FX_ATTR_BACKGROUND);
				}

				r->wndInit = 1;
				//r->attr |= (FX_ATTR_CREATED);
				r->attr &= (~FX_ATTR_BACKGROUND);
				r->attr &= (~FX_ATTR_INVALID);
			}
			else if (r->attr & FX_ATTR_ERASE)
			{
				FillRect(hdc, ToWinRECT(&target, r), CreateSolidBrush((COLORREF)r->renderColor));
				r->attr &= (~FX_ATTR_ERASE);
			}
		}
		
		

		p = p->next;
	}
}


VOID DrawRectanglesV3(PFXDEVDRV drv, PFXNODELIST compatible)
{
	RECT target;

	PFXUIENV pguiEnv = __fx_penv;

	PFXNODELIST renderList = pguiEnv->renderList; 

	PGFXRECT currentFocus = pguiEnv->state->focusCurrent;

	PFXNODE p = renderList->head;
	
	// fix me
	HDC hdc = NULL;
	
	
	while (p != NULL)
	{
		PGFXRECT r = (PGFXRECT)p->data;
		if (!r)
			break;
		
		if ((r->attr & FX_ATTR_VISIBLE) && (r->attr & FX_ATTR_INVALID) && ((r->attr & FX_ATTR_BACKGROUND) == 0) &&  (r == currentFocus) && r->wndInit)
		{
			OutputDebugStringA("CURRENT FOCUS UPDATE");
			if (r->clientRect)
			{
				//FillRect(hdc, ToWinRECT(&target, r->clientRect), CreateSolidBrush((COLORREF)RGB(255, 255, 255)));
				((FXWndProc)r->wndProc)(hdc, 0,0,0,r->clientRect);
				r->clientRect->attr &= (~FX_ATTR_INVALID);
			}

			r->attr &= (~FX_ATTR_INVALID);		
		}
		else
		{
			if ((r->attr & FX_ATTR_VISIBLE) && (r->attr & FX_ATTR_INVALID))
			{
				//FillRect(hdc, ToWinRECT(&target, r), CreateSolidBrush((COLORREF)r->renderColor));
				((PFXGFXFUNCTABLE)drv->pDriverFunctionTable)->DrawFillRect(drv, r, r->renderColor);
				

				int i = 0;

				if (!r->nonclientList)
				{
					r->nonclientList = AllocList();
					while (fApplyChrome[i])
					{
						PGFXRECT rc = fApplyChrome[i++](NULL, r, NULL);
						if (rc)
						{
							ListAddStart(r->nonclientList, rc);
						}
					}
				}

				i = 0;
				while (fApplyChrome[i])
				{
					PGFXRECT rc = fApplyChrome[i++](hdc, r, NULL);
				}

				if (r->clientRect)
				{
					//FillRect(hdc, ToWinRECT(&target, r->clientRect), CreateSolidBrush((COLORREF)RGB(255, 255, 255)));
					((FXWndProc)r->wndProc)(hdc, 0,0,0,r->clientRect);
					r->clientRect->attr &= (~FX_ATTR_BACKGROUND);
				}

				r->wndInit = 1;
				//r->attr |= (FX_ATTR_CREATED);
				r->attr &= (~FX_ATTR_BACKGROUND);
				r->attr &= (~FX_ATTR_INVALID);
			}
			else if (r->attr & FX_ATTR_ERASE)
			{
				FillRect(hdc, ToWinRECT(&target, r), CreateSolidBrush((COLORREF)r->renderColor));
				r->attr &= (~FX_ATTR_ERASE);
			}
		}
		
		

		p = p->next;
	}
}



void RedrawScreen(HWND hWnd,BOOL bBackground)
{
	HDC hdc = NULL;
	
	if(__fx_penv)
	{
		if(hWnd)
		{
			hdc = GetDC(hWnd);
		}
		else
		{
			if(__fx_penv->devdrv && __fx_penv->devdrv->pDriverData)
				hdc = (HDC)__fx_penv->devdrv->pDriverData;
		}

		if(hdc)
		{
			DrawRectanglesV2(hdc, __fx_penv->renderList);
			ReleaseDC(hWnd, hdc);
		}
	}
}

void RedrawScreenV3(PFXDEVDRV drv,BOOL bBackground)
{
	HDC hdc = NULL;
	
	if(__fx_penv)
	{
		if(drv)
		{
			hdc = GetDC((HWND)drv->pDriverData);
		}
		else
		{
			if(__fx_penv->devdrv && __fx_penv->devdrv->pDriverData)
				hdc = (HDC)__fx_penv->devdrv->pDriverData;
		}

		if(hdc)
		{
			DrawRectanglesV2(hdc, __fx_penv->renderList);
			ReleaseDC((HWND)drv->pDriverData, hdc);
		}
	}
}

BOOL OnClick(int xPos, int yPos)
{
	BOOL bRet = FALSE;

	PFXUIENV pguiEnv = __fx_penv;

	BOOL bIsDblClick = IsDblClick(pguiEnv);
	if (bIsDblClick)
	{
		OutputDebugStringA("Double Click!!");
	}

	PGFXRECT highhit = GetSelectedRect(pguiEnv->renderList, xPos, yPos, FX_ATTR_VISIBLE);

	pguiEnv->state->isNonClient = FALSE;
	if (highhit && !PointInRect(highhit->clientRect, xPos, yPos))
	{
		pguiEnv->state->isNonClient = TRUE;
		OutputDebugStringA("NON-CLIENT SET...\n");
	}

	if (highhit != NULL && pguiEnv->state->focusCurrent != highhit)
	{
		OutputDebugStringA("OnClick::GetSelectedRect...\n");

		if (pguiEnv->state->focusCurrent != NULL && pguiEnv->state->focusCurrent != highhit)
		{
			pguiEnv->state->focusCurrent->renderColor = pguiEnv->state->focusCurrent->color;
			//pguiEnv->state->focusCurrent->attr |= FX_ATTR_INVALID;			
			//pguiEnv->state->focusCurrent->attr |= FX_ATTR_BACKGROUND;
			
			fxInvalidateWindow(pguiEnv->state->focusCurrent, 1);
			
			OutputDebugStringA("FX_LOST_FOCUS:");
			OutputDebugStringA(pguiEnv->state->focusCurrent->name);
		}

		highhit->renderColor = RGB(52, 146, 235);
		highhit->z = NextDepth();
		highhit->attr |= FX_ATTR_INVALID;
		highhit->attr |= FX_ATTR_BACKGROUND;


		PFXNODE t = ListRemove(pguiEnv->renderList, highhit);
		ListAddEnd(pguiEnv->renderList, highhit);
		DeallocNode(t);

		pguiEnv->state->focusCurrent = highhit;
		fxInvalidateWindow(pguiEnv->state->focusCurrent, 1);

		sprintf(__fx_debugOut, "FX_GOT_FOCUS: %s \n", pguiEnv->state->focusCurrent->name);
		OutputDebugStringA(__fx_debugOut);

		ListClear(pguiEnv->intersectionList);


		//sprintf(debugOut,"Overlaps currentFocus: %s\n", pguiEnv->state->focusCurrent->name);
		//OutputDebugStringA(debugOut);	
		PFXNODELIST overlaps = GetOverLappedRect(pguiEnv->state->focusCurrent, pguiEnv->renderList);
		if (overlaps != NULL)
		{
			//OutputDebugStringA("OVERLAPS:\n");
			PFXNODE node = overlaps->head;
			while (node != NULL)
			{
				PGFXRECT ol = (PGFXRECT)(node->data);
				if (ol && ((ol->attr & FX_ATTR_DESKTOP) != FX_ATTR_DESKTOP))
				{
					//ol->attr|=FX_ATTR_INVALID;

					//sprintf(debugOut,"\tOverlap: %s\n", ol->name);
					//OutputDebugStringA(debugOut);
					PGFXRECT ri = Intersection(pguiEnv->state->focusCurrent, ol);
					if (ri != NULL)
					{
						//sprintf(debugOut,"\tIntersecting: %s\n", ri->name);
						//OutputDebugStringA(debugOut);						
						ListAddStart(pguiEnv->intersectionList, ri);
						//System->out->println("\tIntersect:name: " +  ri->name);
						//System->out->println("\tIntersect:x: " +  ri->x);
						//System->out->println("\tIntersect:y: " +  ri->y);
						//System->out->println("\tIntersect:w: " +  ri->width);
						//System->out->println("\tIntersect:h: " +  ri->height);
					}
				}
				node = node->next;
			}
			DeallocList(overlaps);
		}

		bRet = TRUE;
	}
	else if (highhit != NULL && pguiEnv->state->focusCurrent == highhit)
	{
		//System->out->println(highhit->name + " STILL HAS FOCUS");
		sprintf(__fx_debugOut, "%s Still Has Focus.\n", highhit->name);
		OutputDebugStringA(__fx_debugOut);
	}

	//sprintf(debugOut,"WM_LBUTTONDOWN x: %d y: %d %p \n", 
	//		xPos, yPos, highhit);
	//OutputDebugStringA(debugOut);	

	return bRet;
}

BOOL OnCtlClick(int xPos, int yPos)
{
	BOOL bRet = FALSE;

	OutputDebugStringA("OnCtlClick\n");

	PFXUIENV pguiEnv = __fx_penv;
	//PGFXRECT highhit = GetSelectedRect(hitlist,xPos,yPos);
	PGFXRECT highhit = GetSelectedRect(pguiEnv->renderList, xPos, yPos, FX_ATTR_VISIBLE);
	if (highhit != NULL)
	{
		//OutputDebugStringA("OnCtlClick::GetSelectedRect...\n");

		if (pguiEnv->state->focusCurrent != NULL && pguiEnv->state->focusCurrent != highhit)
		{
			pguiEnv->state->focusCurrent->renderColor = pguiEnv->state->focusCurrent->color;
			//OutputDebugStringA("FX_LOST_FOCUS:");	
			//OutputDebugStringA(pguiEnv->state->focusCurrent->name);	
		}

		highhit->attr &= (~FX_ATTR_VISIBLE);
		highhit->attr |= (FX_ATTR_ERASE);
		highhit->renderColor = (COLORREF)RGB(64, 64, 64);
		highhit->z = 0;

		PFXNODE t = ListRemove(pguiEnv->renderList, highhit);
		ListAddStart(pguiEnv->renderList, highhit);
		DeallocNode(t);

		// must add previous
		pguiEnv->state->focusCurrent = highhit;

		//System->out->println("FX_GOT_FOCUS: " +  pguiEnv->state->focusCurrent->name);
		//sprintf(debugOut,"OnCtlClick::FX_GOT_FOCUS: %s \n",pguiEnv->state->focusCurrent->name);
		//OutputDebugStringA(debugOut);

		//ListClear(pguiEnv->intersectionList);


		//PFXNODELIST overlaps = GetOverLappedRect(pguiEnv->state->focusCurrent,hitlist);
		//sprintf(debugOut,"OnCtlClick::Overlaps currentFocus: %s\n", pguiEnv->state->focusCurrent->name);
		//OutputDebugStringA(debugOut);	
		PFXNODELIST overlaps = GetOverLappedRect(pguiEnv->state->focusCurrent, pguiEnv->renderList);
		if (overlaps != NULL)
		{
			//OutputDebugStringA("OnCtlClick::OVERLAPS:\n");
			PFXNODE node = overlaps->head;
			while (node != NULL)
			{
				PGFXRECT ol = (PGFXRECT)(node->data);
				if (ol && ((ol->attr & FX_ATTR_DESKTOP) != FX_ATTR_DESKTOP))
				{
					ol->attr |= FX_ATTR_INVALID;
					fxInvalidateWindow(ol,1);
					//sprintf(debugOut,"\tOverlap: %s\n", ol->name);
					//OutputDebugStringA(debugOut);

					/*
					PGFXRECT ri = Intersection(pguiEnv->state->focusCurrent,ol);
					if(ri!=NULL)
					{
						//sprintf(debugOut,"\tIntersecting: %s\n", ri->name);
						//OutputDebugStringA(debugOut);

						ListAddStart(pguiEnv->intersectionList, ri);
						//System->out->println("\tIntersect:name: " +  ri->name);
						//System->out->println("\tIntersect:x: " +  ri->x);
						//System->out->println("\tIntersect:y: " +  ri->y);
						//System->out->println("\tIntersect:w: " +  ri->width);
						//System->out->println("\tIntersect:h: " +  ri->height);
					}
					*/
				}
				node = node->next;
			}
			DeallocList(overlaps);
		}

		bRet = TRUE;
	}
	return bRet;
}

BOOL OnMove(int xPos, int yPos)
{
	BOOL bRet = FALSE;

	PFXUIENV pguiEnv = __fx_penv;

	char debugOut[256];

	PGFXRECT highhit = GetSelectedRect(pguiEnv->renderList, xPos, yPos, -1);
	if (highhit != NULL)
	{

		if (highhit != pguiEnv->state->focusHover)
		{
			if (pguiEnv->state->focusHover)
			{
				//sprintf(debugOut,"FX_MOUSE_LEAVE_1: %s \n",pguiEnv->state->focusHover->name);
				//OutputDebugStringA(debugOut);
				//pguiEnv->state->focusHover->renderColor = pguiEnv->state->focusHover->color;
				pguiEnv->state->focusHover = NULL;
			}
			pguiEnv->state->focusHover = highhit;
			//pguiEnv->state->focusHover->renderColor = RGB(128, 128, 128);
			//sprintf(debugOut,"FX_MOUSE_ENTER: %s \n",pguiEnv->state->focusHover->name);
			//OutputDebugStringA(debugOut);
			bRet = TRUE;
		}
	}

	return bRet;
}



