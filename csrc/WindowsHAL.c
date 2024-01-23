#include "FXDevices.h"
#include "FXHAL.h"
#include "FXWindow.h"
#include "WindowsHAL.h"
#include "pgm.h"

#include <process.h>

int _timer_count[] = { 0,0 };

FXHDWMSG  		_fx_msg;
PHALWINCTX 		_fx_ctx;
PFXUIENV 		_fx_env   = NULL;
RECT*    		_hal_rect = NULL;
PFXDEVDRV   	_hal_drv  = NULL;
PFXGFXFUNCTABLE _hal_vid  = NULL;

PFXDEVDRV		_hal_driver_table[16];


CRITICAL_SECTION _hal_queue_cs;

HANDLE   _hal_cpu_thread = NULL;
unsigned _hal_cpu_thread_id = 0;

PHALWINENV _hal_windows_environment = NULL;

char _hal_debug_buffer[256];

void _hal_debug(const char* message)
{
	OutputDebugStringA(message);
}

void _hal_debug_int(const char* message, int val)
{
	sprintf(_hal_debug_buffer, message, val);
	OutputDebugStringA(_hal_debug_buffer);
}

void _hal_debug_string(const char* message, const char* val)
{
	sprintf(_hal_debug_buffer, message, val);
	OutputDebugStringA(_hal_debug_buffer);
}

void _hal_debug_pointer(const char* message, void* val)
{
	sprintf(_hal_debug_buffer, message, val);
	OutputDebugStringA(_hal_debug_buffer);
}


void _hal_queue_lock()
{
	//OutputDebugStringA("_hal_queue_lock\n");
	EnterCriticalSection(&_hal_queue_cs);
}

void _hal_queue_unlock()
{
	//OutputDebugStringA("_hal_queue_unlock\n");
	LeaveCriticalSection(&_hal_queue_cs);
}

void drvRedrawScreen(PFXUIENV env, BOOL bBackground)
{
	PFXGFXFUNCTABLE vid = (PFXGFXFUNCTABLE)(env->devdrv->pDriverFunctionTable);
	if(vid)
	{
		DrawRectangles((HDC)(env->devdrv->pDriverData), env->renderList);
	}
}


unsigned __stdcall _hal_cpu_proc(LPVOID lpParameter)
{
	OutputDebugStringA("_hal_cpu_proc enter...");
	while(TRUE)
	{
		_hal_cpu_time();
	}
}

void _hal_set_ctx(void* ctx)
{
	_fx_ctx = (PHALWINCTX)ctx;
}

void _hal_cpu_time()
{
	_fx_cpu_time();
}

