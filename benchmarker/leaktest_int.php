<?php

require_once 'benchmerker_lib.php';


$methodName = 'ret_s64_arg_s64';
echo $className.'::ret_s64_arg_s64() ================'.$br.PHP_EOL;
for($i=0;$i<BENCH_LOOPS;++$i){
    echo 'loop: '.$i.LINE_END_CHARS;
    $retInt = $className::$methodName(30);
    var_dump($retInt);
    echo LINE_END_CHARS;
    usleep(100000);// wait 100ms 
}
