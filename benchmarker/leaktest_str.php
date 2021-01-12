<?php

require_once 'benchmerker_lib.php';


$methodName = 'ret_str_arg_str';
// $testStr = base64_encode('_1234567890-abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ._');
$testStr = 'H4sIAAAAAAAAA6tWKkktLklJLElUsoo21DHSMdYx0TGN1VHKK81VsrIEglouAB7nkjYkAAAA';

echo $className."::{$methodName}================".LINE_END_CHARS;
echo "testStr: ${testStr}".LINE_END_CHARS;
echo strtoupper( bin2hex(base64_decode($testStr)) ).LINE_END_CHARS;
$decoded = gzdecode(base64_decode($testStr));
var_dump($decoded);

for($i=0;$i<BENCH_LOOPS;++$i){
    echo 'loop: '.$i.LINE_END_CHARS;
    $retStr = $className::$methodName($testStr);
    var_dump($retStr);
    echo LINE_END_CHARS;
    usleep(100000);// wait 100ms 
}

