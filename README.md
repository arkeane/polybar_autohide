# PolyBar_Autohide
C++ script to autohide PolyBar

# How to Install
1. Clone the git repo in your home `git clone https://github.com/arkeane/polybar_autohide.git ~/polybar_autohide`

2. Move to the script directory `cd ~/polybar_autohide`

3. Make adjustments to the script
     - You can adjust polybar_height definition to change sensibility.
     - You can also change paths but be carefull!!!
     - If you have more bars try to add a new condition for other bars height (I haven't tested this yet but it should work)
  
4. Compile the script `g++ polybar_autohide.cpp -o autohide`

5. Autorun the script
     - If you use i3wm add this `exec --no-startup-id ~/polybar_autohide/autohide`
     - If not just use your usual startup launch system.

# How to use Hotkeys
1. The program automatically create a file `~/.togglefile` that contains a value (0 or 1) read by the script.

2. To use the toggle you have to bind the script `~/polybar_autohide/toggle.sh` with wathever you want
     - Remember to run `chmod u+x ~/polybar_autohide/toggle.sh` to make it executable
     - Bind the script with your favourite binding system 


If you want to support me [PayPalMe](paypal.me/LudovicoPestarino)
