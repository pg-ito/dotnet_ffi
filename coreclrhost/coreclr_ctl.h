#pragma once

#include "coreclrhost.h"



int coreclr_ctl_init(const char* runtime_path);
char* coreclr_ctl_invoke_string_ret_string(const char* arg, const ulong arg_len);
ulong coreclr_ctl_invoke_uint64_ret_uint64(const ulong arg);
void* hostHandle = null;
unsigned int domainId;
const char* CORECLR_FILE_NAME ="libcoreclr.so";
