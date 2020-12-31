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

$className = 'DotnetFFI';
if(!class_exists($className)){
	echo $className.' Class is not exists'.$br.PHP_EOL;
	exit(255);
}
echo $className.' Class found'.$br.PHP_EOL;
$methodName = 'ret_s64_arg_s64';
$retInt = $className::$methodName(30);
echo $className.'::ret_s64_arg_s64() ================'.$br.PHP_EOL;
var_dump($retInt);
echo "$br\n";

$methodName = 'ret_str_arg_str';
$retString = $className::$methodName('hello world.');
echo $className."::{$methodName}() ================".$br.PHP_EOL;
var_dump($retString);
echo "$br\n";


$methodName = 'ret_s64_arg_s64_s64';
$retString = $className::$methodName(-100,1024*1024*1024*4);
echo $className."::{$methodName}() ================".$br.PHP_EOL;
var_dump($retString);
echo "$br\n";

$methodName = 'ret_dbl_arg_dbl';
$retDouble = $className::$methodName(5.0);
echo $className."::{$methodName}() ================".$br.PHP_EOL;
var_dump($retDouble);
echo "$br\n";
echo "--------- END ---------$br\n";
