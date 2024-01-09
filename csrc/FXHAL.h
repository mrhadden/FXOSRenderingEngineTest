#ifndef __FX_HAL
#define __FX_HAL

#include "FXLIST.h"

#define FX_IRQ_RESET 	(0) 
#define FX_IRQ_TIMER 	(1) 
#define FX_IRQ_MOUSE 	(2) 
#define FX_IRQ_KEYBOARD	(3) 
#define FX_IRQ_SERIAL	(4) 
#define FX_IRQ_FLOPPY	(5) 
#define FX_IRQ_VIDEO 	(7) 


int _fx_init_hardware();
int _fx_irq_signal(int type, void* data);





#endif


