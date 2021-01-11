<?php

require_once 'benchmerker_lib.php';


$methodName = 'strtoupper';
$testStr = '_1234567890-abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ._';
echo "{$methodName}================".LINE_END_CHARS;
echo "testStr: ${testStr}".LINE_END_CHARS;
for($i=0;$i<BENCH_LOOPS;++$i){
    echo 'loop: '.$i.LINE_END_CHARS;
    $retInt = $methodName($testStr);
    var_dump($retInt);
    echo LINE_END_CHARS;
    usleep(100000);// wait 100ms 
}
