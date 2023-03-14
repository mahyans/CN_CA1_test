#include "../include/IncludeAndDefine.hpp"
#include "../include/User.hpp"
using namespace std;

class Reservation{
    public:
        Reservation(User *user, int _numOfBeds, string _reserveDate, string _checkoutDate);
        int getStartInterval();
        int getEndInterval(); 
        int getInterval(int a);
        int getNumOfBeds(){return numOfBeds;};
        int getUserId(){return user->getId();};
        string toStringAdmin();
        string toString();

    private:
        int numOfBeds;
        User* user;
        string reserveDate, checkoutDate;
};

