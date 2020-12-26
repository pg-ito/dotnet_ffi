<?php

$br = (php_sapi_name() == "cli")? "":"<br>";


if(!extension_loaded('dotnet_ffi')) {
	dl('dotnet_ffi.' . PHP_SHLIB_SUFFIX);
}

$module = 'dotnet_ffi';

$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";

if (!extension_loaded($module)) {
	echo "ERROR! {$module} is not loaded!{$br}";
	exit(255);
} 


error_reporting(E_ALL);


$retDouble = dotnet_ffi_ret_double_double(16);
echo '$retDouble ================'.$br.PHP_EOL;
var_dump($retDouble);
echo "$br\n";

$retDouble = dotnet_ffi_ret_double_double(3);
echo '$retDouble ================'.$br.PHP_EOL;
var_dump($retDouble);
echo "$br\n";

$retInt = dotnet_ffi_ret_long_long_long(9801, 68030);
echo '$retInt ================'.$br.PHP_EOL;
var_dump($retInt);
echo "$br\n";

$retInt = dotnet_ffi_ret_long_long_long(-34, -2);
echo '$retInt ================'.$br.PHP_EOL;
var_dump($retInt);
echo "$br\n";


$retString = dotnet_ffi_ret_string_string('1234567890-abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ.');
echo '$retString ================'.$br.PHP_EOL;
var_dump($retString);
echo "$br\n";

$retString = dotnet_ffi_ret_string_string('1234567890-abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ.');
echo '$retString ================'.$br.PHP_EOL;
var_dump($retString);
echo "$br\n";


$retString = dotnet_ffi_ret_string_string('hello world.');
echo '$retString ================'.$br.PHP_EOL;
var_dump($retString);
echo "$br\n";

echo "--------- END ---------$br\n";
