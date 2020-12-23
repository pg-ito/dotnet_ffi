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

echo "--------- dotnet_ffi fibonacci START ---------$br\n";

$startTime = microtime(true);
$loops = 40;
for($i=0;$i<=$loops;++$i){
	$retInt64 = dotnet_ffi_ret_s64_arg_s64($i);
	echo "{$i}\t{$retInt64}".PHP_EOL;
}
$endTime = microtime(true);
$elapsed = $endTime - $startTime;
echo "fibonacci sequence:\t{$loops}\telapsed:\t{$elapsed}".PHP_EOL;
echo "--------- dotnet_ffi fibonacci END ---------$br\n";


echo "--------- pure php fibonacci Start ---------$br\n";
$startTime = microtime(true);

for($i=0;$i<=$loops;++$i){
	$retInt64 = fibo_php($i);
	echo "{$i}\t{$retInt64}".PHP_EOL;
}
$endTime = microtime(true);
$elapsed = $endTime - $startTime;
echo "fibonacci sequence:\t{$loops}\telapsed:\t{$elapsed}".PHP_EOL;


echo "--------- pure php fibonacci END ---------$br\n";

function fibo_php($i){
	if($i<0){
		return 0;
	}
	if($i==0 || $i==1){
		return $i;
	}
	return fibo_php($i-2) + fibo_php($i-1);
}