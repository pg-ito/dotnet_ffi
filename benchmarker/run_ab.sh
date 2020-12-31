#!/bin/bash -xe

ab -c 4 -t 360000 -n 1080000  http://127.0.0.1/runbench_ffi.php

