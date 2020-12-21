#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <random>

#include "coreclrhost.h"

#include "coreclr_ctlpp.h"


#define MANAGED_ASSEMBLY "invokee_test.dll"

#include <dirent.h>

#include <dlfcn.h>
#include <limits.h>
#define FS_SEPARATOR "/"
#define PATH_DELIMITER ":"
#define MAX_PATH PATH_MAX
#define CORECLR_FILE_NAME "libcoreclr.so"


typedef double (*double_return_docuble_method_ptr)(const double d);
typedef int64_t (*int64_int64_return_int64_method_ptr)(const int64_t i, const int64_t j);
typedef int64_t (*return_int64_arg_int64_method_ptr)(const int64_t i);
typedef char* (*string_return_string_method_ptr)(const char* str);

double_return_docuble_method_ptr managedDelegateReturnDouble{nullptr};
int64_int64_return_int64_method_ptr managedDelegateInvokeReturnInt64{nullptr};
return_int64_arg_int64_method_ptr managedDelegate_return_int64_arg_int64{nullptr};
string_return_string_method_ptr managedDelegateInvokeReturnString{nullptr};


void BuildTpaList(const char* directory, const char* extension, std::string& tpaList);
int ReportProgressCallback(int progress);

// for property variables
// for LoadClr
void *coreClr = nullptr;
coreclr_initialize_ptr initializeCoreClr = nullptr;
coreclr_create_delegate_ptr createManagedDelegate = nullptr;
coreclr_shutdown_ptr shutdownCoreClr = nullptr;
char runtimePath[MAX_PATH];
std::string tpaList{};

// for InitClr
void* hostHandle;
unsigned int domainId;

const char* propertyKeys[] = { "TRUSTED_PLATFORM_ASSEMBLIES" };



extern "C" int LoadClr(const char* argPath){

    DOTNET_FFI_DEBUGLOG("argPath %s\n", argPath);
    if(initializeCoreClr != NULL && createManagedDelegate != NULL && shutdownCoreClr != NULL){
        printf("Already Clr loaded");
        return 1;
    }
    realpath(argPath, runtimePath);
    printf("runtimePath: %s\n", runtimePath);
    char *last_slash = strrchr(runtimePath, FS_SEPARATOR[0]);
    if (last_slash != NULL){
        *last_slash = 0;
    }


    // Construct the CoreCLR path
    // For this sample, we know CoreCLR's path. For other hosts,
    // it may be necessary to probe for coreclr.dll/libcoreclr.so
    std::string coreClrPath(runtimePath);
    coreClrPath.append(FS_SEPARATOR);
    coreClrPath.append(CORECLR_FILE_NAME);

    // Construct the managed library path
    std::string managedLibraryPath(runtimePath);
    managedLibraryPath.append(FS_SEPARATOR);
    managedLibraryPath.append(MANAGED_ASSEMBLY);

    coreClr = dlopen(coreClrPath.c_str(), RTLD_NOW | RTLD_LOCAL);
    if (coreClr == nullptr)
    {
        printf("ERROR: Failed to load CoreCLR from %s\n", coreClrPath.c_str());
        return -1;
    }
    else
    {
        printf("Loaded CoreCLR from %s\n", coreClrPath.c_str());
    }

    initializeCoreClr = (coreclr_initialize_ptr)dlsym(coreClr, "coreclr_initialize");
    createManagedDelegate = (coreclr_create_delegate_ptr)dlsym(coreClr, "coreclr_create_delegate");
    shutdownCoreClr = (coreclr_shutdown_ptr)dlsym(coreClr, "coreclr_shutdown");

    if (initializeCoreClr == nullptr)
    {
        printf("coreclr_initialize not found");
        return -1;
    }

    if (createManagedDelegate == nullptr)
    {
        printf("coreclr_create_delegate not found");
        return -1;
    }

    if (shutdownCoreClr == nullptr)
    {
        printf("coreclr_shutdown not found");
        return -1;
    }



    BuildTpaList(runtimePath, ".dll", tpaList);

    // propertyValues = tpaList.c_str()};

    return 1;
}


/**
 * Initialize CoreClr 
 */
extern "C" int InitClr(){
    const char *propertyValues[] = {tpaList.c_str()};
    // @TODO load signature from ini
    int hr = initializeCoreClr(
                    runtimePath,        // App base path
                    "HostingOnPHP",       // AppDomain friendly name
                    sizeof(propertyKeys) / sizeof(char*),   // Property count
                    propertyKeys,       // Property names
                    propertyValues,     // Property values
                    &hostHandle,        // Host handle
                    &domainId);         // AppDomain ID

    if(hr < 0){
        printf("coreclr_initialize failed - status: 0x%08x\n", hr);
        return -1;
    }

    printf("CoreCLR started\n");
    return hr;
}

