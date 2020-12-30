#!/bin/bash -xe

ab -c 3 -t 36000 -n 108000  http://127.0.0.1/runbench_ffi.php

