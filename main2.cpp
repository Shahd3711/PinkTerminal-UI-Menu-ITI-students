#include <iostream>
#include <string>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <cstring> 
#include "pix.h"
using namespace std;
int main() 
{
    enableRawMode(); 
    Student itiStudents[MAX_STUDENTS];
    int studentCount=0;
    const string menu[]= 
    {
        "💗 Add New Student Data",
        "💞 Display Students List",
        "🌸 Exit"
    };
    const int menuSize=sizeof(menu)/sizeof(menu[0]);
    int selected=0;
    clearScreen();
    drawMenu(menu, menuSize, selected);
    bool running=1; 
    while(running)
    {
        int key=readKey(); 
        if(key==1001||key==1004)
            selected=(selected-1+menuSize)%menuSize;
        else if(key==1002||key==1003)
            selected=(selected+1)%menuSize;
        else if(key=='\n')
        {
            clearScreen();
            switch(selected) 
            {
                case 0:
                {
                    bool add=1;
                    while(add) {
                        if (studentCount >= MAX_STUDENTS) {
                            printCenter("⚠️ Error: Maximum student capacity reached! ⚠️", "pink_bright");
                            add=0;
                            break;
                        }
                        Student newStudent=getStudentInput();
                        itiStudents[studentCount++]=newStudent;
                        clearScreen();
                        char successMsg[200]="Student '";
                        strcat(successMsg, newStudent.name);
                        strcat(successMsg, "' added successfully!");
                        printCenter(successMsg, "pink_bright");
                        disableRawMode();
                        cout<<"\n\nDo you want to add another student? (y/n): ";
                        char choiceStr[5];
                        cin.getline(choiceStr, 5); 
                        enableRawMode();
                        if(choiceStr[0]=='n'||choiceStr[0]=='N')
                            add=0;
                    }
                    clearScreen();
                    printCenter("✅ Update complete successfully! Returning to menu... ✅", "pink_bright");
                    waitForRawEnter(); 
                    break;
                }
                case 1:
                    displayStudents(itiStudents, studentCount);
                    waitForRawEnter(); 
                    break;
                case 2:
                    printCenter("🌸 Bye Bye Princess, We'll miss you! 🌸", "pink_bright");
                    waitForRawEnter();
                    running=0; 
                    break;
            }
            flushInput(); 
            if(running)
            {
                clearScreen();
                drawMenu(menu, menuSize, selected);
            }
        }
        else if(key==27||key==127||key=='x'||key=='X')
        { 
            clearScreen();
            printCenter("🌸 Exiting... Bye Bye! 🌸", "pink_bright");
            disableRawMode();
            running=0; 
        }
        if(running)
            drawMenu(menu, menuSize, selected);
    }
    disableRawMode();
    return 0;
}
