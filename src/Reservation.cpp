#include "../include/Reservation.hpp"

Reservation::Reservation(User* _user, int _numOfBeds, string _reserveDate, string _checkoutDate){
    user = _user;
    numOfBeds = _numOfBeds;
    reserveDate = _reserveDate;
    cout << reserveDate << endl;
    checkoutDate = _checkoutDate;
    cout << checkoutDate << endl;
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
    cout << "pars: ";
    cout << year <<", "<< month <<", "<<  day << endl;
    cout << "ret: " << a << "\n";*/
    return a;
}

int Reservation::getInterval(int start){
    
    stringstream x;
    string num = "";
    x.str("");

    string year, month, day;
   
    string s;
    if(start == 1)s = reserveDate;
    else s = checkoutDate; 
    //cout << "input "<<s << endl;
    day = s.substr(0,2);
    month = s.substr(3,2);
    year = s.substr(6,4);
    //cout << "wh/ole " << x.str() << endl;/
    //cout << "concatenate " << year << month << day << endl;
    int a = stoi(year + month + day );
    //cout << "final num " << a << endl;
    return a;
}

string Reservation::toStringAdmin(){
    return user->toString() + toString();
}

string Reservation::toString(){
    return " [number of beds] " + to_string(numOfBeds) +  
            " [reserve date] " + reserveDate + " [checkout date] " + checkoutDate + "\n";
}