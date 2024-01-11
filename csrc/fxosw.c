#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <process.h>

#include "FXWindow.h"
#include "FXDevices.h"
#include "WindowsHAL.h"

#include "pgm.h"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HALWINCTX ctx;

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


    HWND hWnd = CreateWindowEx(
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


    if (hWnd == NULL)
    {
        return 0;
    }
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
			OutputDebugStringA("WM_CREATE\n");
			
			ctx.hWnd = hWnd;
			ctx.hDC  = GetDC(ctx.hWnd);
			
			_hal_set_ctx(&ctx);
			_hal_irq_signal(NULL,uMsg,wParam,lParam);
			
			ResumeThread(hCpuThread);
		}
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;			
			HDC hdc = BeginPaint(hWnd, &ps);
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
				sprintf(text ,pInstructions, NULL);

				TextOutA(hdc,10,10,text,strlen(text));
				
				SelectObject(hdc, hOldFont);
				DeleteObject(hFont);

				//DrawRectangles(hdc, pguiEnv->renderList);	
				EndPaint(hWnd, &ps);
			}

			OutputDebugStringA("WM_PAINT!\n");
        }
        return 0;
	default:
		_hal_irq_signal(NULL,uMsg,wParam,lParam);
		break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
