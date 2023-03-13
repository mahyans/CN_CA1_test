#include "IncludeAndDefine.hpp"

class Date{
    int day, month, year;
    public:
        Date(string strDate){
            stringstream ss(strDate);
            string _year, _month, _day;
            getline(ss, _day, '-');
            getline(ss, _month, '-');
            getline(ss, _year);
            day = stoi(_day);
            month = stoi(_month);
            year = stoi(_year);
        }
        void addDay(int days){
            day += days;
            if(day  > 30){
                month += 1;
                day -= 30;
            }
            if(month > 12){
                year += 1;
                month -= 12;
            }
        }
        std::string toSting(){
            stringstream ss;
            ss << day << "-" << month << "-" << year;
            return ss.str();
        }

};