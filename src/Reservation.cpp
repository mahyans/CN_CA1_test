#include "../include/Reservation.hpp"

Reservation::Reservation(User _user, int _numOfBeds, string _reserveDate, string _checkoutDate){
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

int Reservation::getStartInterval(){
    stringstream ss(checkoutDate);
    string year, month, day;
    getline(ss, day, '-');
    getline(ss, month, '-');
    getline(ss, year);
    //cout << year << month << day << endl;
    int a = stoi(year+month+day);
    return a;
}

string Reservation::toStringAdmin(){
    return " [User] " + user.toString() + toString();
}

string Reservation::toString(){
    return " [beds] " + to_string(numOfBeds) +  
            " [reserve date] " + reserveDate + " [checkout date] " + checkoutDate + "\n";
}