#!/bin/sh
line=$(head -n 1 ~/.togglefile)
if [ $line = 0 ]; then
    echo 1 > ~/.togglefile
else
    echo 0 > ~/.togglefile
fi