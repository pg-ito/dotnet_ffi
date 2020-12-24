dotnet_ffi
===============

Invoke dotnet core class from php.


install
-------------

* clone
`git@github.com:pg-ito/dotnet_ffi.git && cd dotnet_ffi`

* build  
`./br.sh`

* install  
`sudo make install`

config
-------------

modify dotnet_ffi.ini
```
dotnet_ffi.libcoreclr_file_path=/PATH/TO/PUBLISHED_DOTNET_PROJECT/libcoreclr.so
dotnet_ffi.target_project_name="DOTNET_PROJECT_NAME, Version=1.0.0.0"
dotnet_ffi.target_class_name="INVOKE_TARGET_NAMESPACE.INVOKE_TARGET_CLASS"
dotnet_ffi.target_method_invoke_ret_str_arg_str="return_str_arg_str"
dotnet_ffi.target_method_invoke_ret_s64_arg_s64="return_s64_arg_s64"
dotnet_ffi.target_method_invoke_ret_dbl_arg_dbl="return_double_arg_double"
```


run
-------------

`./run.sh runbench.php`



