#ifndef __FX_HAL
#define __FX_HAL

#include "FXLIST.h"

#define FX_IRQ_RESET 	(0) 
#define FX_IRQ_TIMER 	(1) 
#define FX_IRQ_PROCESS  (2) 
#define FX_IRQ_MOUSE 	(3) 
#define FX_IRQ_KEYBOARD	(4) 
#define FX_IRQ_SERIAL	(5) 
#define FX_IRQ_FLOPPY	(6) 
#define FX_IRQ_VIDEO 	(7) 

typedef struct _fx_irq_message
{
    int   type;	
    int   irq;
	int   size;	
	int   w_data1;
	int   w_data2;
	long  l_data1;
	long  l_data2;
} FXHDWMSG;
typedef FXHDWMSG* PFXHDWMSG;


void _hal_queue_lock();
void _hal_queue_unlock();

int _fx_init_hardware();
int _fx_irq_signal(int type, PFXHDWMSG data);





#endif


