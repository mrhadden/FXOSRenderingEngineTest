
#include "FXHAL.h"

PFXNODELIST _fx_hardware_queue = NULL;

char debug[256];

PFXHDWMSG _fx_copy_hw_message(PFXHDWMSG src)
{
	PFXHDWMSG c = (PFXHDWMSG)malloc(sizeof(FXHDWMSG));
	
	if(c)
	{
		memcpy(c,src,sizeof(FXHDWMSG));
	}
	
	return c;
}

int _fx_init_hardware()
{
	_hal_debug("_fx_init_hardware\n");
	
	
	_fx_hardware_queue = AllocListMax("__fx_hdw_queue",256);
	
	
	return 0;
}

int _fx_cpu_time()
{
	//_hal_debug("_fx_init_cpu\n");
	
	_hal_queue_lock();
	{
		PFXNODE n = ListRemoveEnd(_fx_hardware_queue);
		if(n && n->data)
		{
			PFXHDWMSG m = ((PFXHDWMSG)n->data);
			if(m->type!=3)
			{
				//_hal_debug_pointer("_fx_hardware_queue data: %p", n);
				_hal_debug_int("_fx_hardware_queue type: %d", ((PFXHDWMSG)n->data)->type);
				_hal_debug_int("_fx_hardware_queue size: %d", ListSize(_fx_hardware_queue));
				//DeallocNode(n);
			}
		}		
	}
	_hal_queue_unlock();	
	
	return 0;
}

int _fx_irq_signal(int type, PFXHDWMSG data)
{
	_hal_debug(debug);
	
	if(type == FX_IRQ_PROCESS)
	{
		_fx_cpu_time();
	}
	else
	{
		if(type == FX_IRQ_TIMER)
		{
			//sprintf(debug,"_fx_irq_signal FX_IRQ_TIMER: %d\n",type);
		}
		else if(type == FX_IRQ_MOUSE)
		{
			
		}
		else
			sprintf(debug,"_fx_irq_signal: %d\n",type);


		_hal_queue_lock();
		{
			PFXNODE n = ListAddStart(_fx_hardware_queue, _fx_copy_hw_message(data));
			//_hal_debug("_fx_init_hardware event added.\n");
		}
		_hal_queue_unlock();
	}
	
	return 0;
}