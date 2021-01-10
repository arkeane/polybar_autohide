#!/bin/sh
# DISABLED
TOGGLEFILE="$HOME/.cache/polybar-togglefile"
line=$(head -n 1 "$TOGGLEFILE")
if [ $line = 0 ]; then
    echo 1 > "$TOGGLEFILE"
else
    echo 0 > "$TOGGLEFILE"
fi
