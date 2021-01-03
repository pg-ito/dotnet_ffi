--TEST--
dotnet_ffi_test2() Basic test
--SKIPIF--
<?php
if (!extension_loaded('dotnet_ffi')) {
	echo 'skip';
}
?>
--FILE--
<?php
var_dump(dotnet_ffi_test2());
var_dump(dotnet_ffi_test2('PHP'));
?>
--EXPECT--
string(11) "Hello World"
string(9) "Hello PHP"
