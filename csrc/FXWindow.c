
#include "FXWindow.h"


PFXUIENV InitUIEnvironment()
{
    PFXUIENV env = (PFXUIENV)malloc(sizeof(FXUIENV));
	if(env)
	{
		memset(env,0,sizeof(FXUIENV));
		env->state = (PFXUISTATE)malloc(sizeof(FXUISTATE));
		memset(env->state,0,sizeof(FXUISTATE));
		
		env->knownRects = AllocNamedList("__known_rects");
		env->renderList = AllocNamedList("__render_rects");
		
        env->intersectionList  = AllocNamedList("__intersections");
		
        env->state->desktop = AllocRectEx("desktop",0,0,65000,65000,0,FX_ATTR_DESKTOP);
        env->state->desktop->color = RGB(64,64,64);
        
		ListAddStart(env->renderList, env->state->desktop);	
	}
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

    for(int i = 0;i<4;i++)
    {
        target.left   = winRect->x + FXM_BORDERSIZE ;
        //target.top    = winRect->y + (FXM_BORDERSIZE * 2) + (i*4);
		target.top    = winRect->y + FXM_BORDERSIZE + (i*4);
        target.right  = winRect->x + winRect->width - (FXM_BORDERSIZE * 2) - 10 - 2;
        target.bottom = target.top + 4 ;
        
        FrameRect(hdc, &target ,CreateSolidBrush(RGB(255,255,255)));
    }
}

void AddTitleGadget(HDC hdc, PGFXRECT winRect)
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
	title.right  = title.left  + (sFont * strlen(winRect->name)) + FXM_BORDERSIZE;
	title.bottom = title.top   + FXM_TITLEHEIGHT - FXM_BORDERSIZE;
	
	//FillRect(hdc,&title, CreateSolidBrush((COLORREF)RGB(255,255,255)));			
	FillRect(hdc,&title, CreateSolidBrush(winRect->renderColor));			
				
	FXTextOutEx(hdc,
	          winRect->name,
	          target.left + 1 + FXM_BORDERSIZE,
			  target.top  + FXM_BORDERSIZE + (FXM_TITLEHEIGHT/2) - 4,
			  (const unsigned char*)FONT_ENVIOUS_SERIF_BITMAP,
			  1,             			  
			  (COLORREF)RGB(255,255,255),
			  winRect->renderColor			  
			  );				
				
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
	
	GFXRECTP rt;
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
    }
    r->attr|=FX_ATTR_INVALID;
    //r->attr|=FX_ATTR_ERASE;

    return TRUE;
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
                    SetPixel(hdc,dx + c + (8 - x),dy + y,color);
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