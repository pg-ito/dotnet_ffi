<?php
if(!defined('FIBONACCI_LOOPS')){
	define('FIBONACCI_LOOPS', 40);
}
$loops = isset($_GET['loops'])? intval($_GET['loops']) : FIBONACCI_LOOPS;
echo "--------- dotnet_ffi fibonacci bench START ---------$br\n";

$startTime = microtime(true);
for($i=0;$i<=$loops;++$i){
	$retInt64 = dotnet_ffi_ret_s64_arg_s64($i);
	echo "{$i}:{$retInt64},\t";
}
$endTime = microtime(true);
$elapsed = $endTime - $startTime;
// $resultFFI = $elapsed;
echo PHP_EOL."---------------------------------------------------------------".PHP_EOL;
echo "fibonacci sequence:\t{$loops}\telapsed[sec.]:\t{$elapsed}".PHP_EOL;
$peakMemory = number_format(memory_get_peak_usage(true));
echo "--------- peakMemory[Bytes]: {$peakMemory} ---------".PHP_EOL;
echo "--------- dotnet_ffi fibonacci bench END ---------".PHP_EOL;
return $elapsed;