// public static Int64 ReturnInt64(Int64 i)
extern "C" int64_t invoke_ret_s64_arg_s64(int *hr, int64_t i){
    if(managedDelegate_return_int64_arg_int64 != nullptr){
        *hr = 1;
        printf("Managed delegate already created. Reuse it.\n");
        return managedDelegate_return_int64_arg_int64(i);
    }
    *hr = createManagedDelegate(
            hostHandle,
            domainId,
            "invokee_test, Version=1.0.0.0",
            "invokee_test.InvokeeTest",
            "return_int64_arg_int64",
            (void**)&managedDelegate_return_int64_arg_int64);
    if (hr < 0){
        printf("coreclr_create_delegate failed - status: 0x%08x\n", *hr);
        return 0.0f;        
    }
    *hr = 1;
    printf("Managed delegate created\n");
    return managedDelegate_return_int64_arg_int64(i);
}

// public static double ReturnDouble(double d)
extern "C" double InvokeReturnDouble(int *hr, double d){
    if(managedDelegateReturnDouble != nullptr){
        *hr = 1;
        printf("Managed delegate already created. Reuse it.\n");
        return managedDelegateReturnDouble(d);
    }
    *hr = createManagedDelegate(
            hostHandle,
            domainId,
            "invokee_test, Version=1.0.0.0",
            "invokee_test.InvokeeTest",
            "ReturnDouble",
            (void**)&managedDelegateReturnDouble);
    if (hr < 0){
        printf("coreclr_create_delegate failed - status: 0x%08x\n", *hr);
        return 0.0f;        
    }
    *hr = 1;
    printf("Managed delegate created\n");
    return managedDelegateReturnDouble(d);
}


// public static string ReturnString(string str)
extern "C" void InvokeReturnString(int *hr,  const char *inStr, int inLen, char **retStr, int *retLen){
    if(managedDelegateInvokeReturnString == nullptr){
        *hr = createManagedDelegate(
                hostHandle,
                domainId,
                "invokee_test, Version=1.0.0.0",
                "invokee_test.InvokeeTest",
                "ReturnString",
                (void**)&managedDelegateInvokeReturnString);
        if (*hr < 0){
            printf("coreclr_create_delegate failed - status: 0x%08x\n", *hr);
            return ;        
        }
    }else{
        printf("Managed delegate already created. Reuse it.\n");
    }

    printf("Managed delegate created\n");
    std::string ret = managedDelegateInvokeReturnString(inStr);
    *retLen = ret.length()+1;
    *retStr = (char *)malloc((size_t)*retLen);
    strcpy(*retStr, ret.c_str());
    printf("nativecode ret: %s, retStr: %s, retLen: %d\n", ret.c_str(), *retStr, *retLen);
    *hr = 1;
    return ;
}



// public static long InvokeReturnInt64(long i)
extern "C" int64_t InvokeReturnInt64(int *hr, int64_t i, int64_t j){
    if(managedDelegateInvokeReturnInt64 != nullptr){
        *hr = 1;
        printf("Managed delegate already created. Reuse it.\n");
        return managedDelegateInvokeReturnInt64(i, j);
    }
    *hr = createManagedDelegate(
            hostHandle,
            domainId,
            "invokee_test, Version=1.0.0.0",
            "invokee_test.InvokeeTest",
            "ReturnInt64",
            (void**)&managedDelegateInvokeReturnInt64);
    if (*hr < 0){
        printf("coreclr_create_delegate failed - status: 0x%08x\n", *hr);
        return 0.0f;        
    }
    *hr = 1;
    printf("Managed delegate created\n");
    return managedDelegateInvokeReturnInt64(i, j);
}



// ========== Destruct VM ==============

extern "C" int DestructVm(){
    int hr = shutdownCoreClr(hostHandle, domainId);

    if (hr < 0){
        printf("coreclr_shutdown failed - status: 0x%08x\n", hr);
        return hr;
    }
    printf("CoreCLR successfully shutdown status: 0x%08x\n", hr);
    return hr;
}

