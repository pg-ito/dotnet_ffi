#!/bin/bash -xe

g++ --shared -fPIC -o libcoreclrctl.so coreclr_ctlpp.cpp -ldl
