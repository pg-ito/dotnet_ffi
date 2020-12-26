<?php
require_once 'fibonacci.php';
if(!defined('FIBONACCI_LOOPS')){
	define('FIBONACCI_LOOPS', 40);
}
$loops = FIBONACCI_LOOPS;
echo "--------- pure php fibonacci bench Start ---------".PHP_EOL;
$startTime = microtime(true);

for($i=0;$i<=$loops;++$i){
	$retInt64 = fibo_php($i);
	echo "{$i}:{$retInt64},\t";
}
$endTime = microtime(true);
$elapsed = $endTime - $startTime;
// $resultPHP = $elapsed;

echo PHP_EOL."---------------------------------------------------------------".PHP_EOL;
echo "fibonacci sequence:\t{$loops}\telapsed[sec.]:\t{$elapsed}".PHP_EOL;
$peakMemory = number_format(memory_get_peak_usage(true));
echo "--------- peakMemory[Bytes]: {$peakMemory} ---------".PHP_EOL;
echo "--------- pure php fibonacci bench END ---------".PHP_EOL;

return $elapsed;
