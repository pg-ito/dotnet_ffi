--TEST--
Check for dotnet_ffi presence
--SKIPIF--
<?php if (!extension_loaded("dotnet_ffi")) print "skip"; ?>
--FILE--
<?php
echo "dotnet_ffi extension is available";
/*
	you can add regression tests for your extension here

  the output of your test code has to be equal to the
  text in the --EXPECT-- section below for the tests
  to pass, differences between the output and the
  expected text are interpreted as failure

	see php7/README.TESTING for further information on
  writing regression tests
*/
?>
--EXPECT--
dotnet_ffi extension is available
