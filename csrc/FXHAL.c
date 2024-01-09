
#include "FXHAL.h"
#include <windows.h>

PFXNODELIST _fx_hardware_queue = NULL;

char debug[256];

int _fx_init_hardware()
{
	OutputDebugStringA("_fx_init_hardware\n");
	
	
	_fx_hardware_queue = AllocListMax("__fx_hdw_queue",256);
	
	
	return 0;
}

int _fx_irq_signal(int type, PFXHDWMSG data)
{
	if(type == FX_IRQ_TIMER)
		sprintf(debug,"_fx_irq_signal FX_IRQ_TIMER: %d\n",type);
	else if(type == FX_IRQ_PROCESS)
		sprintf(debug,"_fx_irq_signal FX_IRQ_PROCESS: %d\n",type);
	else
		sprintf(debug,"_fx_irq_signal: %d\n",type);
	
	OutputDebugStringA(debug);
	
	_hal_queue_lock();
	{
		PFXNODE n = ListAddStart(_fx_hardware_queue, data);
		OutputDebugStringA("_fx_init_hardware event added.\n");
	}	
	_hal_queue_unlock();
	
	
	return 0;
}