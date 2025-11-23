#include "pix.h"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <limits>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
struct termios orig_termios;
using namespace std;
void clearScreen()
{
	cout<<"\033[2J\033[1;1H";
}
int readKey()
{
	char c;
	if(read(STDIN_FILENO, &c, 1)!=1)return -1;
	if(c=='\033')
	{
		char seq[2];
		if(read(STDIN_FILENO, &seq[0], 1)!=1)return 27;
		if(read(STDIN_FILENO, &seq[1], 1)!=1)return 27;
		if (seq[0] == '[')
		{
			switch (seq[1])
			{
				case 'A': return 1001;
				case 'B': return 1002;
				case 'C': return 1003;
				case 'D': return 1004;
			}
		}
		return 27;
	}
	if(c==13)c='\n';
	return c;
}
void setColor(const string& colorName)
{
	if(colorName=="pink_bright")cout<<"\033[95m";
	else if(colorName=="pink_light")cout<<"\033[35m";
	else if(colorName=="white")cout<<"\033[97m";
}
void gotoXY(int x, int y)
{
	cout<<"\033["<<y<<";"<<x<<"H";
}
pair<int,int> getTerminalSize()
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return{w.ws_col, w.ws_row};
}
void printCenter(const char* text, const string& color)
{
	auto[cols, rows]=getTerminalSize();
	int x=cols/2-strlen(text)/2;
	int y=rows/2;
	gotoXY(x, y);
	setColor(color);
	cout<<text;
	setColor("white");
}
void waitForRawEnter()
{
	auto[cols, rows]=getTerminalSize();
	gotoXY(cols/2-15, rows/2+2);
	cout<<"Press Return/Enter to continue...";
	cout<<flush;
	bool exitLoop=0;
	while(!exitLoop)
	{
		int key=readKey();
		if(key=='\n'||key==27||key==127)
			exitLoop=1;
	}
}
void flushInput()
{
	char c;
	while (read(STDIN_FILENO, &c, 1) == 1 && c != -1);
}
void enableRawMode()
{
	tcgetattr(STDIN_FILENO, &orig_termios);
	struct termios raw=orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
void disableRawMode()
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
void drawMenu(const string menu[], int menuSize, int selected)
{
	auto[cols, rows]=getTerminalSize();
	int startY=rows/2-menuSize/2;
	for(int i=0; i<menuSize; i++)
	{
		gotoXY(cols/2-10, startY+i);
		if(i==selected)setColor("pink_bright");
		else setColor("pink_light");
		cout<<(i==selected?"> ":"  ")<<menu[i];
		setColor("white");
	}
	cout<<flush;
}
bool isValidName(const char* name)
{
	for(int i=0; i<strlen(name); i++)
	{
		if(!isalpha(name[i])&&name[i]!=' ')
			return false;
	}
	string s(name);
	s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
	if(s.empty()) return false;
	
	return true;
}
bool isValidInstructorName(const char* name)
{
	for(int i=0; i<strlen(name); i++)
	{
		if(isdigit(name[i]))
			return false;
	}
	string s(name);
	s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
	if(s.empty()) return false;
	
	return true;
}
Student getStudentInput() {
	disableRawMode();
	Student s;
	clearScreen();
	cout << "--- ✨ Enter New Student Data ✨ ---" << endl;
	while(1){
		cout << "Enter Student Name: ";
		cin.getline(s.name, MAX_NAME_LENGTH);
		if(strlen(s.name)>0&&isValidName(s.name))break;
		
		if(strlen(s.name)==0)
			cout<<"⚠️ Name cannot be empty!\n";
		else 
			cout<<"⚠️ Invalid Name: Must contain letters and not be spaces only.\n";
	}
	string ageStr;
	bool validAge=0;
	while (!validAge) {
		cout << "Enter Age: ";
		getline(cin, ageStr);
		if(ageStr.empty()){cout<<"⚠️ Age cannot be empty!\n";continue;}
		stringstream ss(ageStr);
		if (ss >> s.age) {
			if(s.age >= 20 && s.age <= 30) {
				validAge=1;
			} else {
				cout << "⚠️ Age must be between 20 and 30.\n";
			}
		}
		else cout << "Invalid age format.\n";
	}
	// التعديل هنا: التراك مسموح به أي شيء (حروف، أرقام، رموز) ما عدا أن يكون فارغاً أو مسافات فقط
	while(1){
		cout << "Enter Track Name: ";
		cin.getline(s.track, MAX_TRACK_LENGTH);
		
		if(strlen(s.track) == 0) {
			cout<<"⚠️ Track cannot be empty!\n";
			continue;
		}
		string temp_track(s.track);
		temp_track.erase(remove_if(temp_track.begin(), temp_track.end(), ::isspace), temp_track.end());
		
		if(temp_track.empty()) {
			cout<<"⚠️ Track name cannot be spaces only!\n";
			continue;
		}
		
		break;
	}
	// التعديل هنا: استخدام دالة isValidInstructorName (تمنع الأرقام وتسمح بالرموز الأخرى)
	while(1){
		cout << "Enter Instructor Name: ";
		cin.getline(s.instructor, MAX_INSTRUCTOR_LENGTH);
		
		if(strlen(s.instructor)>0&&isValidInstructorName(s.instructor))break;
		
		if(strlen(s.instructor)==0)
			cout<<"⚠️ Instructor cannot be empty!\n";
		else 
			cout<<"⚠️ Invalid Instructor Name: Cannot contain numbers or be spaces only.\n";
	}
	enableRawMode();
	return s;
}
void displayStudents(const Student students[], int count) {
	auto[cols, rows]=getTerminalSize();
	clearScreen();
	setColor("pink_bright");
	int lineY=2;
	gotoXY(cols/2-15, lineY++);
	cout<<"--- 👸 ITI Students List 👸 ---";
	lineY++;
	if(count == 0) {
		printCenter("No students added yet!", "pink_light");
	} else {
		gotoXY(5, lineY); cout << "Name";
		gotoXY(30, lineY); cout << "Age";
		gotoXY(40, lineY); cout << "Track";
		gotoXY(70, lineY++); cout << "Instructor";
		gotoXY(5, lineY++);
		for(int i=0; i<cols-10; i++) cout<<"-";
		setColor("pink_light");
		for(int i=0; i<count; i++)
		{
			gotoXY(5, lineY); cout << students[i].name;
			gotoXY(30, lineY); cout << students[i].age;
			gotoXY(40, lineY); cout << students[i].track;
			gotoXY(70, lineY++); cout << students[i].instructor;
		}
	}
	setColor("white");
}
