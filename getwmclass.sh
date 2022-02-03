#!/bin/sh

# store mouse location 
mx=$(xdotool getmouselocation | awk '{print $1}' | awk -F ':' '{print $2}')
my=$(xdotool getmouselocation | awk '{print $2}' | awk -F ':' '{print $2}')

# To get WM_CLASS of bottom bar change 0 0 to something like 0 1080
xdotool mousemove 0 0
windowid=$(xdotool getmouselocation | awk '{print $4}' | awk '{gsub(/\window:/,"");}1')
wmclass=$(xprop -id $windowid | awk '/WM_CLASS/{print $4}' | awk '{gsub(/"/,"");}1')

# print the WM_CLASS
echo $wmclass

# restore mouse location
xdotool mousemove $mx $my