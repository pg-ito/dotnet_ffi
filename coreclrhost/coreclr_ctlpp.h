#ifndef CORECLR_CTLPP_H
#define CORECLR_CTLPP_H


#define DEBUG 0
#define DOTNET_FFI_DEBUGLOG(fmt, ...) do { if (DEBUG) fprintf(stderr, "DOTNET_FFI_DEBUG %s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); } while (0)
#define DOTNET_FFI_ERRLOG(fmt, ...) do { fprintf(stderr, "DOTNET_FFI_ERROR! %s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); } while (0)

#ifdef __cplusplus 
extern "C" { 
#endif 

int LoadClr(const char *argPath);
int InitClr();
long long invoke_ret_s64_arg_s64(int *hr, long long i);
double InvokeReturnDouble(int *hr, double d);
void InvokeReturnString(int *hr, const char *inStr, int inLen, char **retStr, int *retLen);
long long InvokeReturnInt64(int *hr, long long i, long long j);
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
