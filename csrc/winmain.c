#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>

#include "GFXRECT.h"
#include "GFXRECTP.h"
#include "Point.h"
#include "List.h"

#include "FXWindow.h"

BOOL fillBackground = TRUE;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

GFXRECT* rectangles[10] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,};  

//RECT* prects[10] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,};  

PFXNODELIST knownRects   = AllocNamedList("__known_recs");
PFXNODELIST renderList   = AllocNamedList("__render_recs");

PFXNODELIST recNodes     = NULL;
PFXNODELIST hitlist      = NULL;
PFXNODELIST interlist    = NULL;
PGFXRECT    currentFocus = NULL;
PGFXRECT    desktop      = NULL;

PGFXRECT  	hoverFocus   = NULL;

BOOL __redrawMode       = FALSE;
BOOL __redrawBackground = FALSE;
HWND chwnd = NULL;

char debugOut[1024];

ApplyWindowAttr fApplyChrome[] = {AddCloseGadget,AddMinGadget,AddTitleGadget,NULL};

void clientProc(HDC hdc, PGFXRECT winRect)
{
    RECT target;

	const char* caption = "Client Text";

    ToWinRECT(&target, winRect);

    SetTextColor(hdc,((COLORREF)RGB(0,0,0)));
    SetBkColor(hdc,((COLORREF)RGB(255,255,255)));

    TextOutA(hdc,
             target.left + 1 + FXM_BORDERSIZE,
             target.top  + 1 + FXM_BORDERSIZE,
             caption,
             strlen(caption));	

	for(int x=0;x<200;x++)
		SetPixel(hdc,
				 target.left + 1 + FXM_BORDERSIZE + x,
				 target.top  + 1 + FXM_BORDERSIZE + 30,
				 ((COLORREF)RGB(255,0,0)));

}

