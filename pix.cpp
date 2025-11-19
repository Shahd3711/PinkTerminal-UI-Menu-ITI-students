#include "pix.h"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <limits> 
#include <sstream> 
struct termios orig_termios;
using namespace std;

void clearScreen() 
{
    cout<<"\033[2J\033[1;1H";
}
// ... (بقية الدوال: readKey, setColor, gotoXY, getTerminalSize, printCenter, waitForRawEnter, flushInput, enableRawMode, disableRawMode) ...
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
                case 'A': return 1001;//Up
                case 'B': return 1002;//Down
                case 'C': return 1003;//Right
                case 'D': return 1004;//Left
            }
        }
        return 27;//Esc
    }
    //Return/Enter
    if(c==13) 
        c='\n'; 
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
void printCenter(const string& text, const string& color) 
{
    auto[cols, rows]=getTerminalSize();
    int x=cols/2-text.size()/2;
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
        if(key=='\n'||key==27||key==127)//del, esc, enter
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
    //Raw Mode Settings
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

Student getStudentInput() {
    disableRawMode(); 
    Student s;
    clearScreen();
    cout << "--- ✨ Enter New Student Data ✨ ---" << endl;
    
    cout << "Enter Student Name: ";
    getline(cin, s.name);
    
    string ageStr;
    bool validAge = false;
    while (!validAge) {
        cout << "Enter Age: ";
        getline(cin, ageStr);
        stringstream ss(ageStr);
        if (ss >> s.age) {
            validAge = true;
        } else {
            cout << "Invalid age format. Please enter a number." << endl;
        }
    }
    
    cout << "Enter Track Name: ";
    getline(cin, s.track);
    
    cout << "Enter Instructor Name: ";
    getline(cin, s.instructor);
    
    enableRawMode();
    return s;
}

void displayStudents(const vector<Student>& students) {
    auto[cols, rows]=getTerminalSize();
    clearScreen();
    setColor("pink_bright");
    int lineY=2;
    gotoXY(cols/2-15, lineY++);
    cout<<"--- 👸 ITI Students List 👸 ---";
    lineY++;
    
    if(students.empty()) {
        printCenter("No students added yet!", "pink_light");
    } else {
        gotoXY(5, lineY); 
        cout << "Name";
        gotoXY(30, lineY); 
        cout << "Age";
        gotoXY(40, lineY); 
        cout << "Track";
        gotoXY(70, lineY++); 
        cout << "Instructor";
        
        gotoXY(5, lineY++); 
        for(int i=0; i<cols-10; i++) cout<<"-";
        
        setColor("pink_light");
        for(const auto& s : students) {
            gotoXY(5, lineY); 
            cout << s.name;
            gotoXY(30, lineY); 
            cout << s.age;
            gotoXY(40, lineY); 
            cout << s.track;
            gotoXY(70, lineY++); 
            cout << s.instructor;
        }
    }
    setColor("white");
}