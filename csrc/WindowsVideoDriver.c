#include "FXDevices.h"
#include <windows.h>


int drvInfo(PFXDEVDRV drv, PFXDEVDRVCTX ctx)
{
	OutputDebugStringA("Info\n");
	return 0;
}

int drvInitialize(PFXDEVDRV drv, PFXDEVDRVCTX ctx)
{
	OutputDebugStringA("Initialize\n");
	return 0;
}


int drvUninitialize(PFXDEVDRV drv, PFXDEVDRVCTX ctx)
{
	OutputDebugStringA("Uninitialize\n");
	return 0;
}


int drvReset(PFXDEVDRV drv, PFXDEVDRVCTX ctx)
{
	OutputDebugStringA("Reset\n");
	return 0;
}


int drvCommand(PFXDEVDRV drv, PFXDEVDRVCTX ctx, PFXDEVDRVCMD cmd)
{
	OutputDebugStringA("Command\n");
	return 0;
}


int drvDrawPoint(PFXDEVDRV drv, PFXDEVDRVCTX ctx)
{
	OutputDebugStringA("DrawPoint\n");
	return 0;
}


int drvDrawLine(PFXDEVDRV drv, PFXDEVDRVCTX ctx)
{
	OutputDebugStringA("DrawPoint\n");
	return 0;
}


int drvDrawRect(PFXDEVDRV drv, PFXDEVDRVCTX ctx)
{
	OutputDebugStringA("DrawRect\n");
	return 0;
}


int drvDrawFillRect(PFXDEVDRV drv, void* r, int color)
{
	char debug[256];
	
	sprintf(debug,"DrawFillRect %p %d\n",drv->pDriverData, color);
	OutputDebugStringA(debug);
	
	HDC hdc = GetDC((HWND)drv->pDriverData); 
	if(hdc)
	{
		FillRect(hdc, (RECT*)r, CreateSolidBrush((COLORREF)color));
		ReleaseDC((HWND)drv->pDriverData, hdc);
	}
	return 0;
}


int drvDrawFocusRect(PFXDEVDRV drv, PFXDEVDRVCTX ctx)
{
	OutputDebugStringA("DrawFillRect\n");
	return 0;
}


int drvGetPoint(PFXDEVDRV drv, PFXDEVDRVCTX ctx)
{
	OutputDebugStringA("GetPoint\n");
	return 0;
}


int drvBitBlt(PFXDEVDRV drv, PFXDEVDRVCTX ctx)
{
	OutputDebugStringA("BitBlt\n");
	return 0;
}


int drvSetPalette(PFXDEVDRV drv, PFXDEVDRVCTX ctx)
{
	OutputDebugStringA("SetPalette\n");
	return 0;
}

int drvGetPalette(PFXDEVDRV drv, PFXDEVDRVCTX ctx)
{
	OutputDebugStringA("GetPalette\n");
	return 0;
}


PFXGFXFUNCTABLE LoadWindowsVideoDriver()
{
	PFXDEVDRV drv = NULL;
	
	PFXGFXFUNCTABLE tbl = (PFXGFXFUNCTABLE)malloc(sizeof(FXGFXFUNCTABLE));
	if(tbl)
	{
		tbl->BitBlt = drvBitBlt;
		tbl->Command = drvCommand;
		tbl->DrawFillRect = drvDrawFillRect;
		tbl->DrawFocusRect = drvDrawFocusRect;
		tbl->DrawLine = drvDrawLine;
		tbl->DrawPoint = drvDrawPoint;
		tbl->DrawRect = drvDrawRect;
		tbl->GetPalette = drvGetPalette ;
		tbl->GetPoint = drvGetPoint;
		tbl->Info = drvInfo;
		tbl->Initialize = drvInitialize;
		tbl->Reset = drvReset;
		tbl->SetPalette = drvSetPalette;
		tbl->Uninitialize = drvUninitialize;
	}

	return tbl;
}
