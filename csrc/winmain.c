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

#include "pgm.h"


RECT dragRect;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

PFXUIENV pguiEnv = NULL;

HWND chwnd = NULL;

char debugOut[1024];
unsigned char FONTDATA[768];
const char* pInstructions = "Right Click to add a Window.";

ApplyWindowAttr fApplyChrome[] = {AddCloseGadget,AddTitleBarGadget,AddTitleGadget,NULL};

void RedrawScreen(BOOL bBackground);


void MoveFXWindow(PFXUIENV pEnv, PGFXRECT p ,int xPos, int yPos)
{
	HDC hdc =  GetDC(chwnd);
	if(hdc)
	{ 
		RECT target;

		DrawFocusRect(hdc,&dragRect);
		
		PFXNODE t = ListRemove(pEnv->renderList,p);
		//sprintf(debugOut,"ListRemove %p\n",t);	
		//OutputDebugStringA(debugOut);

		PGFXRECT g = (PGFXRECT)(t->data);
		//sprintf(debugOut,"RECT %s\n",g->name);	
		//OutputDebugStringA(debugOut);

		PFXNODELIST overlaps = GetOverLappedRect(g,pEnv->renderList);
		if(overlaps!=NULL)
		{
			//OutputDebugStringA("MoveFXWindow::OVERLAPS:\n");
			PFXNODE node = overlaps->head;
			while(node != NULL)
			{
				PGFXRECT ol = (PGFXRECT)(node->data);
				if(ol && ((ol->attr & FX_ATTR_DESKTOP) != FX_ATTR_DESKTOP))
				{
					ol->attr|=FX_ATTR_INVALID;
				}
				node = node->next;
			}
			DeallocList(overlaps);
		}		

		FillRect(hdc, ToWinRECT(&target,g), CreateSolidBrush((COLORREF)RGB(64,64,64)));
		MoveRect(g, xPos, yPos);
		pEnv->state->focusCurrent = NULL;

		ListAddEnd(pEnv->renderList,g);

		RedrawScreen(FALSE);
	}	
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
    
	//OutputDebugStringA("wWinMain...\n");
	
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
	wc.hCursor       = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    RegisterClass(&wc);

    // Create the window.

	/*
	FILE* ff = fopen("Envious2.fnt","w");
	if(ff)
	{
		fwrite(&FONT_ENVIOUS_SERIF_BITMAP,768,1,ff);
		fclose(ff);
	}
	*/
	FILE* ff = fopen("font/Envious.fnt","r");
	if(ff)
	{
		fread(&FONTDATA,768,1,ff);
		fclose(ff);
	}

	pguiEnv = InitUIEnvironment();

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
	//OutputDebugStringA("GetMessage...\n");
	
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void DebugNode(struct node* p)
{
	GFXRECT* g = (GFXRECT*)p->data;
	
	sprintf(debugOut,"%s[%d]: %d %d %d %d %x\n",g->name,g->z,g->x,g->y,g->width,g->height,g->attr);	
	OutputDebugStringA(debugOut);  
}

void __Unhighlight(PFXNODE p)
{
	GFXRECT* g = (GFXRECT*)p->data;	
	g->renderColor = g->color;
}

void Unhighlight()
{
	VisitList(pguiEnv->renderList,__Unhighlight);
}

PGFXRECT AddRect(const char* name, int xPos, int yPos, int width, int height)
{
	//OutputDebugStringA("AddRect...\n");

	PGFXRECT r = AllocRectEx(name,xPos,yPos,width,height,-1,FX_ATTR_VISIBLE);
	r->szname = strlen(r->name);
	r->color = RGB(125,125,125);
	r->renderColor = RGB(52, 146, 235);
	r->attr|=FX_ATTR_INVALID;

	r->clientRect = AllocRectEx(name,
							    xPos   + FXM_BORDERSIZE,
							    yPos   + (FXM_BORDERSIZE + FXM_TITLEHEIGHT),
							    width  - (FXM_BORDERSIZE * 2),
							    height - (FXM_BORDERSIZE + FXM_TITLEHEIGHT + FXM_BORDERSIZE),
							    -1,
								FX_ATTR_VISIBLE);

	r->wndProc = (void*)(fWndProcs[0]);

	//VisitList(renderList,Unhighlight);
	Unhighlight();

	ListAddStart(pguiEnv->knownRects,r);
	ListAddEnd(pguiEnv->renderList,r);

	//VisitList(renderList,DebugNode);
	if(pguiEnv->state->focusCurrent)
		pguiEnv->state->focusCurrent->attr|=FX_ATTR_INVALID;

	pguiEnv->state->focusCurrent = r;

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
		ReleaseDC(chwnd, hdc);
	}
}

