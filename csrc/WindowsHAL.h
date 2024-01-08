#ifndef __WIN_HAL
#define __WIN_HAL

#include "FXDevices.h"
#include "FXWindow.h"
#include <windowsx.h>

BOOL __irqEventHandler(void* pEnv,int eventId,int wParm, long lParm);

#endif