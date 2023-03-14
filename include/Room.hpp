#ifndef ROOM_HEADER
#define ROOM_HEADER

#include "IncludeAndDefine.hpp"
#include "Reservation.hpp"

#define FULL 1;
#define NOT_FULL 0;

class Room {
    static int count;
    public:
        Room(std::string number, int price, int maxCapacity, int capacity);
        void printRoom();
        bool numMatches(string _number);
        void addReservation(Reservation* newRsv);
        bool hasConflict(Reservation* rsv);
        int getCapacity(){return capacity;};
        std::string getNum(){return number;};
        std::string toString();
        std::string toStringAdmin();
        int getPrice(){return price;};
        vector <Reservation> users;
        void removeReservationById(int id, int n);
        int findNumOfreserveById(int id);
    private:
        int status, price, maxCapacity, capacity;
        std::string number;
        
};

#endif