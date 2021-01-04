dotnet_ffi
===============

Invoke dotnet core class from php.  
Approx. 7~10 time faster than pure php7.4.   

install
-------------

* clone the source

  ```
  cd /opt
  sudo https://github.com/pg-ito/dotnet_ffi.git && cd dotnet_ffi
  ```


* build and run

  `./br.sh`


* run only  

  `./run.sh`


* install  

  `./install.sh`


config
-------------

modify dotnet_ffi.ini file for your environment.    
`sudo vim $(php-config --ini-dir)/dotnet_ffi.ini`

```
dotnet_ffi.libcoreclr_file_path=/PATH/TO/PUBLISHED_DOTNET_PROJECT/libcoreclr.so
dotnet_ffi.target_project_name="DOTNET_PROJECT_NAME, Version=1.0.0.0"
dotnet_ffi.target_class_name="INVOKE_TARGET_NAMESPACE.INVOKE_TARGET_CLASS"
dotnet_ffi.target_method_invoke_ret_str_arg_str="return_str_arg_str"
dotnet_ffi.target_method_invoke_ret_s64_arg_s64="return_s64_arg_s64"
dotnet_ffi.target_method_invoke_ret_dbl_arg_dbl="return_double_arg_double"
```


usage in php
-------------


```
// invoke Int64 type method sample
// call invokee_test.InvokeeTest.return_s64_arg_s64(Int64 i) in the dotnet managed dll class static method
$returnInt64 = DotnetFFI::ret_s64_arg_s64(10);
var_dump($returnInt64);// int(55) e.g. fibonacci sequence n=10


// invoke string type method sample
// call invokee_test.InvokeeTest.return_str_arg_str(string str) in the dotnet managed dll class static method
$returnString = DotnetFFI::ret_str_arg_str('1234567890-abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ.');
var_dump($returnString);// string(65) "1234567890-ABCDEFGHIJKLMNOPQRSTUVWXYZ,ABCDEFGHIJKLMNOPQRSTUVWXYZ." e.g. toUpper

// c.f. see managed code sample dotnet_dll/invokee_test/InvokeeTest.cs
// ./ext_test.php
```



run fibonacci bench test 
-------------

### for command line

`./run.sh benchmarker/runbench.php`

result sample
```
PHPVer. 7.4.12
--------- dotnet_ffi fibonacci bench START ---------
Managed delegate created
0:0,    1:1,    2:1,    3:2,    4:3,    5:5,    6:8,    7:13,   8:21,   9:34,   10:55,  11:89,  12:144, 13:233, 14:377, 15:610, 16:987, 17:1597,        18:2584,        19:4181,        20:6765,        21:10946,       22:17711,       23:28657,       24:46368,       25:75025,       26:121393,      27:196418,      28:317811,      29:514229,     30:832040,       31:1346269,     32:2178309,     33:3524578,     34:5702887,     35:9227465,     36:14930352,    37:24157817,    38:39088169,    39:63245986,    40:102334155,
---------------------------------------------------------------
fibonacci sequence:     40      elapsed:        1.9112939834595
--------- dotnet_ffi fibonacci bench END ---------
--------- pure php fibonacci bench Start ---------
0:0,    1:1,    2:1,    3:2,    4:3,    5:5,    6:8,    7:13,   8:21,   9:34,   10:55,  11:89,  12:144, 13:233, 14:377, 15:610, 16:987, 17:1597,        18:2584,        19:4181,        20:6765,        21:10946,       22:17711,       23:28657,       24:46368,       25:75025,       26:121393,      27:196418,      28:317811,      29:514229,     30:832040,       31:1346269,     32:2178309,     33:3524578,     34:5702887,     35:9227465,     36:14930352,    37:24157817,    38:39088169,    39:63245986,    40:102334155,
---------------------------------------------------------------
fibonacci sequence:     40      elapsed:        20.0272397995
--------- pure php fibonacci bench END ---------
========= 10.48 times faster than pure php =========
```

### for httpd server

`benchmarker/run_ab.sh`

FAQ
-------------

### cannot CoreCLR with apache
change so/dll file's owner to httpd user  
e.g.  
```
chown -R apache: dotnet_dll/*
```
