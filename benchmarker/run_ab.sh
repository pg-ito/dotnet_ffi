#!/bin/bash -xe

ab -c 3 -t 36000 -n 108000  http://172.21.26.180/runbench_ffi.php

