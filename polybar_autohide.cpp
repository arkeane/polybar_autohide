#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

// shell scripts
#define windownumber "xdotool search --all --onlyvisible --desktop $(xprop -notype -root _NET_CURRENT_DESKTOP | cut -c 24-) \"\" 2>/dev/null | tr -d 'Defaulting to search window name, class, and classname'"
#define pointeryposition "xdotool getmouselocation --shell |grep Y= | tr -d 'Y='"
#define show "xdo show -N Polybar"
#define hide "xdo hide -N Polybar"

#define DEBUG false

// read shell command and put in a string string
string getStdoutFromCommand(string cmd) {
    // make some buffers for storing stdout
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];

    // get stderr too
    cmd.append(" 2>&1");

    // run the command
    stream = popen(cmd.c_str(), "r");

    // append stdout/stderr to buffer
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) 
                data.append(buffer);
        pclose(stream);
    }

    return data;
}

void getPointerY(int& y){
	string result;
	result = getStdoutFromCommand(pointeryposition);

	// convert the y position to int
	int num;
	std::istringstream iss (result);
	iss >> num;
	y = num;
}

void windowPresence(int& windowPresent){
	string result;
	result = getStdoutFromCommand(windownumber);

	// convert just the first string to int
	if (result == "") {
		windowPresent = 0;
	} else {
        int num;
        std::istringstream iss (result);
        iss >> num;
        windowPresent = num;
	}
}

int main(){
	//initialization
	int y = 0, polybarShown = 0, windowPresent = 0;

	//Infinite loop
	while(true){
		// get y pointer
		getPointerY(y);	

        // check for any windows
        windowPresence(windowPresent);

        if (DEBUG) {
            std::cout << "pointer y position: " << y 
                      << ", windowPresent: " << windowPresent 
                      << ", polybarShown: " << polybarShown << std::endl;
        }

        // if no windows, then show polybar
        if (windowPresent == 0) {
            if (polybarShown == 0) {
                // put a slight delay so this doesn't show
                // when changing i3 workspaces
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                windowPresence(windowPresent);

                // if there is still no window
                if (windowPresent == 0) {
                    polybarShown = 1;
                    system(show);
                }
            }
        } else if (polybarShown == 0) {
            // if there is a window and polybar is hidden
            // we want to unhide it if mouse is at the top
            if (y <= 5) {
                // have a slight delay so accidental mouse movements don't trigger
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                getPointerY(y);
                
                // if mouse is still at top
                if (y <= 5) {
                    polybarShown = 1;
                    system(show);
                }
            }
        } else {
            // else, there is a window, and polybar is shown,
            // we want to hide it if mouse moves away
            if (y > 50 && polybarShown > 0) {
                polybarShown = 0;
                system(hide);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
    return 0;
}
