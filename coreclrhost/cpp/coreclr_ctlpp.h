#pragma once

#include "coreclrhost.h"


extern "C" int coreclr_ctl_init(const char* runtime_path);
extern "C" char* coreclr_ctl_invoke_string_ret_string(const char* arg, const uint64_t arg_len);
extern "C" uint64_t coreclr_ctl_invoke_uint64_ret_uint64(const uint64_t arg);

class coreclr_ctl {
public:
    static int init(const char* runtime_path);
    static char* invoke_string_ret_string(const char* arg, const uint64_t arg_len);
    static uint64_t invoke_uint64_ret_uint64(const uint64_t arg);

private:
    void* hostHandle{nullptr};
    unsigned int domainId;
    const string CORECLR_FILE_NAME{"libcoreclr.so"};
};