void RedrawInvalid(PFXNODE p)
{
	RECT target;

	PGFXRECT r = (PGFXRECT)p->data;
	if(r->attr & FX_ATTR_VISIBLE && (r->attr & FX_ATTR_INVALID))
	{
		HDC hdc =  GetDC(chwnd);

		FillRect(hdc, ToWinRECT(&target, r), CreateSolidBrush((COLORREF)RGB(64,64,64)));
		ReleaseDC(chwnd, hdc);

		r->attr&=(~FX_ATTR_INVALID);
	}
}

void RedrawVisible(PFXNODE p)
{
	RECT target;
	PGFXRECT r = (PGFXRECT)p->data;

	if(r->attr & FX_ATTR_VISIBLE)
	{
		r->attr|=(FX_ATTR_INVALID);
	}
}

VOID DrawRectangles(HDC hdc, PFXNODELIST renderList)
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
			
			if(!r->nonclientList)
			{
				r->nonclientList = AllocList();
				while(fApplyChrome[i])
				{
					PGFXRECT rc = fApplyChrome[i++](NULL,r);
					if(rc)
					{
						ListAddStart(r->nonclientList, rc);
					}
				}				
			}
			
			i = 0;
			while(fApplyChrome[i])
			{
				PGFXRECT rc = fApplyChrome[i++](hdc,r);
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

void RedrawScreen(BOOL bBackground)
{
	HDC hdc =  GetDC(chwnd);
	if(hdc)
	{
		DrawRectangles(hdc,pguiEnv->renderList);
		ReleaseDC(chwnd, hdc);
	}
}

BOOL OnClick(int xPos, int yPos)
{
	BOOL bRet = FALSE;

	BOOL bIsDblClick = IsDblClick(pguiEnv);
	if(bIsDblClick)
	{
		OutputDebugStringA("Double Click!!");
	}

	PGFXRECT highhit = GetSelectedRect(pguiEnv->renderList,xPos,yPos,FX_ATTR_VISIBLE);

	pguiEnv->state->isNonClient = FALSE;
	if(highhit && !PointInRect(highhit->clientRect,xPos,yPos))
	{	
		pguiEnv->state->isNonClient = TRUE;	
		OutputDebugStringA("NON-CLIENT SET...\n");
	}

	if(highhit!=NULL && pguiEnv->state->focusCurrent!=highhit)
	{
		OutputDebugStringA("OnClick::GetSelectedRect...\n");

		if(pguiEnv->state->focusCurrent!=NULL && pguiEnv->state->focusCurrent!=highhit)
		{
			pguiEnv->state->focusCurrent->renderColor = pguiEnv->state->focusCurrent->color;
			pguiEnv->state->focusCurrent->attr|=FX_ATTR_INVALID;
			OutputDebugStringA("FX_LOST_FOCUS:");	
			OutputDebugStringA(pguiEnv->state->focusCurrent->name);	
		}
		
		highhit->renderColor = RGB(52, 146, 235);
		highhit->z           = NextDepth();
		highhit->attr|=FX_ATTR_INVALID;
		

		PFXNODE t = ListRemove(pguiEnv->renderList,highhit);
		ListAddEnd(pguiEnv->renderList,highhit);
		DeallocNode(t);
		
		pguiEnv->state->focusCurrent = highhit;
		
		sprintf(debugOut,"FX_GOT_FOCUS: %s \n",pguiEnv->state->focusCurrent->name);
		OutputDebugStringA(debugOut);
		
		ListClear(pguiEnv->intersectionList);
		
		
		//sprintf(debugOut,"Overlaps currentFocus: %s\n", pguiEnv->state->focusCurrent->name);
		//OutputDebugStringA(debugOut);	
		PFXNODELIST overlaps = GetOverLappedRect(pguiEnv->state->focusCurrent,pguiEnv->renderList);
		if(overlaps!=NULL)
		{
			//OutputDebugStringA("OVERLAPS:\n");
			PFXNODE node = overlaps->head;
			while(node != NULL)
			{
				PGFXRECT ol = (PGFXRECT)(node->data);
				if(ol && ((ol->attr & FX_ATTR_DESKTOP) != FX_ATTR_DESKTOP))
				{
					//ol->attr|=FX_ATTR_INVALID;

					//sprintf(debugOut,"\tOverlap: %s\n", ol->name);
					//OutputDebugStringA(debugOut);
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
				}
				node = node->next;
			}
			DeallocList(overlaps);
		}
		
		bRet = TRUE;
	}
	else if(highhit!=NULL && pguiEnv->state->focusCurrent==highhit)
	{
		//System->out->println(highhit->name + " STILL HAS FOCUS");
		sprintf(debugOut,"%s Still Has Focus.\n", highhit->name);
		OutputDebugStringA(debugOut);	
	}	
	
	//sprintf(debugOut,"WM_LBUTTONDOWN x: %d y: %d %p \n", 
	//		xPos, yPos, highhit);
	//OutputDebugStringA(debugOut);	
	
	return bRet;
}

BOOL OnCtlClick(int xPos, int yPos)
{
	BOOL bRet = FALSE;
	//PGFXRECT highhit = GetSelectedRect(hitlist,xPos,yPos);
	PGFXRECT highhit = GetSelectedRect(pguiEnv->renderList,xPos,yPos,FX_ATTR_VISIBLE);
	if(highhit!=NULL)
	{
		//OutputDebugStringA("OnCtlClick::GetSelectedRect...\n");

		if(pguiEnv->state->focusCurrent!=NULL && pguiEnv->state->focusCurrent!=highhit)
		{
			pguiEnv->state->focusCurrent->renderColor = pguiEnv->state->focusCurrent->color;
			//OutputDebugStringA("FX_LOST_FOCUS:");	
			//OutputDebugStringA(pguiEnv->state->focusCurrent->name);	
		}
		
		highhit->attr&=(~FX_ATTR_VISIBLE);
		highhit->attr|=(FX_ATTR_ERASE);
		highhit->renderColor = (COLORREF)RGB(64,64,64);
		highhit->z           = 0;
		
		PFXNODE t = ListRemove(pguiEnv->renderList,highhit);
		ListAddStart(pguiEnv->renderList,highhit);
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
		PFXNODELIST overlaps = GetOverLappedRect(pguiEnv->state->focusCurrent,pguiEnv->renderList);
		if(overlaps!=NULL)
		{
			//OutputDebugStringA("OnCtlClick::OVERLAPS:\n");
			PFXNODE node = overlaps->head;
			while(node != NULL)
			{
				PGFXRECT ol = (PGFXRECT)(node->data);
				if(ol && ((ol->attr & FX_ATTR_DESKTOP) != FX_ATTR_DESKTOP))
				{
					ol->attr|=FX_ATTR_INVALID;

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

	PGFXRECT highhit = GetSelectedRect(pguiEnv->renderList,xPos,yPos,-1);
	if(highhit!=NULL)
	{

		if(highhit!=pguiEnv->state->focusHover)
		{
			if(pguiEnv->state->focusHover)
			{
				//sprintf(debugOut,"FX_MOUSE_LEAVE_1: %s \n",pguiEnv->state->focusHover->name);
				//OutputDebugStringA(debugOut);
				pguiEnv->state->focusHover->renderColor = pguiEnv->state->focusHover->color;
				pguiEnv->state->focusHover = NULL;
			}
			pguiEnv->state->focusHover = highhit;
			pguiEnv->state->focusHover->renderColor = RGB(128,128,128);
			//sprintf(debugOut,"FX_MOUSE_ENTER: %s \n",pguiEnv->state->focusHover->name);
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
			VisitList(pguiEnv->renderList,RedrawVisible);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	case WM_ERASEBKGND:
		{
	
		}
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
			VisitList(pguiEnv->renderList,RedrawVisible);

            HDC hdc = BeginPaint(hwnd, &ps);
			if(hdc)
			{
				

				FillRect(hdc, &ps.rcPaint, CreateSolidBrush((COLORREF)RGB(64,64,64)));

				HFONT hFont = CreateFontA(16, 8, 0, 0, FW_NORMAL,
					               FALSE, FALSE, FALSE, ANSI_CHARSET,
					               OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, VARIABLE_PITCH,
					               ("Consolas"));
				HFONT hOldFont = (HFONT) SelectObject(hdc, hFont); // <-- add this

				SetBkColor(hdc,(COLORREF)RGB(64,64,64));
				SetTextColor(hdc,(COLORREF)RGB(255,255,255));


				TextOutA(hdc,10,10,pInstructions,strlen(pInstructions));
				
				SelectObject(hdc, hOldFont);
				DeleteObject(hFont);

				DrawRectangles(hdc, pguiEnv->renderList);	
				EndPaint(hwnd, &ps);
			}

			OutputDebugStringA("WM_PAINT!\n");
        }
        return 0;
	case WM_MOUSEMOVE:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 

			if(IsDragging(pguiEnv))
			{
				//OutputDebugStringA("Dragging!\n");	
				HDC hdc =  GetDC(hwnd);
				if(hdc)
				{
					LOGBRUSH LogBrush;
					RECT target;

					//HBRUSH hBack = CreateSolidBrush(RGB(64,64,64));	
					/*
					sprintf(debugOut,"DRAG MOVE x: %d y: %d dx: %d dy: %d ox: %d oy: %d \n",
					xPos,
					yPos,
					pguiEnv->state->dragStart.x,
					pguiEnv->state->dragStart.y,
					pguiEnv->state->dragOffset.x,
					pguiEnv->state->dragOffset.y);
					OutputDebugStringA(debugOut);
					*/
					
					//FrameRect(hdc,&dragRect,hBack);
					DrawFocusRect(hdc,&dragRect);
					//HBRUSH hBrush = CreateHatchBrush(HS_HORIZONTAL,RGB(200,200,200));	
					/*
					target.top = yPos;
					target.left = xPos;
					target.bottom = yPos + 100;
					target.right = xPos + 100;
					*/
					yPos = yPos - pguiEnv->state->dragOffset.y;
					xPos = xPos - pguiEnv->state->dragOffset.x;
					
					target.top    = yPos;
					target.left   = xPos;
					target.bottom = target.top  + pguiEnv->state->focusCurrent->height;
					target.right  = target.left + pguiEnv->state->focusCurrent->width;
					
					//FrameRect(hdc,&target,hBrush);
					DrawFocusRect(hdc,&target);
					/*
					dragRect.top = yPos;
					dragRect.left = xPos;
					dragRect.bottom = yPos + 100;
					dragRect.right = xPos + 100;
					*/
					dragRect.top    = yPos;
					dragRect.left   = xPos;
					dragRect.bottom = target.top  + pguiEnv->state->focusCurrent->height;
					dragRect.right  = target.left + pguiEnv->state->focusCurrent->width;


					ReleaseDC(chwnd, hdc);
				}				
			}

			if( GetKeyState(VK_SHIFT ) & 0x8000 )
			{
				OutputDebugStringA("LEFT SHIFT MOVE!\n");
			}
			else
			{
				if(!pguiEnv->state->focusHover)
				{
					//sprintf(debugOut,"WM_MOUSEMOVE x: %d y: %d\n", 
					//		xPos, yPos);
					//OutputDebugStringA(debugOut);
				}
				OnMove(xPos,yPos);
				//if(OnMove(xPos,yPos))
				//	InvalidateRect(hwnd, NULL, TRUE);				
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 

			if( GetKeyState(VK_CONTROL ) & 0x8000 )
			{
				//OutputDebugStringA("LEFT CONTROL CLICK!\n");
				if(OnCtlClick(xPos,yPos))
				{
					RedrawScreen(FALSE);
				}
			}
			else if( GetKeyState(VK_SHIFT ) & 0x8000 )
			{
				//OutputDebugStringA("LEFT SHIFT CLICK!\n");
				//DragStart(pguiEnv, xPos, yPos);

				DragStart(pguiEnv,xPos,yPos);

				dragRect.top    = yPos;
				dragRect.left   = xPos;
				dragRect.bottom = yPos + 100;
				dragRect.right  = xPos + 100;

				HDC hdc =  GetDC(hwnd);
				if(hdc)
				{
					//HBRUSH hBrush = CreateHatchBrush(HS_HORIZONTAL,RGB(200,200,200));	
				
					//FrameRect(hdc,&dragRect,hBrush);
					DrawFocusRect(hdc,&dragRect);

					ReleaseDC(chwnd, hdc);
				}	

			}
			else
			{
				if(OnClick(xPos,yPos))
				{
					RedrawScreen(FALSE);
				}
				
				if(pguiEnv->state->isNonClient)
				{
					if(PointInRect((PGFXRECT)pguiEnv->state->focusCurrent->nonclientList->head->data,xPos,yPos ))
					{
						//OutputDebugStringA("OnClick NON-CLIENT CLOSE");
						if(OnCtlClick(xPos,yPos))
						{
							RedrawScreen(FALSE);
						}
						return FALSE;
					}

					DragStart(pguiEnv,xPos,yPos);

					dragRect.top    = pguiEnv->state->focusCurrent->y;
					dragRect.left   = pguiEnv->state->focusCurrent->x;
					dragRect.bottom = dragRect.top  + pguiEnv->state->focusCurrent->height;
					dragRect.right  = dragRect.left + pguiEnv->state->focusCurrent->width;

					HDC hdc =  GetDC(hwnd);
					if(hdc)
					{
						DrawFocusRect(hdc,&dragRect);
						ReleaseDC(chwnd, hdc);
					}											
				}
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam);
			if(IsDragging(pguiEnv))
			{	
				yPos = yPos - pguiEnv->state->dragOffset.y;
				xPos = xPos - pguiEnv->state->dragOffset.x;				
		
				DragEnd(pguiEnv, xPos, yPos);

				MoveFXWindow(pguiEnv, pguiEnv->state->focusCurrent, xPos, yPos);
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
			else if( GetKeyState(VK_SHIFT ) & 0x8000 )
			{
				VisitList(pguiEnv->renderList,DebugNode);
			}
			else
			{
				AddRect("Workbench", xPos, yPos, 400,200);
				RedrawScreen(TRUE);
				//sprintf(debugOut,"WM_RBUTTONDOWN x: %d y: %d\n", xPos, yPos);
				//OutputDebugStringA(debugOut);
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

			if(pguiEnv->state->focusHover)
			{
				//sprintf(debugOut,"FX_MOUSE_LEAVE_2: %s \n",pguiEnv->state->focusHover->name);
				//OutputDebugStringA(debugOut);
				pguiEnv->state->focusHover->renderColor = pguiEnv->state->focusHover->color;
				pguiEnv->state->focusHover = NULL;
			}


		}
		break;

    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
