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

//shell scripts
#define windownumber "xdotool search --all --onlyvisible --desktop $(xprop -notype -root _NET_CURRENT_DESKTOP | cut -c 24-) \"\" 2>/dev/null | tr -d 'Defaulting to search window name, class, and classname'"
#define pointeryposition "xdotool getmouselocation --shell |grep Y= | tr -d 'Y='"
#define show "xdo show -N Polybar"
#define hide "xdo hide -N Polybar"
#define TOGGLEFILE "/home/david/.cache/polybar-togglefile"

/*
void togglefile(){
	//inizialize toggle file
	fstream fout;
	fout.open(TOGGLEFILE, ios::out);
	fout << 0;
	fout.close();
}
*/

//read shell command and put in a string string
string GetStdoutFromCommand(string cmd) {
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");
    stream = popen(cmd.c_str(), "r");
    if (stream) {
    while (!feof(stream))
    if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
    }
return data;
}

void getpointerY(int& y){
	string result;
	result = GetStdoutFromCommand(pointeryposition);
	//convert the y position to int
	int num;
	std::istringstream iss (result);
	iss >> num;
	y = num;
    // std::cout << "y-position: " << y << std::endl;
}

void windowpresence(int& win){
	string result;
	result = GetStdoutFromCommand(windownumber);
	//convert just the first string to int
	if(result == ""){
		win = 0;
	}
	else
	{
	int num;
	std::istringstream iss (result);
	iss >> num;
	win = num;
	}
}

/*
void keybinding(int& k){
	fstream fin;
	fin.open(TOGGLEFILE, ios::in);
	fin >> k;
	fin.close();
}
*/

int main(){
	//inizialization
	// togglefile();
	int y = 0, w = 0, win = 0;

    /*
    while (true) {
        // check for any windows
        windowpresence(w);

        // once it shows up, hide it
        if (w != 0) {
            w = 0;
            system(hide);
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    */

	//Infinite loop
	while(true){
		// detect keybinding
		// keybinding(k);
		// get y pointer
		getpointerY(y);	
		// detect window presence
        /*
		if(k == 1){
			system(show);
		}
        */
		// else{

        // check for any windows
        windowpresence(win);

        // std::cout << "win: " << win << ", w: " << w << std::endl;

        // if no windows, then show polybar
        if (win == 0) {
            if (w == 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                windowpresence(win);

                // if there is still no window
                if (win == 0) {
                    w = 1;
                    system(show);
                }
            }
        } else if (w == 0) {
            // if there is a window and polybar is hidden
            // we want to unhide it if mouse is at the top
            if (y <= 5) {
                // have a slight delay so accidental mouse movements at the top don't trigger
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                getpointerY(y);
                
                // if mouse is still at top
                if (y <= 5) {
                    w = 1;
                    system(show);
                }
            }
        } else {
            // else, there is a window, and polybar is shown,
            // we want to hide it if mouse moves away
            if (y > 50 && w > 0) {
                w = 0;
                system(hide);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
    return 0;
}
