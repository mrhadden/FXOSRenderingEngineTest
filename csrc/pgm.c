

#include "pgm.h"
#include "FXWindow.h"

//HFXFONT hEnvious = LoadFont("font/Hourglass.fnt");
HFXFONT hEnvious = NULL;




BOOL clientProcBase(HDC hdc, const char* fmt, PGFXRECT winRect)
{
    RECT target;

	PGMDATA* pd = NULL;
	
	if(winRect->parent)
	{
		pd = (PGMDATA*)winRect->parent->wndData;
		//winRect->parent->attr |= FX_ATTR_INVALID;
	}
	else
	{
		pd = (PGMDATA*)winRect->wndData;
		//winRect->attr |= FX_ATTR_INVALID;
	}
	OutputDebugStringA("clientProc enter...");

	if(!hEnvious)
		 hEnvious = LoadFont("font/Hourglass.fnt");

	OutputDebugStringA("clientProc font loaded...");

	//const char* caption = "Client Text\0";
	//const char* caption = "Client Workbench\0";

	char buffer[256];

	


	sprintf(buffer, fmt,  (void*)winRect);
	const char* caption = (const char*)buffer;

    ToWinRECT(&target, winRect);

	OutputDebugStringA("clientProc fxRenderText...");

	fxRenderText(hdc,caption,
	             target.left + 1 + FXM_BORDERSIZE,
			     target.top  + 1 + FXM_BORDERSIZE,
			     hEnvious, 
			     (COLORREF)RGB(0,0,0));

	OutputDebugStringA("clientProc fxRenderText data...");


	if(pd)
	{
		sprintf(buffer, "Instance Data: %d\n", pd->nIndex);
		fxSetWindowTitle(winRect->parent, pd->caption);
	}
	else
		sprintf(buffer, "Instance Data: MISSING WNDDATA\n");

	fxRenderText(hdc, buffer,
		target.left + 1 + FXM_BORDERSIZE,
		target.top  + 1 + FXM_BORDERSIZE + 10,
		hEnvious,
		(COLORREF)RGB(0, 0, 0));


	fxRenderText(hdc,GetFontName(hEnvious),
	             target.left + 1 + FXM_BORDERSIZE,
			     target.top  + 1 + FXM_BORDERSIZE + 20,
			     hEnvious, 
			     (COLORREF)RGB(0,0,0));
			  
	for(int x=0;x<200;x++)
		SetPixel(hdc,
				 target.left + 1 + FXM_BORDERSIZE + x,
				 target.top  + 1 + FXM_BORDERSIZE + 30,
				 ((COLORREF)RGB(255,0,0)));


	OutputDebugStringA("clientProc fxRenderText after data...");
	if(pd)
		pd->nIndex += 1;

	OutputDebugStringA("clientProc fxRenderText incremented...");

	return TRUE;
}

BOOL clientProc1(HDC hdc, int msgId, int wParam, int lParam, PGFXRECT winRect)
{
	char buffer[256];

	PGMDATA* pd = ((PGMDATA*)winRect->wndData);

	if(msgId == 1 && winRect)
	{

		winRect->wndData = malloc(sizeof(PGMDATA));
		if(winRect->wndData)
		{
			pd = ((PGMDATA*)winRect->wndData);
			pd->caption = (const char*)malloc(64);
			memset((char*)pd->caption,0,64);
			//if(((PGMDATA*)winRect->wndData)->caption)
			//	strcpy((char*)((PGMDATA*)winRect->wndData)->caption, "Control Panel");


			char buffer[256];
			sprintf(buffer, "Client 1 CREATE: %p  Value: %d \n", winRect->wndData, ((PGMDATA*)winRect->wndData)->nIndex);
			OutputDebugStringA(buffer);
		}

		return TRUE;
	}
	else if(msgId == 2)
	{
		//if(strlen(pd->caption > 0))
		
		if(pd->caption)
		{
			if(strlen(pd->caption) == 0)
				((char*)pd->caption)[0] = wParam;
			else
				((char*)pd->caption)[strlen(pd->caption)] = wParam;

			OutputDebugStringA(pd->caption);
			if(winRect->parent)
			{
				pd = (PGMDATA*)winRect->parent->wndData;
				winRect->parent->attr |= FX_ATTR_INVALID;
			}
			else
			{
				pd = (PGMDATA*)winRect->wndData;
				winRect->attr |= FX_ATTR_INVALID;
			}
			//RedrawScreen(NULL, FALSE);
		}
	}

	return clientProcBase(hdc, "Client 1 %p", winRect);
}

BOOL clientProc2(HDC hdc, int msgId, int wParam, int lParam, PGFXRECT winRect)
{
	if(msgId == 1 && winRect)
	{
		winRect->wndData = malloc(sizeof(PGMDATA));
		if(winRect->wndData)
		{
			((PGMDATA*)winRect->wndData)->nIndex = 20;
			((PGMDATA*)winRect->wndData)->caption = (const char*)malloc(64);
			if(((PGMDATA*)winRect->wndData)->caption)
				strcpy((char*)((PGMDATA*)winRect->wndData)->caption, "System");

			char buffer[256];
			sprintf(buffer, "Client 2 CREATE: %p  Value: %d \n", winRect->wndData, ((PGMDATA*)winRect->wndData)->nIndex);
			OutputDebugStringA(buffer);
		}

		return TRUE;
	}
	return clientProcBase(hdc, "Client 2 %p", winRect);
}

