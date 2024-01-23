#ifndef __FX_HAL
#define __FX_HAL

#include "FXLIST.h"
#include "FXDevices.h"

#define FX_IRQ_RESET 	(0) 
#define FX_IRQ_TIMER 	(1) 
#define FX_IRQ_PROCESS  (2) 
#define FX_IRQ_MOUSE 	(3) 
#define FX_IRQ_KEYBOARD	(4) 
#define FX_IRQ_SERIAL	(5) 
#define FX_IRQ_FLOPPY	(6) 
#define FX_IRQ_VIDEO 	(7)
 
#define FX_IRQ_MOUSE_L	(8) 
#define FX_IRQ_MOUSE_R 	(9) 

/*
#define LOBYTE(w)              ((BYTE)((DWORD_PTR)(w) & 0xFF))
#define HIBYTE(w)              ((BYTE)((DWORD_PTR)(w) >> 8))

#define LOWORD(l)              ((WORD)((DWORD_PTR)(l) & 0xFFFF))
#define HIWORD(l)              ((WORD)((DWORD_PTR)(l) >> 16))
*/

#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

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

void _hal_debug(const char* message);
void _hal_debug_int(const char* message,int val);
void _hal_debug_string(const char* message,const char* val);
void _hal_debug_pointer(const char* message,void* val);


void _hal_queue_lock();
void _hal_queue_unlock();

int _fx_init_hardware(short enableInterrupts);
int _fx_cpu_time();
int _fx_irq_signal(int type, PFXHDWMSG data);
int _fx_enable_interrupts(short enableInterrupts);

PFXDEVDRV _hal_driver_table[16];
PFXUIENV _fx_env;

#endif


