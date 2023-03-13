#include "../include/IncludeAndDefine.hpp"
#include "../include/User.hpp"
using namespace std;

class Reservation{
    public:
        Reservation(User* user, int _numOfBeds, string _reserveDate, string _checkoutDate);
        int getStartInterval();
        int getEndInterval(); 
        int getNumOfBeds(){return numOfBeds;};
        string toStringAdmin();
        string toString();

    private:
        int numOfBeds;
        User* user;
        string reserveDate, checkoutDate;
};

