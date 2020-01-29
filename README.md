# PolyBar_Autohide
C++ script to autohide PolyBar

# How to Install
1. Clone the git repo in your home `git clone https://github.com/arkeane/polybar_autohide.git ~/polybar_autohide`

2. Move to the script directory `cd ~/polybar_autohide`

3. Make adjustments to the script
     - You should adjust polybar_height definition to your actual height.
     - If you have more bars try to add a new condition for other bars height (I haven't tested this yet but it shoul work)
  
4. Compile the script `g++ polybar_autohide.cpp -o autohide`

5. Autorun the script
     - If you use i3wm add this `exec --no-startup-id ~/polybar_autohide/autohide`
     - If not just use your usual startup launch system.


If you want to support me paypal.me/LudovicoPestarino
