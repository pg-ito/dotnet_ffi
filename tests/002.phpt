--TEST--
dotnet_ffi_test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('dotnet_ffi')) {
	echo 'skip';
}
?>
--FILE--
<?php
$ret = dotnet_ffi_test1();

var_dump($ret);
?>
--EXPECT--
The extension dotnet_ffi is loaded and working!
NULL
