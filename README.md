# PolyBar_Autohide

Polybar autohide is a programs that implements autohide features for polybar and other status bars.
polybar_autohide is wm agnostic and bar agnostic, it should work with any wm and bar.

## How to Install

1. Clone the git repo in your home:

     ```[bash]
     git clone https://github.com/arkeane/polybar_autohide.git ~/polybar_autohide
     ```

     - Install dependencies: `polybar`(or other bars), `xdotool`, `xdo` and `xprop`

2. Move to the script directory `cd ~/polybar_autohide`

3. Make adjustments to the script directly from the source code `autohide.h`.

     - To find the WM_CLASS of your bar you can use the `getwmclass.sh` script.

          ```[bash]
          ./getwmclass.sh
          ```

4. Compile the script  with `make`

5. Run the script with whatever kind of startup script you are using.

     ```[bash]
     ./autohide &
     ```

________________________________________________________________________________
[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=LZDKH4PL5Z3XN&source=url)