BOOL clientProc3(HDC hdc, int msgId, int wParam, int lParam, PGFXRECT winRect)
{
	if(msgId == 1 && winRect)
	{
		winRect->wndData = malloc(sizeof(PGMDATA));
		if(winRect->wndData)
		{
			((PGMDATA*)winRect->wndData)->nIndex = 20;
			((PGMDATA*)winRect->wndData)->caption = (const char*)malloc(64);
			if(((PGMDATA*)winRect->wndData)->caption)
				strcpy((char*)((PGMDATA*)winRect->wndData)->caption, "Notepad");

			char buffer[256];
			sprintf(buffer, "Client 3 CREATE: %p  Value: %d \n", winRect->wndData, ((PGMDATA*)winRect->wndData)->nIndex);
			OutputDebugStringA(buffer);
		}

		return TRUE;
	}
	return clientProcBase(hdc, "Client 3 %p", winRect);
}

BOOL controlProc(HDC hdc, int msgId, int wParam, int lParam, PGFXRECT winRect)
{
	char buffer[256];

	RECT target;

	if(!winRect)
		return TRUE;


	if(msgId == 1)
	{


		winRect->wndData = malloc(sizeof(CTLDATA));
		CTLDATA* pd = (CTLDATA*)winRect->wndData;
		if(pd)
		{
			memset(pd->text, 0, 256);
			//strcpy(pd->text,"Sample Text.");

			
			sprintf(buffer, "CONTROLPROC init RECT: %p  DATA: %p \n", winRect, winRect->wndData);
			OutputDebugStringA(buffer);

			//winRect->color = RGB(64, 64, 64);
		}
	}
	else if(msgId == 2)
	{
		sprintf(buffer, "CONTROLPROC MSG2 RECT: %p  DATA: %p \n", winRect, winRect->wndData);
		OutputDebugStringA(buffer);



		if(winRect->wndData)
		{
			//sprintf(buffer, "CONTROLPROC MSG PARENT: %p \n", winRect->parent->wndData);
			sprintf(buffer, "CONTROLPROC MSG2 RECT: %p  DATA: %p \n", winRect, winRect->wndData);
			OutputDebugStringA(buffer);

			CTLDATA* pd = (CTLDATA*)winRect->wndData;
			if(pd)
			{
				if(strlen(pd->text) == 0)
				{
					((char*)pd->text)[0] = wParam;
				}
				else
				{
					((char*)pd->text)[strlen(pd->text)] = wParam;
				}

				OutputDebugStringA(pd->text);
				if(winRect->parent)
					winRect->parent->attr |= FX_ATTR_INVALID;
				else
					winRect->attr |= FX_ATTR_INVALID;
				//RedrawScreen(NULL,FALSE);
			}
		}
	}
	else
	{
		sprintf(buffer, "CONTROLPROC ELSE MSG: %p \n", winRect->wndData);
		OutputDebugStringA(buffer);

		sprintf(buffer, "CONTROLPROC ELSE MSG PARENT: %p \n", winRect->parent->wndData);
		OutputDebugStringA(buffer);

		if(winRect->wndData)
		{
			CTLDATA* pd = (CTLDATA*)winRect->wndData;
			if(pd)
			{
				ToWinRECT(&target, winRect);

				if(!hEnvious)
					hEnvious = LoadFont("font/Hourglass.fnt");

				fxRenderText(hdc,
							pd->text,
							target.left + 1 + FXM_BORDERSIZE,
							target.top + 1 + FXM_BORDERSIZE,
							hEnvious,
							(COLORREF)RGB(0, 0, 0));

				sprintf(buffer, "CONTROLPROC fxRenderText: %s \n", pd->text);
				OutputDebugStringA(buffer);
			}
		}
	}

	return TRUE;
}

BOOL iconProc(HDC hdc, int msgId, int wParam, int lParam, PGFXRECT winRect)
{
	if(msgId == 1 && winRect)
	{
		winRect->wndData = malloc(sizeof(PGMDATA));
		if(winRect->wndData)
		{
			((PGMDATA*)winRect->wndData)->nIndex = 20;
			((PGMDATA*)winRect->wndData)->caption = (const char*)malloc(64);
			if(((PGMDATA*)winRect->wndData)->caption)
				strcpy((char*)((PGMDATA*)winRect->wndData)->caption, "Notepad");

			char buffer[256];
			sprintf(buffer, "Client 3 CREATE: %p  Value: %d \n", winRect->wndData, ((PGMDATA*)winRect->wndData)->nIndex);
			OutputDebugStringA(buffer);
		}

		return TRUE;
	}
	return clientProcBase(hdc, "Client 3 %p", winRect);
}
