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
#include "Around.h"
#include "Shinobi.h"
#include "Envious.h"

RECT dragRect;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

PFXUIENV pguiEnv = NULL;

HWND chwnd = NULL;

char debugOut[1024];

ApplyWindowAttr fApplyChrome[] = {AddCloseGadget,AddMinGadget,AddTitleGadget,NULL};

void RedrawScreen(BOOL bBackground);


char letterA[] = 
{
0,0,0,1,1,0,0,0,
0,0,1,0,0,1,0,0,
0,1,0,0,0,0,1,0,
0,1,0,0,0,0,1,0,
0,1,1,1,1,1,1,0,
0,1,0,0,0,0,1,0,
0,1,0,0,0,0,1,0,
0,1,0,0,0,0,1,0,
};


char letterBinAX[] = 
{
0x18,
0x24,//0,0,1,0,0,1,0,0,
0x42,//0,1,0,0,0,0,1,0,
0x42,//0,1,0,0,0,0,1,0,
0x7E,//0,1,1,1,1,1,1,0,
0x42,//0,1,0,0,0,0,1,0,
0x42,//0,1,0,0,0,0,1,0,
0x42,//0,1,0,0,0,0,1,0,
};
char letterBinA[] = 
{
0x3e, 0x63, 0x41, 0x41, 0x7f, 0x41, 0x41, 0x41,
};



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

unsigned char FONTDATA[768];

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
	FILE* ff = fopen("Envious2.fnt","r");
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
				DrawRectangles(hdc, pguiEnv->renderList);	
				
				const char *message = "ABCDE - HELLO + abcd!\0";

				int index = 0;
				int c = 0;
				//for(int c=0;c<90;c+=9)
				while(*message)
				{

					//sprintf(debugOut,"FONT: %c %d %d\n",*message,(int)*message,(int)(*message-32));
					//OutputDebugStringA(debugOut);
					const unsigned char* fchar = &FONT_ENVIOUS_SERIF_BITMAP[(*message - 32)*8];

					for(int y=0;y<8;y++)
					{
						for(int x=0;x<8;x++)
						{
							if(((fchar[y]) >> x) & 1)
								SetPixel(hdc,10 + c + (8 - x),10 + y,(COLORREF)RGB(255,255,255));
						}
					}

					c+=9;
					message++;
				}

				/*
				message = "ABCDE - HELLO + abcd!\0";
				index = 0;
				c = 0;
				//for(int c=0;c<90;c+=9)
				while(*message)
				{

					//sprintf(debugOut,"FONT: %c %d %d\n",*message,(int)*message,(int)(*message-32));
					//OutputDebugStringA(debugOut);
					const unsigned char* fchar = &FONTDATA[(*message - 32)*8];

					for(int y=0;y<8;y++)
					{
						for(int x=0;x<8;x++)
						{
							if(((fchar[y]) >> x) & 1)
								SetPixel(hdc,10 + c + (8 - x),20 + y,(COLORREF)RGB(255,255,255));
						}
					}

					c+=9;
					message++;
				}
				*/

				FXTextOut(hdc,"ABCDE - HELLO + abcde!\0",10,20,(const unsigned char*)FONTDATA,(COLORREF)RGB(255,255,255));
				FXTextOutEx(hdc,"ABCDE - HELLO + abcde!\0",10,30,(const unsigned char*)FONTDATA,2,(COLORREF)RGB(255,0,0));

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

					//FrameRect(hdc,&dragRect,hBack);
					DrawFocusRect(hdc,&dragRect);
					//HBRUSH hBrush = CreateHatchBrush(HS_HORIZONTAL,RGB(200,200,200));	
					/*
					target.top = yPos;
					target.left = xPos;
					target.bottom = yPos + 100;
					target.right = xPos + 100;
					*/
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
					OutputDebugStringA("OnClick NON-CLIENT CLICK");
					DragStart(pguiEnv,xPos,yPos);

					dragRect.top    = pguiEnv->state->focusCurrent->y;
					dragRect.left   = pguiEnv->state->focusCurrent->x;
					dragRect.bottom = dragRect.top  + pguiEnv->state->focusCurrent->height;
					dragRect.right  = dragRect.left + pguiEnv->state->focusCurrent->width;

					HDC hdc =  GetDC(hwnd);
					if(hdc)
					{
						//HBRUSH hBrush = CreateHatchBrush(HS_HORIZONTAL,RGB(200,200,200));	
					
						//FrameRect(hdc,&dragRect,hBrush);
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
				/*
				HDC hdc =  GetDC(hwnd);
				if(hdc)
				{ 
					RECT target;

					DrawFocusRect(hdc,&dragRect);
					
					//FillRect(hdc, ToWinRECT(&target,pguiEnv->state->focusCurrent), CreateSolidBrush((COLORREF)RGB(64,64,64)));
					MoveRect(pguiEnv->state->focusCurrent, xPos, yPos);
					pguiEnv->state->focusCurrent = NULL;
					RedrawScreen(FALSE);
				}
				*/
				DragEnd(pguiEnv, xPos, yPos);
				MoveFXWindow(pguiEnv, pguiEnv->state->focusCurrent, xPos, yPos);
				//DragEnd(pguiEnv, xPos, yPos);
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
				AddRect(NULL, xPos, yPos, 400,200);
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
