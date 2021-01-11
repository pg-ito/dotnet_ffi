#ifndef CORECLR_CTLPP_H
#define CORECLR_CTLPP_H


// #define DEBUG 0
#ifndef DEBUG
#define DEBUG 0
#endif

#define DOTNET_FFI_DEBUGLOG(fmt, ...) do { if (DEBUG){ fprintf(stderr, "DOTNET_FFI_DEBUG %s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__);} } while (0)
#define DOTNET_FFI_ERRLOG(fmt, ...) do { fprintf(stderr, "DOTNET_FFI_ERROR! %s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); } while (0)

#ifdef __cplusplus 
extern "C" { 
#endif 

int LoadClr(const char *argPath);
int InitClr();
void SetTargtClass(const char* project_name, const char* class_name );
long long invoke_ret_s64_arg_s64(int *hr, long long i, const char* method_name);
double InvokeReturnDouble(int *hr, double d);
void invoke_ret_str_arg_str(int *hr, const char *inStr, int inLen, char **retStr, int *retLen, const char* method_name);
void invoke_ret_str_arg_str_multi(int *hr, const char *inStr, int inLen, char **retStr, int *retLen, const char* method_name);
long long InvokeReturnInt64(int *hr, long long i, long long j);
int DestructVm();



#ifdef __cplusplus 
} //end extern "C" 
#endif 

#endif // include guard
