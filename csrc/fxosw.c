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


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

PFXUIENV pguiEnv   = NULL;
RECT*    pdragRect = NULL;
PFXDEVDRV       drv;
PFXGFXFUNCTABLE vid;

char debugOut[1024];
const char* pInstructions = "Right Click to add a Window.  Focus: %p";


HANDLE hCpuThread = NULL;
DWORD  cpuThread = 0;

DWORD WINAPI CpuThreadProc(LPVOID lpParameter)
{
	OutputDebugStringA("CpuThreadProc enter...");
	while(TRUE)
	{
		OutputDebugStringA("CpuThreadProc running...");
		Sleep(1000);
	}
}


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
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

	hCpuThread = CreateThread(NULL, 0, CpuThreadProc, NULL, CREATE_SUSPENDED, &cpuThread);

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
			OutputDebugStringA("WM_CREATE\n");
			ResumeThread(hCpuThread);
		}
		break;
	case WM_TIMER:
		{
			//pguiEnv->evtHandler(pguiEnv,uMsg,wParam,lParam);
		}
		break;		
	case WM_SIZE:
		{
			//pguiEnv->evtHandler(pguiEnv,uMsg,wParam,lParam);
			//VisitList(pguiEnv->renderList,RedrawVisible);
			//InvalidateRect(hwnd, NULL, TRUE);
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
			
			//VisitList(pguiEnv->renderList,RedrawVisible);

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
				sprintf(text ,pInstructions, NULL);

				TextOutA(hdc,10,10,text,strlen(text));
				
				SelectObject(hdc, hOldFont);
				DeleteObject(hFont);

				//DrawRectangles(hdc, pguiEnv->renderList);	
				EndPaint(hwnd, &ps);
			}

			OutputDebugStringA("WM_PAINT!\n");
        }
        return 0;
	case WM_MOUSEMOVE:
		{

			
		}
		break;
	case WM_LBUTTONDOWN:
		{

		}
		break;
	case WM_LBUTTONUP:
		{

		}
		break;
	case WM_RBUTTONDOWN:
		{

		}
		break;
	case WM_NCMOUSELEAVE:
		{

		}
		break;

    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
