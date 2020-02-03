#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sstream>
#include<string>
#include<fstream>
#include<X11/Xlib.h>
#include<X11/Xutil.h>

// Shell scripts
#define windowlist "xdotool search --all --onlyvisible --desktop $(xprop -notype -root _NET_CURRENT_DESKTOP | cut -c 24-) \"\" 2>/dev/null | tr -d 'Defaulting to search window name, class, and classname' > .windowlist"
#define windowcount "wc -l .windowlist | tr -d ' .windowlist'"
#define show "xdo show -N Polybar"
#define hide "xdo hide -N Polybar"

// Variables
#define polybar_height 30

void togglefile(){
	// Inizialize toggle file
	std::fstream fout;
	fout.open(".togglefile", std::ios::out);
	fout << 0;
	fout.close();
}

void keybinding(int& k){
	// Read toggle file
	std::fstream fin;
	fin.open(".togglefile", std::ios::in);
	fin >> k;
	fin.close();
}

void GetStdoutFromCommand(std::string cmd, std::string &data) {
	// Read shell command and put in a string
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");
    stream = popen(cmd.c_str(), "r");
    if(stream){
    	while(!feof(stream))
    	if(fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    	pclose(stream);
    }
}

void getpointer(int &y){
	// Setup display and such
    char *display_name = getenv("DISPLAY");
    Display *display = XOpenDisplay(display_name);
    int screen = DefaultScreen(display);

    // Get the mouse cursor position
    int win_x, root_x, root_y = 0;
    unsigned int mask = 0;
    Window child_win, root_win;
    XQueryPointer(display, XRootWindow(display, screen), &child_win, &root_win, &root_x, &root_y, &win_x, &y, &mask);
}

void windowcounter(int &w){
	// Get active windows number as string
	system(windowlist);
	std::string result;
	GetStdoutFromCommand(windowcount, result);

	// Convert string to int
	std::istringstream iss (result);
	iss >> w;
}

int main(int argc, char* argv[]){
	// Inizialization
	togglefile();
	int k, w, y = 0;

	// Infinite Loop
	while(true){
		// Detect toggle
		keybinding(k);
		// Get y pointer
		getpointer(y);
		// Get windows number
		windowcounter(w);

		// Activation hierarchy
		// Toggle active = 1
		if(k == 1){
			system(show);
		}
		// Toggle not active = 0
		else{
			// Mouse pointer near the bar
			if(y <= polybar_height){
				system(show);
			}
			// Mouse pointer not near the bar
			else{
				// No active windows
				if(w == 0){
					system(show);
				}
				// 1 or more active windows
				else{
					system(hide);
				}
			}
		}
		// Delay
		sleep(1);
	}
return 0;
}
