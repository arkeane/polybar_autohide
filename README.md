# PolyBar_Autohide
C++ script to autohide PolyBar

# How to Install
0. Clone the git repo in your home `git clone https://github.com/arkeane/polybar_autohide.git`

1. Make proper adjustments to the script
     - You should adjust polybar_height definition to your actual height.
     - If you have more bars try to add a new condition for other bars height.
  
2. Compile the script `g++ polybar_autohide.cpp -o autohide`

3. Make the script to run at startup
     - If you use i3wm add this `exec --no-startup-id ~/polybar_autohide/autohide`
