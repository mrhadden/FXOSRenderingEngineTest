
#include "FXHAL.h"
#include "FXWindow.h"
#include "pgm.h"

short interruptEnabled = 0;
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

int _fx_init_hardware(short enableInterrupts)
{
	_hal_debug("_fx_init_hardware enter\n");
	
	interruptEnabled = enableInterrupts;
	_fx_hardware_queue = AllocListMax("__fx_hdw_queue",256);
	
	_hal_debug("_fx_init_hardware exit\n");
	return 0;
}

int _fx_enable_interrupts(short enableInterrupts)
{
	interruptEnabled = enableInterrupts;
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
					{
						int xPos = GET_X_LPARAM(m->l_data1); 
						int yPos = GET_Y_LPARAM(m->l_data1); 	
						
						if(OnClick(xPos,yPos))
						{
							RedrawScreenV3(_hal_driver_table[FX_DRV_VIDEO],FALSE);
						}
						
						/*
						if(pguiEnv->state->isNonClient)
						{
							//if(PointInRect((PGFXRECT)pguiEnv->state->focusCurrent->nonclientList->head->data,xPos,yPos ))
							
							if(PointInListEx(pguiEnv->state->focusCurrent->nonclientList,xPos,yPos, NULL))
							{
								OutputDebugStringA("OnClick NON-CLIENT CLOSE");

								if(OnCtlClick(xPos,yPos))
								{
									RedrawScreenV3(_hal_driver_table[FX_DRV_VIDEO],FALSE);
								}
								return FALSE;
							}
						}
						*/
					}
					else
						_hal_debug("L MOUSE UP\n");
				}
				break;
			case FX_IRQ_MOUSE_R:
				{
					int xPos = GET_X_LPARAM(m->l_data1); 
					int yPos = GET_Y_LPARAM(m->l_data1); 					
					
					if(m->w_data2 == 1)
					{
						_hal_debug("R MOUSE DOWN\n");
						AddRect("Workbench", xPos, yPos, 400, 200, (void*)controlProc);
						RedrawScreenV3(_hal_driver_table[FX_DRV_VIDEO],TRUE);
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
	if(!interruptEnabled)
	{
		_hal_debug("_fx_irq_signal::interruptEnabled:Interrupts Disabled");
		return !interruptEnabled;
	}
	
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
	
	return !interruptEnabled;
}