#ifndef __FX_BASE
#define __FX_BASE


typedef void* FXHANDLE;

FXHANDLE fxLoadLibrary(const char* name);
void fxUnloadLibrary(FXHANDLE library);



#endif