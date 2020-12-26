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
echo 'PHPVer. '.phpversion().PHP_EOL;
echo "--------- dotnet_ffi fibonacci bench START ---------$br\n";

$startTime = microtime(true);
// $loops = 40;
define('FIBONACCI_LOOPS', 40);


$resultPurePHP = require 'runbench_purephp.php';
var_dump($resultPurePHP);

$resultDotnetFFI = require 'runbench_ffi.php';
var_dump($resultDotnetFFI);


$ratio = round($resultPurePHP/$resultDotnetFFI, 2);
echo "========= {$ratio} times faster than pure php =========".PHP_EOL;


