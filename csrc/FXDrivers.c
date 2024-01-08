#include "FXDevices.h"

PFXGFXFUNCTABLE LoadWindowsVideoDriver();

PFXDEVDRV LoadDriver(const char* driverName)
{
	PFXDEVDRV drv = NULL;
	
	drv = (PFXDEVDRV)malloc(sizeof(FXDEVDRV));
	drv->pDriverData = NULL;
	drv->pDriverFunctionTable = LoadWindowsVideoDriver();

	return drv;
}
