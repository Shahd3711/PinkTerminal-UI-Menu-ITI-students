#ifndef PIX_H
#define PIX_H

#include <string>
#include <utility>
#include <vector>
#include <termios.h>
using namespace std;
extern struct termios orig_termios;

struct Student {
    string name;
    int age;
    string track;
    string instructor;
};

void clearScreen();
void setColor(const std::string& colorName);
void gotoXY(int x, int y);
std::pair<int,int> getTerminalSize();
void printCenter(const std::string& text, const std::string& color="white");
int readKey();
void waitForRawEnter();
void flushInput();
void enableRawMode();
void disableRawMode();

void drawMenu(const std::string menu[], int menuSize, int selected);

Student getStudentInput();
void displayStudents(const std::vector<Student>& students);

#endif