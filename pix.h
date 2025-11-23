#ifndef PIX_H
#define PIX_H
#include <string>
#include <utility>
#include <termios.h>
#include <cstdio>
extern struct termios orig_termios;
#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define MAX_TRACK_LENGTH 50
#define MAX_INSTRUCTOR_LENGTH 50
using namespace std;
struct Student
{
char name[MAX_NAME_LENGTH];
int age;
char track[MAX_TRACK_LENGTH];
char instructor[MAX_INSTRUCTOR_LENGTH];
};
void clearScreen();
void setColor(const string& colorName);
void gotoXY(int x, int y);
pair<int,int> getTerminalSize();
void printCenter(const char* text, const std::string& color="white");
int readKey();
void waitForRawEnter();
void flushInput();
void enableRawMode();
void disableRawMode();
void drawMenu(const string menu[], int menuSize, int selected);
bool isValidName(const char* name);
Student getStudentInput();
void displayStudents(const Student students[], int count);
#endif
