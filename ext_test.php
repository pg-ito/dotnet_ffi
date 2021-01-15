<?php

$br = (php_sapi_name() == "cli")? PHP_EOL:'<br />'.PHP_EOL;
define('LINE_END_CHARS', $br);

if (php_sapi_name() == 'cli') {
	$loops = isset( $argv[1] )? intval($argv[1]):3;
}else{
	$loops = isset($_GET['loops'])? intval($_GET['loops']):3;
}


echo "loops: ${loops}".LINE_END_CHARS;

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

$methodName = 'ret_str_arg_str_multi';
$retString = $className::$methodName('H4sIAAAAAAAAA6tWKkktLklJLElUsoo21DHSMdYx0TGN1VHKK81VsrIEglouAB7nkjYkAAAA', 'return_str_arg_str_toupper');
echo $className."::{$methodName}() ================".$br.PHP_EOL;
var_dump($retString);
echo "$br\n";

$methodName = 'ret_str_arg_str_multi';
$retString = $className::$methodName('1234567890-abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ.', 'return_str_arg_str_toupper');
echo $className."::{$methodName}() ================".$br.PHP_EOL;
var_dump($retString);
echo "$br\n";

$bas64str = base64_encode("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A");
$methodName = 'ret_str_arg_str_multi';
$retString = $className::$methodName($bas64str, 'return_str_arg_str_base64_dec');
echo $className."::{$methodName}() ================".$br.PHP_EOL;
var_dump($retString);
echo "$br\n";


$bas64str = base64_encode(random_bytes(15));
$methodName = 'ret_str_arg_str';
$retString = $className::$methodName($bas64str);
echo $className."::{$methodName}() ================".$br.PHP_EOL;
var_dump($retString);
echo "$br\n";


$methodName = 'ret_str_arg_str_multi';
$retString = $className::$methodName('hello world multi.', 'return_str_arg_str_toupper');
echo $className."::{$methodName}() ================".$br.PHP_EOL;
var_dump($retString);
echo "$br\n";

$methodName = 'ret_str_arg_str_multi';
$retString = $className::$methodName('1234567890-abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ.multi', 'return_str_arg_str_toupper');
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

$methodName = 'ret_s64_arg_str';
$retInt = $className::$methodName('testJapaneseStringLength');
echo $className."::{$methodName}() ================".$br.PHP_EOL;
var_dump($retInt);
echo "$br\n";

$methodName = 'ret_s64_arg_str';
$retInt = $className::$methodName('日本語文字数カウントテスト');
echo $className."::{$methodName}() ================".$br.PHP_EOL;
var_dump($retInt);
echo "$br\n";


invoke_str_loops($loops);

echo "--------- END ---------$br\n";
echo (microtime(true) - $startTime)." [sec.]$br\n";


function invoke_str_loops(int $loops){
	$loops = ($loops<1)?1:$loops;
	$className = 'DotnetFFI';
	$methodName = 'ret_str_arg_str';
	for($i=0;$i<$loops;++$i){
		echo 'loop: '.$i.LINE_END_CHARS;
		$randomStr = str_repeat(' 1234567890-abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ._'.bin2hex( random_bytes(random_int(1, 35)) ), random_int(1, 14) );
		$retString = $className::$methodName( base64_encode($randomStr) );
		echo $className."::{$methodName}() ================".LINE_END_CHARS;
		var_dump($randomStr);
		var_dump($retString);
		echo LINE_END_CHARS;
	}
}