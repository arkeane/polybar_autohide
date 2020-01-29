#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sstream>
#include<string>
using namespace std;

//shell scripts
#define windownumber "xdotool search --all --onlyvisible --desktop $(xprop -notype -root _NET_CURRENT_DESKTOP | cut -c 24-) \"\" 2>/dev/null | tr -d 'Defaulting to search window name, class, and classname'"
#define pointeryposition "xdotool getmouselocation --shell |grep Y= | tr -d 'Y='"
#define show "xdo show -N Polybar"
#define hide "xdo hide -N Polybar"
//variables
#define polybar_height 30

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
}

void windowpresence(int& w){
	string result;
	result = GetStdoutFromCommand(windownumber);
	//convert just the first string to int
	if(result == ""){
		w = 0;
	}
	else
	{
	int num;
	std::istringstream iss (result);
	iss >> num;
	w = num;
	}
}

int main(){
	int y = 0;
	int w = 0;
	while(true){
	// get y pointer
	getpointerY(y);	
	// detect window presence
	windowpresence(w);
	if(y <= polybar_height){
		system(show);
	}
	else{
		//check if windows are displayed
		if(w == 0){
			system(show);
		}
		else{
			system(hide);
		}
	}
	sleep(1);
	}
return 0;}