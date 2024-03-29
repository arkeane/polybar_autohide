#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xdo.h>
#include <string.h>

// CONFIG OPTIONS

// The Window Class of your status bar 
// WM_CLASS(STRING)
#define BAR_WM_CLASS "Bar"

// change top bar or bottom?
#define USE_TOP_BAR 1
#define USE_BOTTOM_BAR 0

// the margin at the top that will trigger polybar showing in Pixels
#define MARGIN_TOP 50
#define MARGIN_BOTTOM 1080

// the margin that will hide polybar if mouse is moved away in Pixels
#define MARGIN_HIDE_TOP 30
#define MARGIN_HIDE_BOTTOM 1080

// delay for each loop in milliseconds,
// set lower for more responsiveness, or
// higher for less resource usage
#define LOOP_DELAY 500

// delay for cursor and window positions in milliseconds,
// cursor must be kept for this time at the top,
// or window must be hidden for this time
// before polybar will show
#define CURSOR_WINDOW_DELAY 300

// check if the currently active window is fullscreen
// do not show the bar if it is
#define CHECK_FULLSCREEN 0
