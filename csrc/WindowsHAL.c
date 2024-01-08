#include "FXDevices.h"
#include "FXWindow.h"
#include "WindowsHAL.h"
#include "pgm.h"

void drvRedrawScreen(PFXUIENV env,BOOL bBackground)
{
	PFXGFXFUNCTABLE vid = (PFXGFXFUNCTABLE)(env->devdrv->pDriverFunctionTable);
	if(vid)
	{
		DrawRectangles((HDC)(env->devdrv->pDriverData), env->renderList);
	}
}

BOOL __irqEventHandler(void* pEnv,int eventId,int wParm, long lParm)
{
	/*
	char debugOut[256];
	sprintf(debugOut,"EventHandler id:%d wParm:%d lParm:%d \n", 
    eventId,
	wParm,
	lParm);
    OutputDebugStringA(debugOut);
	*/
	PFXUIENV pguiEnv = (PFXUIENV)pEnv;
	
	switch(eventId)
	{
	case WM_CREATE:
		{
			OutputDebugStringA("HAL CREATE...");
		}
		break;
	case WM_TIMER:
		{
			OutputDebugStringA("HAL TICK...");
		}
		break;
	case WM_RBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParm); 
			int yPos = GET_Y_LPARAM(lParm); 

			AddRect("Workbench", xPos, yPos, 400,200, (void*)clientProc );
			drvRedrawScreen(pguiEnv,TRUE);
		}	
		break;
	/*
	case WM_MOUSEMOVE:
		{
			int xPos = GET_X_LPARAM(lParm); 
			int yPos = GET_Y_LPARAM(lParm); 

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
		}
		break;
		*/
	};
	
	
}




