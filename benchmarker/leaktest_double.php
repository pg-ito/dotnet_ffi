<?php

require_once 'benchmerker_lib.php';


$methodName = 'ret_dbl_arg_dbl';
echo "{$className}::{$methodName}() ================".LINE_END_CHARS;
for($i=0;$i<BENCH_LOOPS;++$i){
    echo 'loop: '.$i.LINE_END_CHARS;
    $retInt = $className::$methodName(7);
    var_dump($retInt);
    echo LINE_END_CHARS;
    usleep(100000);// wait 100ms 
}
