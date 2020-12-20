#ifndef CORECLR_CTLPP_H
#define CORECLR_CTLPP_H

// #include "coreclrhost.h"
// #include <string.h>

#ifdef __cplusplus 
extern "C" { 
#endif 

int LoadClr(const char *argPath);
int InitClr();
double InvokeReturnDouble(int *hr, double d);
void InvokeReturnString(int *hr, const char *inStr, int inLen, char **retStr, int *retLen);
long InvokeReturnInt64(int *hr, long i, long j);
int DestructVm();

#ifdef DOTNET_FFI_LOG_ENBALE
#define DBGLOG( debuglog ) printf( "File:%s Line:%d Func:%s Log:%s\n", __FILE__, __LINE__, __func__, debuglog )
#else
#define DBGLOG( debuglog )
#endif

#ifdef __cplusplus 
} //end extern "C" 
#endif 

#endif // include guard
