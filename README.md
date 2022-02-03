# PolyBar_Autohide

PolyBar_Autohide is a programs that implements autohide features for polybar and other status bars.
PolyBar_Autohide is wm agnostic and bar agnostic, it should work with any wm and bar only on X11.

## How to Install

1. Clone the git repo in your home:

     ```[bash]
     git clone https://github.com/arkeane/polybar_autohide.git ~/polybar_autohide
     ```

     - Install dependencies: `libxdo-dev` from [xdotool](https://github.com/jordansissel/xdotool)

2. Make adjustments to the script directly from the source code `autohide.h`.

     - To find the WM_CLASS of your bar you can use the `getwmclass.sh` script.

          ```[bash]
          ./getwmclass.sh
          ```

3. Compile the script  with `make`

4. Run the script with whatever kind of startup script you are using.

     ```[bash]
     ./autohide &
     ```

________________________________________________________________________________
[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=LZDKH4PL5Z3XN&source=url)
