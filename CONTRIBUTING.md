# CONTRIBUTING

## The project

If you have some new feature and you want to add it to the project, please make a pull request. Remember that polybar_autohide should stay as wm agnostic as possible. Try to keep the code as simple as possible and self explanatory. Please also make sure that the code is tested and works as expected. Stick to C code and if necessary bash scripts as a temporary solution while we work on a better solution.

## What is missing

Here are a few ideas for what is missing:

- A way to make both top and bottom bars hiding/showing within the same autohide process.
- Different resolutions multimonitor support (e.g. two monitors with different resolutions)
- Make the programm show the bar if it is the only window on the screen (depends on various window managers implementations)
- Hotkeys support (e.g. `ctrl+alt+h` to show/hide the bar)
- A better way to get the bar window id directly.
