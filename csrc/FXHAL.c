
#include "FXHAL.h"

PFXNODELIST _fx_hardware_queue = NULL;

char debug[256];
int _fx_last_event = 0;

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
	
	PFXNODE n = NULL;
	
	_hal_queue_lock();
	{
		n = ListRemoveEnd(_fx_hardware_queue);
	}
	_hal_queue_unlock();	

	if(n && n->data)
	{
		PFXHDWMSG m = ((PFXHDWMSG)n->data);
		if(m)
		{
			/*
			if(m->type!=3)
			{
				//_hal_debug_pointer("_fx_hardware_queue data: %p", n);
				_hal_debug_int("_fx_hardware_queue type: %d", m->type);
				_hal_debug_int("_fx_hardware_queue size: %d", ListSize(_fx_hardware_queue));
			}
			*/
			switch(m->type)
			{
			case FX_IRQ_MOUSE:
				{
					
				}
				break;
			case FX_IRQ_MOUSE_L:
				{
					if(m->w_data2 == 1)
						_hal_debug("L MOUSE DOWN\n");
					else
						_hal_debug("L MOUSE UP\n");
				}
				break;
			case FX_IRQ_MOUSE_R:
				{
					if(m->w_data2 == 1)
					{
						_hal_debug("R MOUSE DOWN\n");
						//AddRect("Workbench", xPos, yPos, 400, 200, (void*)clientProc);
						//RedrawScreen(hwnd, TRUE);
					}
					else
						_hal_debug("R MOUSE UP\n");
				}
				break;				
			}
			
			/*
			if(_fx_scheduler)
			{
				_fx_scheduler();
			}
			*/


			_fx_last_event = m->type;
		}
		DeallocNode(n);
	}	

	
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
		_hal_queue_lock();
		{
			PFXNODE n = ListAddStart(_fx_hardware_queue, _fx_copy_hw_message(data));
			data->type = FX_IRQ_RESET;
		}
		_hal_queue_unlock();
	}
	
	return 0;
}