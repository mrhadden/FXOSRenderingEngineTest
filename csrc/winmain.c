#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>

#include "FXWindow.h"
#include "FXDevices.h"
#include "WindowsHAL.h"

#include "pgm.h"

int isShifted = 0;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

PFXUIENV pguiEnv   = NULL;
RECT*    pdragRect = NULL;
PFXDEVDRV       drv;
PFXGFXFUNCTABLE vid;


int pgmIndex = 0;
//FXWndProc pgms[] = { clientProc1,clientProc2 ,clientProc3 };
FXWndProc pgms[] = { controlProc };

char debugOut[1024];
const char* pInstructions = "Right Click to add a Window.  Focus: %p";

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	const wchar_t* CLASS_NAME  = L"Sample Window Class";
    
	WNDCLASS wc;

	memset(&wc,0,sizeof(WNDCLASS));

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
	wc.hCursor       = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    RegisterClass(&wc);

    // Create the window.
	//pguiEnv = InitUIEnvironment(sizeof(RECT));
	//pdragRect = (RECT*)pguiEnv->state->driverData;

	PFXNODELIST test = AllocListMax("test",256);
	if(test)
	{
		for(int i=0;i<10;i++)
			ListAddStart(test, (void*)i);
		int s = ListSize(test);
		sprintf(debugOut,"list size: %d",s);
		OutputDebugStringA(debugOut);	

		for(int i=0;i<15;i++)
		{
			PFXNODE n = ListRemoveEnd(test);
			if(n)
			{
				int s = ListSize(test);
				sprintf(debugOut,"list data: %p",n->data);
				OutputDebugStringA(debugOut);
			}	
			else
			{
				OutputDebugStringA("list data: NULL");
			}
			sprintf(debugOut,"list size: %d",ListSize(test));
			OutputDebugStringA(debugOut);
		}

	}

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"FXOS Render Testing",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        1000, 100, 500, 500,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);

    MSG msg ;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
	case WM_CREATE:
		{
			pguiEnv = InitUIEnvironment(sizeof(RECT));
			pdragRect = (RECT*)pguiEnv->state->driverData;
			//pguiEnv->evtHandler = __irqEventHandler;
			
			drv = LoadDriver("WindowsVideoDriver");
			vid = ((PFXGFXFUNCTABLE)drv->pDriverFunctionTable);
			if(vid)
			{
				vid->Info(NULL, NULL);
				vid->Initialize(NULL, NULL);
				vid->Uninitialize(NULL, NULL);
				vid->BitBlt(NULL, NULL);
				vid->DrawFillRect(NULL, NULL);
				vid->DrawRect(NULL, NULL);
			}
			drv->pDriverData = GetDC(hwnd);
			pguiEnv->devdrv = drv;
			
			//pguiEnv->evtHandler(pguiEnv,uMsg,wParam,lParam);
			
			//SetTimer(hwnd,1,2000,NULL);	
			OutputDebugStringA("SET WM_TIMER\n");			
			SetTimer(hwnd,1,10,NULL);				
		}
		break;
	case WM_TIMER:
		{
			//OutputDebugStringA("WM_TIMER\n");
			
			RedrawScreen(hwnd,FALSE);
			/*
			if(IsInvalidRects())
			{
				RedrawScreen(hwnd,FALSE);
				//OutputDebugStringA("INVALID RECT DETECTED\n");
			}
			*/
		}
		break;		
	case WM_SIZE:
		{
			//pguiEnv->evtHandler(pguiEnv,uMsg,wParam,lParam);
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
			
			//pguiEnv->evtHandler(pguiEnv,uMsg,wParam,lParam);
			
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
				
				char text[256];
				sprintf(text ,pInstructions, pguiEnv->state->focusCurrent);

				TextOutA(hdc,10,10,text,strlen(text));
				
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
			//pguiEnv->evtHandler(pguiEnv,WM_MOUSEMOVE,wParam,lParam);
			
			
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 

			if(IsDragging(pguiEnv))
			{
				HDC hdc = GetDC(hwnd);
				if(hdc)
				{
					RECT target;

					DrawFocusRect(hdc, pdragRect);

					yPos = yPos - pguiEnv->state->dragOffset.y;
					xPos = xPos - pguiEnv->state->dragOffset.x;
					
					target.top    = yPos;
					target.left   = xPos;
					target.bottom = target.top  + pguiEnv->state->focusCurrent->height;
					target.right  = target.left + pguiEnv->state->focusCurrent->width;
					
					DrawFocusRect(hdc,&target);

					pdragRect->top    = yPos;
					pdragRect->left   = xPos;
					pdragRect->bottom = target.top  + pguiEnv->state->focusCurrent->height;
					pdragRect->right  = target.left + pguiEnv->state->focusCurrent->width;


					ReleaseDC(hwnd, hdc);
				}				
			}
			else
			{
				if(wParam & MK_LBUTTON)
				{
					OutputDebugStringA("WM_MOUSEMOVE with MK_LBUTTON\n");
					if(pguiEnv->state->isNonClient)
					{
						OutputDebugStringA("WM_MOUSEMOVE DragStart\n");
						
						DragStart(pguiEnv,xPos,yPos);

						pdragRect->top    = pguiEnv->state->focusCurrent->y;
						pdragRect->left   = pguiEnv->state->focusCurrent->x;
						pdragRect->bottom = pdragRect->top  + pguiEnv->state->focusCurrent->height;
						pdragRect->right  = pdragRect->left + pguiEnv->state->focusCurrent->width;

						HDC hdc =  GetDC(hwnd);
						if(hdc)
						{
							DrawFocusRect(hdc,pdragRect);
							ReleaseDC(hwnd, hdc);
						}											
					}					
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
			//pguiEnv->evtHandler(pguiEnv,WM_LBUTTONDOWN,wParam,lParam);
			
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 

			if( GetKeyState(VK_CONTROL ) & 0x8000 )
			{
				//OutputDebugStringA("LEFT CONTROL CLICK!\n");
				if(OnCtlClick(xPos,yPos))
				{
					RedrawScreen(hwnd,FALSE);
				}
			}
			else if( GetKeyState(VK_SHIFT ) & 0x8000 )
			{
				//OutputDebugStringA("LEFT SHIFT CLICK!\n");
				//DragStart(pguiEnv, xPos, yPos);

				DragStart(pguiEnv,xPos,yPos);

				pdragRect->top    = yPos;
				pdragRect->left   = xPos;
				pdragRect->bottom = yPos + 100;
				pdragRect->right  = xPos + 100;

				HDC hdc = GetDC(hwnd);
				if(hdc)
				{
					//HBRUSH hBrush = CreateHatchBrush(HS_HORIZONTAL,RGB(200,200,200));	
				
					//FrameRect(hdc,pdragRect,hBrush);
					DrawFocusRect(hdc,pdragRect);

					ReleaseDC(hwnd, hdc);
				}	

			}
			else
			{
				if(OnClick(xPos,yPos))
				{
					RedrawScreen(hwnd,FALSE);
				}
				
				if(pguiEnv->state->isNonClient)
				{
					if(PointInRect((PGFXRECT)pguiEnv->state->focusCurrent->nonclientList->head->data,xPos,yPos ))
					{
						OutputDebugStringA("OnClick NON-CLIENT CLOSE");
						if(OnCtlClick(xPos,yPos))
						{
							RedrawScreen(hwnd,FALSE);
						}
						return FALSE;
					}
					
					/*
					DragStart(pguiEnv,xPos,yPos);

					pdragRect->top    = pguiEnv->state->focusCurrent->y;
					pdragRect->left   = pguiEnv->state->focusCurrent->x;
					pdragRect->bottom = pdragRect->top  + pguiEnv->state->focusCurrent->height;
					pdragRect->right  = pdragRect->left + pguiEnv->state->focusCurrent->width;

					HDC hdc =  GetDC(hwnd);
					if(hdc)
					{
						DrawFocusRect(hdc,pdragRect);
						ReleaseDC(hwnd, hdc);
					}
					*/
				}
			}
			//InvalidateRect(hwnd, NULL, TRUE);	
		}
		break;
	case WM_LBUTTONUP:
		{
			//pguiEnv->evtHandler(pguiEnv,WM_LBUTTONUP,wParam,lParam);
			
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam);
			if(IsDragging(pguiEnv))
			{	
			    OutputDebugStringA("WM_LBUTTONUP End Drag.\n");
				yPos = yPos - pguiEnv->state->dragOffset.y;
				xPos = xPos - pguiEnv->state->dragOffset.x;				
		
				DragEnd(pguiEnv, xPos, yPos);

				MoveFXWindow(hwnd, pguiEnv, pguiEnv->state->focusCurrent, xPos, yPos);
			}
			
			//InvalidateRect(hwnd, NULL, TRUE);	
		}
		break;
	case WM_RBUTTONDOWN:
		{
			//pguiEnv->evtHandler(pguiEnv,WM_RBUTTONDOWN,wParam,lParam);
			
			
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 

			if( GetKeyState(VK_CONTROL ) & 0x8000 )
			{
				OutputDebugStringA("RIGHT CONTROL CLICK!\n");
				RedrawScreen(hwnd,TRUE);
			}
			else if( GetKeyState(VK_SHIFT ) & 0x8000 )
			{
				VisitList(pguiEnv->renderList,DebugNode);
			}
			else
			{
				//AddRect("Workbench", xPos, yPos, 400,200, (void*)clientProc );
				//AddRect("Workbench", xPos, yPos, 400, 200, (void*)pgms[pgmIndex++]);
				AddRect("Workbench", xPos, yPos, 400, 200, (void*)pgms[0]);
				if(pgmIndex > 2)
					pgmIndex = 0;

				RedrawScreen(hwnd,TRUE);
				//sprintf(debugOut,"WM_RBUTTONDOWN x: %d y: %d\n", xPos, yPos);
				//OutputDebugStringA(debugOut);
			}
			

		}
		break;
	case WM_NCMOUSELEAVE:
		{
			//pguiEnv->evtHandler(pguiEnv,WM_NCMOUSELEAVE,wParam,lParam);
			
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 

			//sprintf(debugOut,"WM_NCMOUSELEAVE x: %d y: %d\n", 
			//        xPos, yPos);
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
	case WM_KEYUP:
		{
			if(wParam == VK_SHIFT)
			{
				isShifted = 0;
			}			
		}
		break;
	case WM_KEYDOWN:
		{
			int keycode = wParam;

			//sprintf(debugOut, "WM_KEYDOWN x: %d (%d)\n",keycode, (lParam & 0x80000) == 0x80000);
			//OutputDebugStringA(debugOut);
			
			if(wParam == VK_SHIFT)
			{
				isShifted = 1;
			}
			else
			{
				if(!isShifted)
					wParam+=32;
				
				
				if(pguiEnv && pguiEnv->state->focusCurrent)
				{
					((FXWndProc)pguiEnv->state->focusCurrent->wndProc)(GetDC(hwnd),2,wParam,0, pguiEnv->state->focusCurrent);
				}
			}

		}
		break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
