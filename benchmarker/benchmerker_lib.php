<?php
$br = (php_sapi_name() == "cli")? PHP_EOL:'<br />'.PHP_EOL;
define('LINE_END_CHARS', $br);

if (php_sapi_name() == 'cli') {
	$loops = isset( $argv[1] )? intval($argv[1]):5;
}else{
	$loops = isset($_GET['loops'])? intval($_GET['loops']):5;
}
define('BENCH_LOOPS', $loops);


$className = 'DotnetFFI';
if(!class_exists($className)){
	echo $className.' Class is not exists'.$br.PHP_EOL;
	exit(255);
}
echo $className.' Class found'.$br.PHP_EOL;


define('START_FROM', date('Ymd_His'));
echo 'start at '.START_FROM.' peak memoery usage[Bytes]: '.number_format(memory_get_peak_usage(true)).LINE_END_CHARS;


function shutdownCallback(){
    echo "start from: ".START_FROM.", end at ".date('Ymd_His').' peak memoery usage[Bytes]: '.number_format(memory_get_peak_usage(true)).LINE_END_CHARS;
    exit;
}
register_shutdown_function ('shutdownCallback');
function signalHandler(int $signo , mixed $siginfo){
    var_dump($siginfo);
    echo 'Signal Received. signo: '.$signo.LINE_END_CHARS;
    shutdownCallback();
    exit;
}

// pcntl_signal(SIGINT, 'signalHandler', true);// for CTR+C. but not working?
