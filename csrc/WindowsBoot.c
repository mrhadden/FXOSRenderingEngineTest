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


HALWINENV	halEnvironment;


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
	const wchar_t* CLASS_NAME  = L"FXOSWindowsEmulator";
    
	WNDCLASS wc;

	memset(&wc,0,sizeof(WNDCLASS));

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
	wc.hCursor       = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(0,                              // Optional window styles.
							   CLASS_NAME,                     // Window class
							   L"FXOS Dev Emulator",    // Window text
							   WS_OVERLAPPEDWINDOW,            // Window style
							   // Size and position
							   1000, 100, 500, 500,
							   NULL,       // Parent window
							   NULL,       // Menu
							   hInstance,  // Instance handle
							   NULL        // Additional application data
							   );
    if (hWnd == NULL)
    {
        return 0;
    }
	
	halEnvironment.hInstance     = hInstance;
	halEnvironment.hPrevInstance = hPrevInstance;
	halEnvironment.pCmdLine 	 = pCmdLine;
	halEnvironment.nCmdShow 	 = nCmdShow;

    ShowWindow(hWnd, nCmdShow);

    MSG msg ;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
	case WM_CREATE:
		{
			halEnvironment.hWnd = hWnd;
			
			_hal_irq_signal(&halEnvironment,uMsg,wParam,lParam);
			
			SetTimer(hWnd,1,1000,NULL);		
		}
		break;
	case WM_TIMER:
		{
			_hal_irq_signal(pguiEnv,uMsg,wParam,lParam);
		}
		break;		
	case WM_SIZE:
		{
			_hal_irq_signal(pguiEnv,uMsg,wParam,lParam);
		}
		break;
	case WM_ERASEBKGND:
		{
			_hal_irq_signal(pguiEnv,uMsg,wParam,lParam);
		}
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
						
            HDC hdc = BeginPaint(hWnd, &ps);
			if(hdc)
			{
				//VisitList(pguiEnv->renderList,RedrawVisible);
				//DrawRectanglesV2(hdc, pguiEnv->renderList);	
				_hal_irq_signal(pguiEnv,uMsg,wParam,lParam);
				EndPaint(hWnd, &ps);
			}

			OutputDebugStringA("WM_PAINT!\n");
        }
        return 0;
	case WM_MOUSEMOVE:
		{
			_hal_irq_signal(pguiEnv,uMsg,wParam,lParam);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			_hal_irq_signal(pguiEnv,uMsg,wParam,lParam);
		}
		break;
	case WM_LBUTTONUP:
		{
			_hal_irq_signal(pguiEnv,uMsg,wParam,lParam);	
		}
		break;
	case WM_RBUTTONDOWN:
		{
			_hal_irq_signal(pguiEnv,uMsg,wParam,lParam);
		}
		break;
	case WM_RBUTTONUP:
		{
			_hal_irq_signal(pguiEnv,uMsg,wParam,lParam);
		}
		break;
	case WM_NCMOUSELEAVE:
		{
			_hal_irq_signal(pguiEnv,uMsg,wParam,lParam);
		}
		break;
	case WM_CHAR:
		{
			_hal_irq_signal(pguiEnv,uMsg,wParam,lParam);
		}
		break;
	case WM_KEYUP:
		{
			_hal_irq_signal(pguiEnv,uMsg,wParam,lParam);		
		}
		break;
	case WM_KEYDOWN:
		{
			_hal_irq_signal(pguiEnv,uMsg,wParam,lParam);
		}
		break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
