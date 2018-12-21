#!/bin/bash

mv staccel_proj staccel_proj.old 1>/dev/null 2>&1
mkdir staccel_proj
cp -r src/drive/interconnects/interconnects.cpp staccel_proj
mkdir staccel_proj/kernels
mkdir staccel_proj/inc
cp inc/* staccel_proj/inc
find src -name "*cpp" | xargs -I {} cp {} staccel_proj/kernels
rm staccel_proj/kernels/interconnects.cpp
