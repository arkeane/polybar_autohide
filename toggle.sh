#!/bin/sh
line=$(head -n 1 ~/polybar_autohide/.togglefile)
if [ $line = 0 ]; then
    echo 1 > ~/polybar_autohide/.togglefile
else
    echo 0 > ~/polybar_autohide/.togglefile
fi