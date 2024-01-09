
#include "FXHAL.h"


int _fx_init_hardware()
{
	OutputDebugStringA("_fx_init_hardware\n");
	return 0;
}

int _fx_irq_signal(int type, void* data)
{
	OutputDebugStringA("_fx_irq_signal\n");
	return 0;
}