FXWndProc fWndProcs[] = 
{
	clientProc,
	NULL
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    //const wchar_t CLASS_NAME[]  = L"Sample Window Class";
	const wchar_t* CLASS_NAME  = L"Sample Window Class";
    
	OutputDebugStringA("wWinMain...\n");
	
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
	wc.hCursor       = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    RegisterClass(&wc);

    // Create the window.
	OutputDebugStringA("CreateWindowEx...\n");

	recNodes  = AllocList();
	hitlist   = AllocList();
	interlist = AllocList();


	desktop = AllocRectEx("desktop",0,0,65000,65000,0,FX_ATTR_DESKTOP);
	desktop->color = RGB(64,64,64);
	ListAddStart(renderList, desktop);
	//ListAddStart(hitlist,    AllocRectEx("desktop",0,0,65000,65000,0,1));

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"FXOS Render Testing",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

	chwnd = hwnd;

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
	OutputDebugStringA("GetMessage...\n");
	
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
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


void DebugNode(struct node* p)
{
	GFXRECT* g = (GFXRECT*)p->data;
	
	sprintf(debugOut,"%s[%d]: %d %d %d %d\n",g->name,g->z,g->x,g->y,g->width,g->height);	
	OutputDebugStringA(debugOut);  
}

void __Unhighlight(PFXNODE p)
{
	GFXRECT* g = (GFXRECT*)p->data;	
	g->renderColor = g->color;
}

void Unhighlight()
{
	VisitList(renderList,__Unhighlight);
}


PGFXRECT AddGRect(const char* name, int xPos, int yPos, int width, int height)
{
	OutputDebugStringA("AddGRect...\n");

	PGFXRECT r = AllocRectEx(name,xPos,yPos,width,height,-1,FX_ATTR_VISIBLE);
	r->szname = strlen(r->name);
	r->color = RGB(125,125,125);
	r->renderColor = RGB(52, 146, 235);
	r->attr|=FX_ATTR_INVALID;

	r->clientRect = AllocRectEx(name,
							    xPos  + FXM_BORDERSIZE,
							    yPos  + (FXM_BORDERSIZE + FXM_TITLEHEIGHT),
							    width - (FXM_BORDERSIZE * 2),
							    height - (FXM_BORDERSIZE + FXM_TITLEHEIGHT + FXM_BORDERSIZE),
							    -1,
								FX_ATTR_VISIBLE);

	r->wndProc = (void*)(fWndProcs[0]);

	//VisitList(renderList,Unhighlight);
	Unhighlight();


	ListAddStart(knownRects,r);
	ListAddEnd(renderList,r);
	//VisitList(renderList,DebugNode);
	if(currentFocus)
		currentFocus->attr|=FX_ATTR_INVALID;
	currentFocus = r;

	return r;
}

void RedrawRect(PFXNODE p)
{
	RECT target;
	PGFXRECT r = (PGFXRECT)p->data;

	if(r->attr & FX_ATTR_VISIBLE)
	{
		HDC hdc =  GetDC(chwnd);

		FillRect(hdc, ToWinRECT(&target, r), CreateSolidBrush((COLORREF)RGB(0,0,0)));
		//FillRect(hdc, &target, CreateSolidBrush((COLORREF)RGB(0,0,0)));
		ReleaseDC(chwnd, hdc);
	}
}

//ol->attr|=FX_ATTR_INVALID;
void RedrawInvalid(PFXNODE p)
{
	RECT target;
	PGFXRECT r = (PGFXRECT)p->data;

	if(r->attr & FX_ATTR_VISIBLE && (r->attr & FX_ATTR_INVALID))
	{
		HDC hdc =  GetDC(chwnd);

		FillRect(hdc, ToWinRECT(&target, r), CreateSolidBrush((COLORREF)RGB(64,64,64)));
		//FillRect(hdc, &target, CreateSolidBrush((COLORREF)RGB(0,0,0)));
		ReleaseDC(chwnd, hdc);

		r->attr&=(~FX_ATTR_INVALID);
	}
}


VOID DrawRectangles(HDC hdc);

void RedrawScreen(BOOL bBackground)
{
	/*
	RECT target;

	target.top = 0;
	target.left = 0;
	target.bottom = 100;
	target.right = 100;

	if(bBackground)
		__redrawBackground = TRUE;
	__redrawMode = TRUE;

	HDC hdc =  GetDC(chwnd);

	FillRect(hdc, &target, CreateSolidBrush((COLORREF)RGB(0,0,0)));
	//InvalidateRect(chwnd, NULL, __redrawBackground);

	ReleaseDC(chwnd, hdc);
	*/
	//VisitList(renderList,RedrawRect);
	//VisitList(renderList,RedrawInvalid);

	//Sleep(500);

	HDC hdc =  GetDC(chwnd);
	if(hdc)
	{
		DrawRectangles(hdc);
		ReleaseDC(chwnd, hdc);
	}

}

VOID DrawRectangles(HDC hdc)
{
	RECT target;

	PFXNODE p = renderList->head;
	while(p != NULL)
	{
		PGFXRECT r = (PGFXRECT)p->data;
		if(!r)
			break;

		if((r->attr & FX_ATTR_VISIBLE) &&  (r->attr & FX_ATTR_INVALID))
		{
			FillRect(hdc, ToWinRECT(&target, r), CreateSolidBrush((COLORREF)r->renderColor));

			int i = 0;
			while(fApplyChrome[i])
			{
				fApplyChrome[i++](hdc,r);
			}

			if(r->clientRect)
			{
				FillRect(hdc, ToWinRECT(&target, r->clientRect), CreateSolidBrush((COLORREF)RGB(255,255,255)));	
				((FXWndProc)r->wndProc)(hdc,r->clientRect);
			}

			r->attr&=(~FX_ATTR_INVALID);
		}
		else if(r->attr & FX_ATTR_ERASE)
		{
			FillRect(hdc, ToWinRECT(&target, r), CreateSolidBrush((COLORREF)r->renderColor));
			r->attr &= (~FX_ATTR_ERASE);
		}
		p = p->next;
	}

}

PGFXRECT GetSelectedRect(PFXNODELIST objList,int mx,int my,int whichAttr)
{
	PGFXRECT highRect = NULL;
	
	//OutputDebugStringA("GetSelectedRect::enter...\n");
	
	if(!objList)
		return NULL;
	
	PFXNODE p = objList->head;
	while(p != NULL)
	{
		PGFXRECT r = (PGFXRECT)(p->data);
		//OutputDebugStringA("GetSelectedRect::got rect...\n");

		//r->attr|=FX_ATTR_INVALID;

		if((r && r->attr & whichAttr) || (whichAttr == -1))
		{
			if(r->x < mx && (r->x + r->width) > mx)
			{
				if(r->y < my && (r->y + r->height) > my)
				{
					//sprintf(debugOut,"GetSelectedRect::got hit x: %d y: %d %p \n",mx, my, r->name);
					//OutputDebugStringA(debugOut);	

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
			else
			{
				//OutputDebugStringA("GetSelectedRect::got miss...\n");
			}
		}
		p = p->next;
	}
	/*
	if(highRect)
	{
		sprintf(debugOut,"GetSelectedRect::EXIT highRect x: %d y: %d %p \n",mx, my, highRect->name);
		OutputDebugStringA(debugOut);
	}
	*/
	//OutputDebugStringA("GetSelectedRect::Exit...\n");
	
	//highRect->attr|=FX_ATTR_INVALID;

	return highRect;
}

BOOL OnClick(int xPos, int yPos)
{
	BOOL bRet = FALSE;
	//PGFXRECT highhit = GetSelectedRect(hitlist,xPos,yPos);
	PGFXRECT highhit = GetSelectedRect(renderList,xPos,yPos,FX_ATTR_VISIBLE);
	if(highhit!=NULL && currentFocus!=highhit)
	{
		OutputDebugStringA("OnClick::GetSelectedRect...\n");

		if(currentFocus!=NULL && currentFocus!=highhit)
		{
			currentFocus->renderColor = currentFocus->color;
			currentFocus->attr|=FX_ATTR_INVALID;
			OutputDebugStringA("FX_LOST_FOCUS:");	
			OutputDebugStringA(currentFocus->name);	
		}
		
		highhit->renderColor = RGB(52, 146, 235);
		highhit->z           = NextDepth();
		highhit->attr|=FX_ATTR_INVALID;
		
		PFXNODE t = ListRemove(renderList,highhit);
		ListAddEnd(renderList,highhit);
		DeallocNode(t);
		
		currentFocus = highhit;
		
		//System->out->println("FX_GOT_FOCUS: " +  currentFocus->name);
		sprintf(debugOut,"FX_GOT_FOCUS: %s \n",currentFocus->name);
		OutputDebugStringA(debugOut);
		
		ListClear(interlist);
		
		
		//PFXNODELIST overlaps = GetOverLappedRect(currentFocus,hitlist);
		sprintf(debugOut,"Overlaps currentFocus: %s\n", currentFocus->name);
		OutputDebugStringA(debugOut);	
		PFXNODELIST overlaps = GetOverLappedRect(currentFocus,renderList);
		if(overlaps!=NULL)
		{
			OutputDebugStringA("OVERLAPS:\n");
			PFXNODE node = overlaps->head;
			while(node != NULL)
			{
				PGFXRECT ol = (PGFXRECT)(node->data);
				if(ol && ((ol->attr & FX_ATTR_DESKTOP) != FX_ATTR_DESKTOP))
				{
					//ol->attr|=FX_ATTR_INVALID;

					sprintf(debugOut,"\tOverlap: %s\n", ol->name);
					OutputDebugStringA(debugOut);

					PGFXRECT ri = Intersection(currentFocus,ol);
					if(ri!=NULL)
					{
						sprintf(debugOut,"\tIntersecting: %s\n", ri->name);
						OutputDebugStringA(debugOut);						

						ListAddStart(interlist, ri);
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
	else if(highhit!=NULL && currentFocus==highhit)
	{
		//System->out->println(highhit->name + " STILL HAS FOCUS");
		sprintf(debugOut,"%s Still Has Focus.\n", highhit->name);
		OutputDebugStringA(debugOut);	
	}	
	
	sprintf(debugOut,"WM_LBUTTONDOWN x: %d y: %d %p \n", 
			xPos, yPos, highhit);

	
	//OutputDebugStringA(debugOut);	
	
	return bRet;
}

BOOL OnCtlClick(int xPos, int yPos)
{
	BOOL bRet = FALSE;
	//PGFXRECT highhit = GetSelectedRect(hitlist,xPos,yPos);
	PGFXRECT highhit = GetSelectedRect(renderList,xPos,yPos,FX_ATTR_VISIBLE);
	if(highhit!=NULL)
	{
		OutputDebugStringA("OnCtlClick::GetSelectedRect...\n");

		if(currentFocus!=NULL && currentFocus!=highhit)
		{
			currentFocus->renderColor = currentFocus->color;
			OutputDebugStringA("FX_LOST_FOCUS:");	
			OutputDebugStringA(currentFocus->name);	
		}
		
		highhit->attr&=(~FX_ATTR_VISIBLE);
		highhit->attr|=(FX_ATTR_ERASE);
		highhit->renderColor = (COLORREF)RGB(64,64,64);
		highhit->z           = 0;
		
		PFXNODE t = ListRemove(renderList,highhit);
		ListAddStart(renderList,highhit);
		DeallocNode(t);
		
		// must add previous
		currentFocus = highhit;
		
		//System->out->println("FX_GOT_FOCUS: " +  currentFocus->name);
		sprintf(debugOut,"OnCtlClick::FX_GOT_FOCUS: %s \n",currentFocus->name);
		OutputDebugStringA(debugOut);
		
		ListClear(interlist);
		
		
		//PFXNODELIST overlaps = GetOverLappedRect(currentFocus,hitlist);
		sprintf(debugOut,"OnCtlClick::Overlaps currentFocus: %s\n", currentFocus->name);
		OutputDebugStringA(debugOut);	
		PFXNODELIST overlaps = GetOverLappedRect(currentFocus,renderList);
		if(overlaps!=NULL)
		{
			OutputDebugStringA("OnCtlClick::OVERLAPS:\n");
			PFXNODE node = overlaps->head;
			while(node != NULL)
			{
				PGFXRECT ol = (PGFXRECT)(node->data);
				if(ol && ((ol->attr & FX_ATTR_DESKTOP) != FX_ATTR_DESKTOP))
				{
					ol->attr|=FX_ATTR_INVALID;

					sprintf(debugOut,"\tOverlap: %s\n", ol->name);
					OutputDebugStringA(debugOut);

					PGFXRECT ri = Intersection(currentFocus,ol);
					if(ri!=NULL)
					{
						sprintf(debugOut,"\tIntersecting: %s\n", ri->name);
						OutputDebugStringA(debugOut);						

						ListAddStart(interlist, ri);
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

	
	sprintf(debugOut,"WM_LBUTTONDOWN WITH CONTROL x: %d y: %d %p \n", 
			xPos, yPos, highhit);

	
	//OutputDebugStringA(debugOut);	
	
	return bRet;
}

BOOL OnMove(int xPos, int yPos)
{
	BOOL bRet = FALSE;

	//static PGFXRECT currentFocus = NULL;

	PGFXRECT highhit = GetSelectedRect(renderList,xPos,yPos,-1);
	if(highhit!=NULL)
	{

		if(highhit!=hoverFocus)
		{
			if(hoverFocus)
			{
				//sprintf(debugOut,"FX_MOUSE_LEAVE_1: %s \n",hoverFocus->name);
				//OutputDebugStringA(debugOut);
				hoverFocus->renderColor = hoverFocus->color;
				hoverFocus = NULL;
			}
			hoverFocus = highhit;
			hoverFocus->renderColor = RGB(128,128,128);
			//sprintf(debugOut,"FX_MOUSE_ENTER: %s \n",hoverFocus->name);
			//OutputDebugStringA(debugOut);
			bRet = TRUE;
		}
	}	
	

	
	return bRet;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

	case WM_SIZE:
		{
			//fillBackground = TRUE;
		}
		break;
	case WM_ERASEBKGND:
		{
			/*
			if(!fillBackground)
			{
				return 1;
			}	
			*/		
		}
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            RECT small;  
            HDC hdc = BeginPaint(hwnd, &ps);

			/*
			sprintf(debugOut,"WM_PAINT top: %d left: %d bottom: %d right: %d\n", 
			        ps.rcPaint.top, ps.rcPaint.left, 
					ps.rcPaint.bottom, ps.rcPaint.right);
			OutputDebugStringA(debugOut);
			*/
            // All painting occurs here, between BeginPaint and EndPaint.
            

			FillRect(hdc, &ps.rcPaint, CreateSolidBrush((COLORREF)RGB(64,64,64)));
			/*
			if(fillBackground)
			{
				FillRect(hdc, &ps.rcPaint, CreateSolidBrush((COLORREF)RGB(64,64,64)));
				fillBackground = FALSE;
			}
			*/
			DrawRectangles(hdc);	
            /*
			small.top = 10;
	        small.left = 10;
            small.right = 100;
            small.bottom = 100;	    
            FillRect(hdc, &small, (HBRUSH) (COLOR_WINDOW+2));
			*/
			//Output("top: %d left: %d", ps.rcPaint.top, ps.rcPaint.left);
			
            EndPaint(hwnd, &ps);
        }
        return 0;
	case WM_MOUSEMOVE:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 

			if(!hoverFocus)
			{
				sprintf(debugOut,"WM_MOUSEMOVE x: %d y: %d\n", 
						xPos, yPos);
				//OutputDebugStringA(debugOut);
			}
			OnMove(xPos,yPos);
			//if(OnMove(xPos,yPos))
			//	InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 

			if( GetKeyState(VK_CONTROL ) & 0x8000 )
			{
				OutputDebugStringA("LEFT CONTROL CLICK!\n");
				if(OnCtlClick(xPos,yPos))
				{
					//InvalidateRect(hwnd, NULL, TRUE);
					RedrawScreen(FALSE);
				}
			}
			else
			{
				if(OnClick(xPos,yPos))
				{
					//InvalidateRect(hwnd, NULL, TRUE);
					RedrawScreen(FALSE);
				}
			}
		}
		break;
	case WM_RBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 

			if( GetKeyState(VK_CONTROL ) & 0x8000 )
			{
				OutputDebugStringA("RIGHT CONTROL CLICK!\n");
				RedrawScreen(TRUE);
			}
			else
			{
				AddGRect(NULL, xPos, yPos, 400,200);
				//InvalidateRect(hwnd, NULL, TRUE);
				RedrawScreen(TRUE);
				sprintf(debugOut,"WM_RBUTTONDOWN x: %d y: %d\n", xPos, yPos);
				OutputDebugStringA(debugOut);
			}

		}
		break;
	case WM_NCMOUSELEAVE:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 

			sprintf(debugOut,"WM_NCMOUSELEAVE x: %d y: %d\n", 
			        xPos, yPos);
			//OutputDebugStringA(debugOut);

			if(hoverFocus)
			{
				//sprintf(debugOut,"FX_MOUSE_LEAVE_2: %s \n",hoverFocus->name);
				//OutputDebugStringA(debugOut);
				hoverFocus->renderColor = hoverFocus->color;
				hoverFocus = NULL;
			}


		}
		break;

    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
