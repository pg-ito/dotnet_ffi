<?php

$br = (php_sapi_name() == "cli")? PHP_EOL:'<br />'.PHP_EOL;
define('LINE_END_CHARS', $br);

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
echo 'PHPVer. '.phpversion()."$br\n";

$startTime = microtime(true);
echo "$br\n";

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

$methodName = 'ret_str_arg_str';
$retString = $className::$methodName('1234567890-abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ.');
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

invoke_str_loops(111);

echo "--------- END ---------$br\n";
echo (microtime(true) - $startTime)." [sec.]$br\n";


function invoke_str_loops(int $loops){
	$loops = ($loops<1)?1:$loops;
	$className = 'DotnetFFI';
	$methodName = 'ret_str_arg_str';
	for($i=0;$i<$loops;++$i){
		$randomStr = str_repeat(' 1234567890-abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ._'.bin2hex( random_bytes(random_int(1, 35)) ), random_int(1, 14) );
		$retString = $className::$methodName($randomStr);
		echo $className."::{$methodName}() ================".LINE_END_CHARS;
		var_dump($randomStr);
		var_dump($retString);
		echo LINE_END_CHARS;
	}
}