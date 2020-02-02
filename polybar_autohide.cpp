#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sstream>
#include<string>
#include<fstream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
using namespace std;

//shell scripts
#define windowlist "xdotool search --all --onlyvisible --desktop $(xprop -notype -root _NET_CURRENT_DESKTOP |\
                    cut -c 24-) \"\" 2>/dev/null |\
					tr -d 'Defaulting to search window name, class, and classname' > .windowlist"

#define windowcount "wc -l .windowlist |\
					 tr -d ' .windowlist'"

#define show "xdo show -N Polybar"
#define hide "xdo hide -N Polybar"

//variables
#define polybar_height 30

void togglefile(){
	//inizialize toggle file
	fstream fout;
	fout.open(".togglefile", ios::out);
	fout << 0;
	fout.close();
}

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

void getpointerY(int &y){
	// Setup display and such
    char *display_name = getenv("DISPLAY");
    Display *display = XOpenDisplay(display_name);
    int screen = DefaultScreen(display);

    // Get the mouse cursor position
    int win_x, root_x, root_y = 0;
    unsigned int mask = 0;
    Window child_win, root_win;
    XQueryPointer(display, XRootWindow(display, screen),
        &child_win, &root_win,
        &root_x, &root_y, &win_x, &y, &mask);
}

void windowcounter(unsigned int& w){
	system(windowlist);
	string result;
	result = GetStdoutFromCommand(windowcount);
	int num;
	std::istringstream iss (result);
	iss >> num;
	w = num;
}

void keybinding(int& k){
	fstream fin;
	fin.open(".togglefile", ios::in);
	fin >> k;
	fin.close();
}

int main(){
	//inizialization
	togglefile();
	int y, k = 0;
	unsigned int w = 0;
	//Infinite loop
	while(true){
		// detect keybinding
		keybinding(k);
		// get y pointer
		getpointerY(y);
		// detect window presence
		windowcounter(w);
		if(k == 1){
			system(show);
		}
		else{
			if(y <= polybar_height){
				system(show);
			}
			else{
				//check if windows are displayed
				if(w == 0){
					//cout << w << endl;
					system(show);
				}
				else{
					//cout << w << endl;
					system(hide);
				}
			}
		}
		sleep(1);
	}
return 0;
}