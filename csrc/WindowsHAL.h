#ifndef __WIN_HAL
#define __WIN_HAL

#include "FXDevices.h"
#include "FXWindow.h"
#include <windowsx.h>
#include <synchapi.h>


typedef struct _hal_windows_ctx
{
	HWND hWnd;
	HDC  hDC;
}HALWINCTX;
typedef HALWINCTX* PHALWINCTX;


void _hal_set_ctx(void* ctx);
void _hal_cpu_time();
BOOL _hal_irq_signal(void* pEnv,int eventId,int wParm, long lParm);

#endif