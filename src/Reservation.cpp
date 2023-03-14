#include "../include/Reservation.hpp"

Reservation::Reservation(User* _user, int _numOfBeds, string _reserveDate, string _checkoutDate){
    user = _user;
    numOfBeds = _numOfBeds;
    reserveDate = _reserveDate;
    checkoutDate = _checkoutDate;
}

int Reservation::getStartInterval(){
    stringstream ss(reserveDate);
    string year, month, day;
    getline(ss, day, '-');
    getline(ss, month, '-');
    getline(ss, year);
    //cout << year << month << day << endl;
    int a = stoi(year+month+day);
    return a;
}

int Reservation::getEndInterval(){
    stringstream s(checkoutDate);
    string year, month, day;
    getline(s, day, '-');
    getline(s, month, '-');
    getline(s, year);
    
    int a = stoi(year+month+day);
    /*cout <<"ch: " <<checkoutDate << "\n";
    cout <<"pars: "<< year <<", "<< month <<", "<<  day << endl;
    cout <<"ret: " << a << "\n";*/
    return a;
}

int Reservation::getInterval(int start){
    
    stringstream x;
    if(start == 1)x << reserveDate;
    else x << checkoutDate;
    string year, month, day;
    getline(x, day, '-');
    getline(x, month, '-');
    getline(x, year);
    cout << year << month << day << endl;
    int a = stoi(year+month+day);
    return a;
}

string Reservation::toStringAdmin(){
    return user->toString() + toString();
}

string Reservation::toString(){
    return " [number of beds] " + to_string(numOfBeds) +  
            " [reserve date] " + reserveDate + " [checkout date] " + checkoutDate + "\n";
}