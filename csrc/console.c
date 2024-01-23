
#include "console.h"

char* _fx_screen_buffer = NULL;
int   _fx_screen_max_row = 0;
int   _fx_screen_max_col = 0;
int   _fx_screen_max_mod = 0;
int   _fx_screen_cur_col = 0;
int   _fx_screen_cur_row = 0;

int   _fx_screen_cursor_state = 0;

void _console_text_mode(int mode)
{
	OutputDebugStringA("_console_text_mode()");

	switch(mode)
	{
	case TEXTMODE_40X25:
		{	
			_fx_screen_buffer = (char*)malloc(40 * 25);
			_fx_screen_max_row = 25;
			_fx_screen_max_col = 40;
			_fx_screen_max_mod = TEXTMODE_40X25;
			OutputDebugStringA("_console_text_mode(TEXTMODE_40X25)");
		}
		break;
	case TEXTMODE_80X25:
		{
			_fx_screen_buffer = (char*)malloc(80 * 25);
			_fx_screen_max_row = 25;
			_fx_screen_max_col = 80;
			_fx_screen_max_mod = TEXTMODE_80X25;
			OutputDebugStringA("_console_text_mode(TEXTMODE_80X25)");
		}
		break;
	case TEXTMODE_80X43:
		{
			_fx_screen_buffer = (char*)malloc(80 * 43);
			_fx_screen_max_row = 43;
			_fx_screen_max_col = 80;
			_fx_screen_max_mod = TEXTMODE_80X43;
			OutputDebugStringA("_console_text_mode(TEXTMODE_80X43)");
		}
		break;
	case TEXTMODE_80X50:
		{
			_fx_screen_buffer = (char*)malloc(80 * 50);
			_fx_screen_max_row = 50;
			_fx_screen_max_col = 80;
			_fx_screen_max_mod = TEXTMODE_80X50;
			OutputDebugStringA("_console_text_mode(TEXTMODE_80X50)");
		}
		break;
	default:
		{
			_fx_screen_buffer = (char*)malloc(40 * 25);
			_fx_screen_max_row = 25;
			_fx_screen_max_col = 40;
			_fx_screen_max_mod = TEXTMODE_40X25;
			OutputDebugStringA("_console_text_mode(TEXTMODE_40X25)");
		}
		break;
	};

	memset(_fx_screen_buffer,' ',_fx_screen_max_col * _fx_screen_max_row);

}

void _console_set_char(int charCode,int row,int col)
{
	//OutputDebugStringA("_console_set_char()");

	if(_fx_screen_buffer)
		_fx_screen_buffer[(row * _fx_screen_max_col) + col] = (char)charCode;

}

void _console_flash_cursor()
{
	//OutputDebugStringA("_console_flash_cursor()");
	if(_fx_screen_buffer)
	{
		if(_fx_screen_cursor_state)
			_console_set_char(' ',_fx_screen_cur_row,_fx_screen_cur_col);
		else
			_console_set_char('_',_fx_screen_cur_row,_fx_screen_cur_col);
		
		_fx_screen_cursor_state = !_fx_screen_cursor_state;
	}

}


void _console_next_char(int charCode)
{
	//OutputDebugStringA("_console_next_char()");

	if(_fx_screen_buffer)
	{	
		if(charCode == VK_RETURN)
		{
			_console_set_char(' ',_fx_screen_cur_row,_fx_screen_cur_col);
			_fx_screen_cur_row++;
			_fx_screen_cur_col = 0;
			return;
		}
		else if(charCode == VK_BACK)
		{			
			_console_set_char(' ',_fx_screen_cur_row,_fx_screen_cur_col);
			_fx_screen_cur_col--;
			_console_set_char(' ',_fx_screen_cur_row,_fx_screen_cur_col);
			if(_fx_screen_cur_col < 0)
			{
				_fx_screen_cur_col = (_fx_screen_max_col - 1);
				_fx_screen_cur_row--;
			}
			return;
		}

		
		_console_set_char(charCode,_fx_screen_cur_row,_fx_screen_cur_col);
		
		_fx_screen_cur_col++;
		if(_fx_screen_cur_col >= _fx_screen_max_col)
		{
			_fx_screen_cur_col = 0;
			_fx_screen_cur_row++;
		}
		
		//_console_set_char(charCode,_fx_screen_cur_row,_fx_screen_cur_col);
	}

}


PFXTEXTMETRICS _console_get_metrics(PFXTEXTMETRICS pMet)
{
	//OutputDebugStringA("_console_get_buffer()");

	pMet->columns    = _fx_screen_max_col;
	pMet->rows       = _fx_screen_max_row;
	pMet->textBuffer = _fx_screen_buffer;
	pMet->mode       = _fx_screen_max_mod;

	pMet->cursor_row = _fx_screen_cur_row;
	pMet->cursor_col = _fx_screen_cur_col;

	return pMet;
}

void _console_clear_screen()
{
	OutputDebugStringA("_clear_screen()");

	char buffer[256];
	char cc[2];

	if(_fx_screen_buffer)
	{
		
		//memset(_fx_screen_buffer,' ',(_fx_screen_max_row * _fx_screen_max_col));
		/*
		for(int r = 0;r < _fx_screen_max_row;r++)
		{
			memset(buffer, 0, 256);
			buffer[0] = ' ';
			for(int c = 0;c < _fx_screen_max_col;c++)
			{
				cc[0] = _fx_screen_buffer[(r * _fx_screen_max_col) + c];
				cc[1] = 0;
				strcat(buffer, (const char*)cc);
				strcat(buffer, " ");
			}
			strcat(buffer, "\n");
			OutputDebugStringA(buffer);
		}
		*/
	}

}


FXHANDLE fxLoadLibrary(const char* name)
{
	if(stricmp(name,"console") == 0)
	{
		CONSOLE console = (CONSOLE)malloc(sizeof(CONSOLE_LIBRARY));
		if(console)
		{
			console->ClearScreen    = _console_clear_screen;
			console->SetTextMode    = _console_text_mode;
			console->SetChar        = _console_set_char;
			console->GetTextMetrics = _console_get_metrics;
			console->NextChar       = _console_next_char;
		}
		return console;
	}

	return NULL;
}

void fxUnloadLibrary(FXHANDLE library)
{
	
}

