#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sstream>
#include<string>
#include<fstream>
using namespace std;

//shell scripts
#define windownumber "xdotool search --all --onlyvisible --desktop $(xprop -notype -root _NET_CURRENT_DESKTOP | cut -c 24-) \"\" 2>/dev/null | tr -d 'Defaulting to search window name, class, and classname'"
#define pointeryposition "xdotool getmouselocation --shell |grep Y= | tr -d 'Y='"
#define show "xdo show -N Polybar"
#define hide "xdo hide -N Polybar"

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

void keybinding(int& k){
	fstream fin;
	fin.open(".togglefile", ios::in);
	fin >> k;
	fin.close();
}

int main(){
	//inizialization
	togglefile();
	int y, w, k = 0;
	//Infinite loop
	while(true){
		// detect keybinding
		keybinding(k);
		// get y pointer
		getpointerY(y);	
		// detect window presence
		windowpresence(w);
		if(k == 1){
			system(show);
		}
		else{
			if(y <= 5){
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
		}
		sleep(1);
	}
return 0;
}
