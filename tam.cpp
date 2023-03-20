#include <ctime>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Myclass{
    static int count;
    public:
    Myclass(){
        count += 1;
    }
    int id;
    int getCount(){return count;};
};
int Myclass::count{0};

int main(){
    string day, month, year;
    string s = "01234567";
    day = s.substr(0,2);
    month = s.substr(3,2);
    year = s.substr(6,4);
    char a[20] = "hello";
    cout << a  << endl;
    
    memmove(a, a+1, strlen(a));
    //cout << "wh/ole " << x.str() << endl;/
    cout << a  << endl;
    
}