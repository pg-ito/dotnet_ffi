#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "coreclrhost.h"
// #include "coreclr_ctl.h"



#define MANAGED_ASSEMBLY "invokee_test.dll"

#include <dirent.h>

#include <dlfcn.h>
#include <limits.h>
#define FS_SEPARATOR "/"
#define PATH_DELIMITER ":"
#define MAX_PATH PATH_MAX
#define CORECLR_FILE_NAME "libcoreclr.so"

typedef int (*report_callback_ptr)(int progress);
typedef double (*return_docuble_method_ptr)(const double d);

void BuildTpaList(const char* directory, const char* extension, std::string& tpaList);
int ReportProgressCallback(int progress);

// for property variables
void *coreClr = NULL;
coreclr_initialize_ptr initializeCoreClr = NULL;
coreclr_create_delegate_ptr createManagedDelegate = NULL;
coreclr_shutdown_ptr shutdownCoreClr = NULL;
char runtimePath[MAX_PATH];

int InitClr(const char* argPath);

int InitClr(const char* argPath){

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
    if (coreClr == NULL)
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

    if (initializeCoreClr == NULL)
    {
        printf("coreclr_initialize not found");
        return -1;
    }

    if (createManagedDelegate == NULL)
    {
        printf("coreclr_create_delegate not found");
        return -1;
    }

    if (shutdownCoreClr == NULL)
    {
        printf("coreclr_shutdown not found");
        return -1;
    }
    return 1;
}


int main(int argc, char* argv[])
{
    if(argc < 2){
        printf("need 1 runtime path argument\n");
        return 255;
    }
    InitClr(argv[1]);



    std::string tpaList;
    BuildTpaList(runtimePath, ".dll", tpaList);


    const char* propertyKeys[] = {
        "TRUSTED_PLATFORM_ASSEMBLIES"      // Trusted assemblies
    };

    const char* propertyValues[] = {
        tpaList.c_str()
    };



    // ========== coreclr start ==========

    void* hostHandle;
    unsigned int domainId;

    // This function both starts the .NET Core runtime and creates
    // the default (and only) AppDomain
    int hr = initializeCoreClr(
                    runtimePath,        // App base path
                    "SampleHost",       // AppDomain friendly name
                    sizeof(propertyKeys) / sizeof(char*),   // Property count
                    propertyKeys,       // Property names
                    propertyValues,     // Property values
                    &hostHandle,        // Host handle
                    &domainId);         // AppDomain ID

    if (hr >= 0)
    {
        printf("CoreCLR started\n");
    }
    else
    {
        printf("coreclr_initialize failed - status: 0x%08x\n", hr);
        return -1;
    }


    // ========== invoke managed code ==========
    return_docuble_method_ptr managedDelegate;  
    // todo load signature from ini
    hr = createManagedDelegate(
            hostHandle,
            domainId,
            "invokee_test, Version=1.0.0.0",
            "invokee_test.InvokeeTest",
            "ReturnDouble",
            (void**)&managedDelegate);
    // </Snippet5>

    if (hr >= 0)
    {
        printf("Managed delegate created\n");
    }
    else
    {
        printf("coreclr_create_delegate failed - status: 0x%08x\n", hr);
        return -1;
    }


    double csArg = 5;
    double ret = managedDelegate(csArg);
    printf("input: %lf , Managed code returned: %lf\n",csArg, ret);




    // ========== Destruct VM ==============
    hr = shutdownCoreClr(hostHandle, domainId);

    if (hr >= 0)
    {
        printf("CoreCLR successfully shutdown\n");
    }
    else
    {
        printf("coreclr_shutdown failed - status: 0x%08x\n", hr);
    }

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