int main(int argc, char* argv[])
{
    if(argc < 2){
        printf("need 1 runtime path argument\n");
        return 255;
    }
    int LoadResult = LoadClr(argv[1]);
    if(LoadResult != 1){
        printf("LoadClr failed\n");
        return 255;
    }


    // ========== coreclr start ==========
   
    int hr = InitClr();
    if(hr < 0){
        printf("initResult failed\n");
        return 255;
    }

    // ========== invoke managed code ==========
    
    printf("\n================= InvokeReturnDouble test =================\n");
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::uniform_real_distribution<> dist(0.0, 40.0);
    double csArg = dist(engine);
    double ret = InvokeReturnDouble(&hr, csArg);
    printf("input: %lf , Managed code returned: %lf, hr: %d\n",csArg, ret, hr);

    csArg = dist(engine);
    ret = InvokeReturnDouble(&hr, csArg);
    printf("input: %lf , Managed code returned: %lf, hr: %d\n",csArg, ret, hr);


    printf("\n================= InvokeReturnInt64 test =================\n");

    std::uniform_int_distribution<> distInt(-40, 40);
    long long n = distInt(engine);
    long long m = distInt(engine);
    long long retInt64 = InvokeReturnInt64(&hr, n, m);
    printf("input: n=%lld m=%lld, Managed code returned: %lld, hr: %d\n", n, m, retInt64, hr);

    n = distInt(engine);
    m = distInt(engine);
    retInt64 = InvokeReturnInt64(&hr, n, m);
    printf("input: n=%lld m=%lld, Managed code returned: %lld, hr: %d\n", n, m, retInt64, hr);

    n = distInt(engine);

    printf("\n================= InvokeReturnString test =================\n");

    std::string inputStr{"1234567890-abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ."};
    int strLen = inputStr.length();
    char *retString = nullptr;
    int retLen = 0;
    InvokeReturnString(&hr, inputStr.c_str(), inputStr.length(), &retString, &strLen);
    printf("input: %s Managed code returned: %s, hr: %d\n", inputStr.c_str(), retString, hr);
    free(retString);

    std::string inputStr1{"1234567890-abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ."};
    int strLen1 = inputStr1.length();
    char *retString1 = nullptr;
    int retLen1 = 0;
    InvokeReturnString(&hr, inputStr1.c_str(), inputStr1.length(), &retString1, &strLen1);
    printf("input: %s Managed code returned: %s, hr: %d\n", inputStr1.c_str(), retString1, hr);
    free(retString1);

    std::string inputStr2{"hello world"};
    int strLen2 = inputStr2.length();
    char *retString2 = nullptr;
    int retLen2 = 0;
    InvokeReturnString(&hr, inputStr2.c_str(), inputStr2.length(), &retString2, &strLen2);
    printf("input: %s Managed code returned: %s, hr: %d\n", inputStr2.c_str(), retString2, hr);
    free(retString2);


    printf("\n================= invoke_ret_s64_arg_s64 test =================\n");

    for(long long i=0;i<13;++i){
        retInt64 = invoke_ret_s64_arg_s64(&hr, i);
        printf("input: n=%lld, Managed code returned: %lld, hr: %d\n", i, retInt64, hr);
    }

    std::uniform_int_distribution<> distPositiveInt(0, 50);
    n = distPositiveInt(engine);
    retInt64 = invoke_ret_s64_arg_s64(&hr, n);
    printf("input: n=%lld, Managed code returned: %lld, hr: %d\n", n, retInt64, hr);

    n = distPositiveInt(engine);
    retInt64 = invoke_ret_s64_arg_s64(&hr, n);
    printf("input: n=%lld, Managed code returned: %lld, hr: %d\n", n, retInt64, hr);


    hr = DestructVm();
    printf("shutdown with hr: %d\n", hr);
    return 0;
}


// =============== utilities ================

// POSIX directory search for .dll files
void BuildTpaList(const char* directory, const char* extension, std::string& tpaList)
{
    DIR* dir = opendir(directory);
    struct dirent* entry;
    int extLength = strlen(extension);

    while ((entry = readdir(dir)) != NULL)
    {
        // This simple sample doesn't check for symlinks
        std::string filename(entry->d_name);

        // Check if the file has the right extension
        int extPos = filename.length() - extLength;
        if (extPos <= 0 || filename.compare(extPos, extLength, extension) != 0)
        {
            continue;
        }

        // Append the assembly to the list
        tpaList.append(directory);
        tpaList.append(FS_SEPARATOR);
        tpaList.append(filename);
        tpaList.append(PATH_DELIMITER);

        // Note that the CLR does not guarantee which assembly will be loaded if an assembly
        // is in the TPA list multiple times (perhaps from different paths or perhaps with different NI/NI.dll
        // extensions. Therefore, a real host should probably add items to the list in priority order and only
        // add a file if it's not already present on the list.
        //
        // For this simple sample, though, and because we're only loading TPA assemblies from a single path,
        // and have no native images, we can ignore that complication.
    }
}

int ReportProgressCallback(int progress)
{
    // Just print the progress parameter to the console and return -progress
    printf("Received status from managed code: %d\n", progress);
    return -progress;
}