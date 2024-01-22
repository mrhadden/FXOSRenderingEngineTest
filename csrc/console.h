#ifndef __FX_CONSOLE
#define __FX_CONSOLE

#include <stdlib.h>
#include <string.h>
#include "FXBASE.h"
#include <windows.h>

typedef struct _fx_text_metrics
{
	int mode;
	int rows;
	int columns;
	char* textBuffer;
}FXTEXTMETRICS;
typedef FXTEXTMETRICS* PFXTEXTMETRICS;

typedef PFXTEXTMETRICS (*funcGetTextMetrics)(PFXTEXTMETRICS);
typedef void(*funcClearScreen)(void);
typedef void(*funcSetTextMode)(int);
typedef void(*funcSetChar)(int charCode, int row, int col);

#define TEXTMODE_40X25 (1)
#define TEXTMODE_80X25 (2)
#define TEXTMODE_80X43 (3)
#define TEXTMODE_80X50 (4)

typedef struct _fx_console_library
{
	funcSetTextMode		SetTextMode;
	funcClearScreen		ClearScreen;
	funcSetChar			SetChar;
	funcGetTextMetrics	GetTextMetrics;
}CONSOLE_LIBRARY;
typedef CONSOLE_LIBRARY* CONSOLE;

extern char* _fx_screen_buffer;

/*
typedef struct  _fx_console_library_internal
{
	funcSetTextMode SetTextMode;
	funcClearScreen ClearScreen;
	char* screen_buffer;
}INTERNAL_CONSOLE_LIBRARY;
typedef INTERNAL_CONSOLE_LIBRARY* __CONSOLE;
*/

#endif