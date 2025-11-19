#include <iostream>
using namespace std;
#define el '\n'
#define BATGURL37 ios_base::sync_with_stdio(0); cin.tie(0);
void swap1(int *a, int *b)
{
    *a=(*a)+(*b);
    *b=(*a)-(*b);
    *a=(*a)-(*b); 
}
void swap2(int *a, int *b)
{
    *a=(*a)^(*b);
    *b=(*a)^(*b);
    *a=(*a)^(*b);
}
void swap3(int *x, int *y) 
{
    *x=(*x)*(*y);
    *y=(*x)/(*y);
    *x=(*x)/(*y);
}
void swap4(int *x, int *y) 
{
    tie(*x, *y)=make_tuple(*y, *x);
}
void swap5(int *x, int *y)
{
    int temp=*x;
    *x=*y;
    *y=temp;
}
void swap6(int *x, int *y)
{
    swap(*x, *y);
}
int main() 
{
    BATGURL37;
    int a=3, b=7;
    cout<<"Before swap1: a="<<a<<", b="<<b<<el;
    swap1(&a, &b);
    cout<<"After swap1: a="<<a<<", b="<<b<<el;
    cout<<"Before swap2: a="<<a<<", b="<<b<<el;
    swap2(&a, &b);
    cout<<"After swap2: a="<<a<<", b="<<b<<el;
    cout<<"Before swap3: a="<<a<<", b="<<b<<el;
    swap3(&a, &b);
    cout<<"After swap3: a="<<a<<", b="<<b<<el;
    cout<<"Before swap4: a="<<a<<", b="<<b<<el;
    swap4(&a, &b);
    cout<<"After swap4: a="<<a<<", b="<<b<<el;
    cout<<"Before swap5: a="<<a<<", b="<<b<<el;
    swap5(&a, &b);
    cout<<"After swap5: a="<<a<<", b="<<b<<el;
    cout<<"Before swap6: a="<<a<<", b="<<b<<el;
    swap6(&a, &b);
    cout<<"After swap6: a="<<a<<", b="<<b<<el;
    return 0;
}
