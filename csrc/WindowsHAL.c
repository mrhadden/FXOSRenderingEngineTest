#include "FXDevices.h"
#include "FXHAL.h"
#include "FXWindow.h"
#include "WindowsHAL.h"
#include "pgm.h"

int _timer_count[] = {0,0};

FXHDWMSG _fx_msg;

void _hal_queue_lock()
{
	OutputDebugStringA("_hal_queue_lock\n");
}

void _hal_queue_unlock()
{
	OutputDebugStringA("_hal_queue_unlock\n");
}

void drvRedrawScreen(PFXUIENV env,BOOL bBackground)
{
	PFXGFXFUNCTABLE vid = (PFXGFXFUNCTABLE)(env->devdrv->pDriverFunctionTable);
	if(vid)
	{
		DrawRectangles((HDC)(env->devdrv->pDriverData), env->renderList);
	}
}

int __irqEventHandler(void* pEnv,int eventId,int wParm, long lParm)
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
			_fx_init_hardware();
		}
		break;
	case WM_TIMER:
		{
			_timer_count[wParm]++;
			
			OutputDebugStringA("HAL TICK...");
			
			_fx_msg.type = wParm;
			_fx_msg.irq  = 1;
			_fx_msg.size = 4;
			_fx_msg.data = (void*)_timer_count;
			
			_fx_irq_signal(_fx_msg.type, &_fx_msg);
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
	return FALSE;
	
}




