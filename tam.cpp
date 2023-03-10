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
    
    
    time_t tt = time(0);
    tm *ltm = localtime(&tt);

    char* t = ctime(&tt);
    cout << ltm->tm_mday << "-" << ltm->tm_mon << "-" << ltm->tm_year + 1900 << endl;

    string date = "27-03-2023";
    stringstream ss(date);
    string year, month, day;
    getline(ss, day, '-');
    getline(ss, month, '-');
    getline(ss, year);
    cout << year << month << day << endl;
    int a = stoi(year+month+day);
    cout << a;
}