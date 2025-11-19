#include <iostream>
using namespace std;
#define el '\n'
#define BATGURL37 ios_base::sync_with_stdio(0); cin.tie(0);
struct ITI_Students 
{
    char name[50];
    int age;
    char track[50];
    char instructor[50];
};
int main()
 {
    int students_num;
    cout<<"Enter number of students please: ";
    cin>>students_num;
    ITI_Students students[100];
    cin.ignore();
    for(int i=0; i<students_num; i++)
    {
        cout<<"Student #"<<i+1<<el;
        cout<<"Student Name: ";
        cin.getline(students[i].name, 50);
        cout<<"Age: ";
        cin>>students[i].age;
        cin.ignore();
        cout<<"Track: ";
        cin.getline(students[i].track, 50);
        cout<<"Instructor: ";
        cin.getline(students[i].instructor, 50);
    }
    cout<<el;
    cout<<"=====^_^ ITI STUDENTS DATA ^_^=====";
    cout<<el;
    for(int i=0; i<students_num; i++)
    {
        cout<<"===Student # "<<i+1<<"==="<<el;
        cout<<"Student #"<<i+1<<el;
        cout<<"Student Name: "<<students[i].name<<el;
        cout<<"Age:         "<<students[i].age<<el;
        cout<<"Track:       "<<students[i].track<<el;
        cout<<"Instructor:  "<<students[i].instructor<<el;
    }
    return 0;
}
