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




$retDouble = dotnet_ffi_ret_double_double(16.0);
echo '$retDouble ================'.$br;
var_dump($retDouble);

$retInt = dotnet_ffi_ret_long_long_long(9801, 68030);
echo '$retInt ================'.$br;
var_dump($retInt);

$retString = dotnet_ffi_ret_string_string('1234567890-abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ.');
echo '$retString ================'.$br;
var_dump($retString);