int _hal_irq_signal(void* pEnv, int eventId, int wParm, long lParm)
{
	/*
	char debugOut[256];
	sprintf(debugOut,"EventHandler id:%d wParm:%d lParm:%d \n",
	eventId,
	wParm,
	lParm);
	OutputDebugStringA(debugOut);
	*/


	//PFXUIENV pguiEnv = (PFXUIENV)pEnv;
	switch(eventId)
	{
	case WM_CREATE:
		{
			OutputDebugStringA("HAL WM_CREATE...");
			
			_hal_windows_environment = (PHALWINENV)pEnv;

			memset(_hal_driver_table,0,sizeof(PFXDEVDRV) * 16);

			char debug[256];
			sprintf(debug,"_hal_windows_environment->hWnd %p\n",_hal_windows_environment->hWnd);
			OutputDebugStringA(debug);
			
			InitializeCriticalSection(&_hal_queue_cs);

			//OutputDebugStringA("_beginthreadex\n");
			_hal_cpu_thread = (HANDLE)_beginthreadex(NULL, 0, &_hal_cpu_proc, NULL, 
			                                         CREATE_SUSPENDED, 
													 &_hal_cpu_thread_id);
			
			_fx_init_hardware(FALSE);
			
			_fx_env   = InitUIEnvironment(sizeof(RECT));
			_hal_rect = (RECT*)_fx_env->state->driverData;
			
			_fx_env->evtHandler = _hal_irq_signal;
			
			OutputDebugStringA("LoadDriver(WindowsVideoDriver)");
			_hal_drv = LoadDriver("WindowsVideoDriver");
			_hal_drv->pDriverData = (void*)_hal_windows_environment->hWnd;
			
			_hal_driver_table[_hal_drv->type] = _hal_drv;
			
			_hal_vid = ((PFXGFXFUNCTABLE)_hal_drv->pDriverFunctionTable);
			if(_hal_vid)
			{
				OutputDebugStringA("Loaded(WindowsVideoDriver)");
				_hal_vid->Info(NULL, NULL);
				_hal_vid->Initialize(NULL, NULL);
				_hal_vid->Uninitialize(NULL, NULL);
				_hal_vid->BitBlt(NULL, NULL);
				_hal_vid->DrawRect(NULL, NULL);
			}
			OutputDebugStringA("Table Set(WindowsVideoDriver)");
			
			_fx_env->devdrv       = _hal_drv;		
			
			OutputDebugStringA("ResumeThread _hal_cpu_thread...");

			if(_hal_cpu_thread)
				ResumeThread(_hal_cpu_thread);	

			_fx_enable_interrupts(TRUE);
		}
		break;
	case WM_TIMER:
		{
			//OutputDebugStringA("HAL TICK...");
			
			_timer_count[wParm]++;

			/*
			RECT r;
			
			r.top = 0;
			r.left = 0;
			r.bottom = 100;
			r.right = 100;
			
			_hal_vid->DrawFillRect(_hal_drv,&r,RGB(128,128,0));
			*/
			
			if(wParm == 2)
			{
				//_fx_cpu_time();
			}
			else
			{
				_fx_msg.type = wParm;
				_fx_msg.irq = 1;
				_fx_msg.size = 4;
				_fx_msg.l_data1 = _timer_count[wParm];

				_fx_irq_signal(_fx_msg.type, &_fx_msg);
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			_fx_msg.type = FX_IRQ_MOUSE_L;
			_fx_msg.irq = 1;
			_fx_msg.size = 4;
			_fx_msg.w_data1 = wParm;
			_fx_msg.w_data2 = 1;
			_fx_msg.l_data1 = lParm;

			_fx_irq_signal(_fx_msg.type, &_fx_msg);
		}
		break;
	case WM_LBUTTONUP:
		{
			_fx_msg.type = FX_IRQ_MOUSE_L;
			_fx_msg.irq = 1;
			_fx_msg.size = 4;
			_fx_msg.w_data1 = wParm;
			_fx_msg.w_data2 = 0;
			_fx_msg.l_data1 = lParm;

			_fx_irq_signal(_fx_msg.type, &_fx_msg);
		}
		break;
	case WM_RBUTTONDOWN:
		{
			_fx_msg.type = FX_IRQ_MOUSE_R;
			_fx_msg.irq = 1;
			_fx_msg.size = 4;
			_fx_msg.w_data1 = wParm;
			_fx_msg.w_data2 = 1;
			_fx_msg.l_data1 = lParm;

			_fx_irq_signal(_fx_msg.type, &_fx_msg);
		}
		break;
	case WM_RBUTTONUP:
		{
			_fx_msg.type = FX_IRQ_MOUSE_R;
			_fx_msg.irq = 1;
			_fx_msg.size = 4;
			_fx_msg.w_data1 = wParm;
			_fx_msg.w_data2 = 0;
			_fx_msg.l_data1 = lParm;

			_fx_irq_signal(_fx_msg.type, &_fx_msg);
		}
		break;

	case WM_MOUSEMOVE:
		{
			int xPos = GET_X_LPARAM(lParm);
			int yPos = GET_Y_LPARAM(lParm);

			_fx_msg.type = FX_IRQ_MOUSE;
			_fx_msg.irq = 4;
			_fx_msg.size = 4;
			_fx_msg.w_data1 = 0;
			_fx_msg.l_data1 = xPos;
			_fx_msg.l_data2 = yPos;

			_fx_irq_signal(_fx_msg.type, &_fx_msg);

			/*
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
			*/
		}
		break;
	case WM_CHAR:
		{
			_fx_msg.type = FX_IRQ_KEYBOARD;
			_fx_msg.irq = 2;
			_fx_msg.size = 4;
			_fx_msg.w_data1 = wParm;
			_fx_msg.l_data1 = 0;
			_fx_msg.l_data2 = 0;

			_fx_irq_signal(_fx_msg.type, &_fx_msg);		
		}
		break;
	};
	
	
	
	return FALSE;

}



