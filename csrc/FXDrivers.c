#include "FXDevices.h"

PFXGFXFUNCTABLE LoadWindowsVideoDriver();

PFXDEVDRV LoadDriver(const char* driverName)
{
	PFXDEVDRV drv = NULL;
	
	drv = (PFXDEVDRV)malloc(sizeof(FXDEVDRV));
	drv->pDriverData = NULL;
	
	if(stricmp("WindowsVideoDriver",driverName) == 0)
	{
		drv->type = FX_DRV_VIDEO;
		drv->pDriverFunctionTable = LoadWindowsVideoDriver();
	}
	
	return drv;
}
