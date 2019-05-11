#include <iostream>
#include <stdlib.h> 
#include <Windows.h>
#include <thread>
#include <ctime>   
#include <string>
        
#include "termcolor.hpp"  

#define VK_W 0x57
#define VK_S 0x53

using namespace std;

bool bNoAfk = false;
bool bFirstTime = true;

int delay;

time_t last_time;
string sLastTime;

void exitProgram() {

	while (true) {

		if (GetAsyncKeyState(VK_DELETE) & 1) exit(-1);

	}
	Sleep(10);
}

void antiAfk() {

	while (true) {

		if (GetAsyncKeyState(VK_INSERT)) bNoAfk = true;

		while (bNoAfk) {

			if (bFirstTime) {

				system("cls"); //This is used to clear the console.
				cout << termcolor::green << "STARTING IN 20 SECONDS";
				Sleep(10000);
				system("cls");
				cout << termcolor::yellow << "STARTING IN 10 SECONDS";
				Sleep(5000);
				system("cls");
				cout << termcolor::red << "STARTING IN 5 SECONDS";
				Sleep(5000);
				system("cls");
				cout << termcolor::cyan << "STARTED..." << endl << endl;
				bFirstTime = false;

			}

			keybd_event(VK_W, MapVirtualKey(VK_W, 0), KEYEVENTF_EXTENDEDKEY, 0); //Sends W key stroke.

			Sleep(100); 

			keybd_event(VK_W, MapVirtualKey(VK_W, 0), KEYEVENTF_KEYUP, 0); //Releases W.

			keybd_event(VK_S, MapVirtualKey(VK_S, 0), KEYEVENTF_EXTENDEDKEY, 0); //Sends S key stroke.

			Sleep(100);

			keybd_event(VK_S, MapVirtualKey(VK_S, 0), KEYEVENTF_KEYUP, 0); //Releases S.

			last_time = time(0); //Gets current date and time.

			tm* tm_LastTime = localtime(&last_time);
			cout << termcolor::cyan << "[" << tm_LastTime->tm_hour << ":" << tm_LastTime->tm_min << ":" << tm_LastTime->tm_sec << "]" << termcolor::green << " Updated" << endl;

			Sleep(delay); //Delay between updates.

			cout << termcolor::white << "------------" << endl;
		}
		Sleep(10);
	}

}

int main()
{

	thread t_antiAfk(antiAfk); //Creates a new thread for antiAfk void.
	thread t_exit(exitProgram);

	cout << "Set delay time between updates (s): ";
	cin >> delay;

	
	system("cls");
	cout << termcolor::cyan << "!!!PRESS" << termcolor::green << " F4 " << termcolor::cyan << "TO START!!!" << endl;
	cout << termcolor::yellow << "While running, you can press SUPR to exit." << endl;
	cout << termcolor::magenta << "Delay chosen = " << delay << " seconds";

	delay = delay * 1000; //Converts seconds to miliseconds (thats what Sleep function uses).

	if(t_antiAfk.joinable()) //If thread is joinable then it will start running.
		t_antiAfk.join();

	if (t_exit.joinable())
		t_exit.join();
	
	return 0;
}
