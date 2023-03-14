#ifndef ROOM_HEADER
#define ROOM_HEADER

#include "IncludeAndDefine.hpp"
#include "../include/Reservation.hpp"

#define FULL 1;
#define NOT_FULL 0;

class Room {
    static int count;
    public:
        Room(std::string number, int price, int maxCapacity, int capacity);
        void printRoom();
        void addReservation(Reservation* newRsv);
        bool hasConflict(Reservation* rsv);
        int getCapacity(){return capacity;};
        int getMaxCapacity(){return maxCapacity;};
        vector <Reservation> getUsers(return users;);
        std::string toString();
        std::string toStringAdmin();
    private:
        int status, price, maxCapacity, capacity;
        std::string number;
        vector <Reservation> users;
};

#endif