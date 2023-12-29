
#include "FXWindow.h"


PFXUIENV InitUIEnvironment()
{
    PFXUIENV env = (PFXUIENV)malloc(sizeof(FXUIENV));
	if(env)
	{
		memset(list,0,sizeof(FXUIENV));
        env->recNodes  = AllocList();
        env->hitlist   = AllocList();
        env->interlist = AllocList();


        env->desktop = AllocRectEx("desktop",0,0,65000,65000,0,FX_ATTR_DESKTOP);
        env->desktop->color = RGB(64,64,64);
        ListAddStart(env->renderList, env->desktop);
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

