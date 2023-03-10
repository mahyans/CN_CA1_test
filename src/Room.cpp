#include "../include/Room.hpp"
using namespace std;

Room::Room(string number, int price, int maxCapacity): number(number), price(price), maxCapacity(maxCapacity){
    status = NOT_FULL;
    capacity = maxCapacity;
    users = vector<Reservation>{};
}

bool Room::hasConflict(Reservation newRes){
    int start = newRes.getStartInterval();
    int end = newRes.getEndInterval();
    for (auto reserve : users){
        int res1 = reserve.getStartInterval();
        int res2 = reserve.getEndInterval();
        if( (res1 <= start & start <= res2) | (res1 <= end & end <= res2))
            return true;
    }
    return false;
}

void Room::addReservation(Reservation rs){
    capacity -= rs.getNumOfBeds();
    if(capacity == 0)
        status = FULL;
    users.push_back(rs);
}

string Room::toString(){
    stringstream ss;
    ss << " Room data: " << " [number] "  << number << " [status] " << status << 
            " [price] " << price << " [max capactiy] " << maxCapacity << " [capacity] " << capacity << 
            " [users] " << phoneNumber << " [address] " << address << endl;
    return ss.str();
}