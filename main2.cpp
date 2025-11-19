#include <iostream>
#include <vector> 
#include <string>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "pix.h"
using namespace std;

//1001: Up, 1002: Down, 1003: Right, 1004: Left
int main() 
{
    enableRawMode();
    
    vector<Student> itiStudents; 
    
    const string menu[]= 
    {
        "💗 Add New Student Data",
        "💞 Display Students List",
        "🌸 Exit"
    };
    const int menuSize = sizeof(menu) / sizeof(menu[0]);
    
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
        else if (key=='\n')
        {
            //Enter
            clearScreen();
            switch(selected) 
            {
                case 0:
                {
                    bool addAnother = true;
                    while(addAnother) {
                        Student newStudent = getStudentInput();
                        itiStudents.push_back(newStudent);
                        
                        clearScreen();
                        printCenter("Student '" + newStudent.name + "' added successfully!", "pink_bright");
                        
                        disableRawMode();
                        cout << "\n\nDo you want to add another student? (y/n): ";
                        
                        string choiceStr;
                        getline(cin, choiceStr);
                        enableRawMode();
                        
                        if (choiceStr.empty() || choiceStr[0] == 'n' || choiceStr[0] == 'N') {
                            addAnother = false;
                        }
                    }
                    clearScreen();
                    printCenter("✅ Update complete successfully! Returning to menu... ✅", "pink_bright");
                    waitForRawEnter(); 
                    break;
                }
                case 1:
                    displayStudents(itiStudents);
                    waitForRawEnter(); 
                    break;
                case 2:
                    printCenter("🌸 Bye Bye Princess, We'll miss you! 🌸", "pink_bright");
                    waitForRawEnter();
                    running=0; 
                    break;
            }
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