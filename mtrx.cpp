#include<iostream>
#include<iomanip>
using namespace std;
#define el '\n'
int** createArr(int rows, int cols) 
{
    int** arr=new int*[rows];
    for(int i=0; i<rows; i++) 
        arr[i]=new int[cols];
    return arr;
}
void Input(int** arr, int rows, int cols) 
{
    cout<<"\n--- Enter arr Data ---\n";
    cout<<"Please enter "<<(rows*cols)<<" integer values:\n";
    for(int i=0; i<rows; i++) 
    {
        cout<<"Entering Row "<<i<<":\n";
        for(int j=0; j<cols; j++) 
        {
            cout<<"  Element ["<<i<<"]["<<j<<"]: ";
            cin>>*(*(arr+i)+j);
        }
    }
}
void print(int** arr, int rows, int cols) 
{
    cout<<"\n--- Shahoda's arr ---\n";
    cout<<"---------------------------\n";
    for(int i=0; i<rows; i++) 
    {
        for(int j=0; j<cols; j++) 
        {
            int x=*(*(arr+i)+j);
            cout<<setw(5)<<x;
        }
        cout<<el;
    }
    cout<<"---------------------------\n";
}
void del(int** arr, int rows) 
{
    for(int i=0; i<rows; i++)
        delete[] arr[i];
    delete[] arr;
}
int main()
{
    int rows, cols;
    cout<<"Enter the number of Rows: ";
    cin>>rows;
    cout<<"Enter the number of Columns: ";
    cin>>cols;
    int** userarr=createArr(rows, cols);
    Input(userarr, rows, cols);
    print(userarr, rows, cols);
    del(userarr, rows);
    return 0;
}
