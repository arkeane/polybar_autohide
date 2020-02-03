#!bin/sh
cd ~/polybar_autohide
g++ polybar_autohide.cpp -o autohide -lX11
./autohide
