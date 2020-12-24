dotnet_ffi
===============

Invoke dotnet core class from php.


install
-------------

* clone the source

  `git@github.com:pg-ito/dotnet_ffi.git && cd dotnet_ffi`


* build  

  `./br.sh`


* install  

  `sudo make install`


config
-------------

modify dotnet_ffi.ini file for your environment.  
```
dotnet_ffi.libcoreclr_file_path=/PATH/TO/PUBLISHED_DOTNET_PROJECT/libcoreclr.so
dotnet_ffi.target_project_name="DOTNET_PROJECT_NAME, Version=1.0.0.0"
dotnet_ffi.target_class_name="INVOKE_TARGET_NAMESPACE.INVOKE_TARGET_CLASS"
dotnet_ffi.target_method_invoke_ret_str_arg_str="return_str_arg_str"
dotnet_ffi.target_method_invoke_ret_s64_arg_s64="return_s64_arg_s64"
dotnet_ffi.target_method_invoke_ret_dbl_arg_dbl="return_double_arg_double"
```


test run
-------------

`./run.sh runbench.php`



usage in php
-------------

```
// invoke Int64 type method sample
// call invokee_test.InvokeeTest.return_s64_arg_s64(Int64 i) in the dotnet managed dll class static method
$returnInt64 = dotnet_ffi_ret_s64_arg_s64(10);
var_dump($returnInt64);// int(55) e.g. fibonacci sequence n=10


// invoke string type method sample
// call invokee_test.InvokeeTest.return_str_arg_str(string str) in the dotnet managed dll class static method
$returnString = dotnet_ffi_ret_string_string('1234567890-abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ.');
var_dump($returnString);// string(65) "1234567890-ABCDEFGHIJKLMNOPQRSTUVWXYZ,ABCDEFGHIJKLMNOPQRSTUVWXYZ." e.g. toUpper

// c.f. see dotnet_dll/invokee_test/InvokeeTest.cs
```

