#ifndef _FX_DEVICE
#define _FX_DEVICE

#include <windows.h>
#include <stdint.h>

#include "FXLIST.h"

#define FX_DRV_VIDEO	0x0F

typedef struct _fx_device_driver_ctx
{
    void* pContextData;
} FXDEVDRVCTX;
typedef FXDEVDRVCTX* PFXDEVDRVCTX;

typedef struct _fx_device_driver
{
	int	  type;
    void* pDriverData;
    void* pDriverFunctionTable;
} FXDEVDRV;
typedef FXDEVDRV* PFXDEVDRV;

typedef int PFXDEVVERB;
typedef struct _fx_device_command
{
    PFXDEVVERB verb;
    void* commandData;
} FXDEVDRVCMD;
typedef FXDEVDRVCMD* PFXDEVDRVCMD;

typedef int (*FXDeviceProc)(PFXDEVDRV, PFXDEVDRVCTX);
typedef int (*FXDeviceCommandProc)(PFXDEVDRV, PFXDEVDRVCTX, PFXDEVDRVCMD);

typedef struct _fx_device_driver_functions
{
    FXDeviceProc Info;
    FXDeviceProc Initialize;
    FXDeviceProc Uninitialize;
    FXDeviceProc Reset;
    FXDeviceCommandProc Command;
} FXDRVFUNCTABLE;
typedef FXDRVFUNCTABLE* PFXDRVFUNCTABLE;


typedef int (*funcDrawFillRect)(PFXDEVDRV drv, void*, int color);


typedef struct _fx_video_driver_functions
{
    FXDeviceProc Info;
    FXDeviceProc Initialize;
    FXDeviceProc Uninitialize;
    FXDeviceProc Reset;
    FXDeviceCommandProc Command;
    FXDeviceProc DrawPoint;
    FXDeviceProc DrawLine;
    FXDeviceProc DrawRect;
    funcDrawFillRect DrawFillRect;
    FXDeviceProc DrawFocusRect;
    FXDeviceProc GetPoint;
    FXDeviceProc BitBlt;
    FXDeviceProc SetPalette;
    FXDeviceProc GetPalette;
} FXGFXFUNCTABLE;
typedef FXGFXFUNCTABLE* PFXGFXFUNCTABLE;

PFXDEVDRV LoadDriver(const char* driverName);

#endif