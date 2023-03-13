#include "../include/Room.hpp"
using namespace std;

int Room::count{0};

Room::Room(string number, int price, int maxCapacity, int capacity)
    : number(number), price(price), maxCapacity(maxCapacity), capacity(capacity){
    status = NOT_FULL;
}

bool Room::hasConflict(Reservation* newRes){
    int start = newRes->getStartInterval();
    int end = newRes->getEndInterval();
    for (auto reserve : users){
        int res1 = reserve.getStartInterval();
        int res2 = reserve.getEndInterval();
        if( (res1 <= start & start <= res2) | (res1 <= end & end <= res2))
            return true;
    }
    return false;
}

void Room::addReservation(Reservation* rs){
    if(capacity == 0)
        status = FULL;
    users.push_back(*rs);
}

string Room::toString(){
    stringstream ss, ss1;
    for(auto res : users){
        ss1 << res.toString() ;
    }
    ss << " Room data: " << " [number] "  << number << " [status] " << status << 
            " [price] " << price << " [max capactiy] " << maxCapacity << " [capacity] " << capacity << 
            " [reservations] " << "{" << ss1.str() << "} ";
    return ss.str();
}

string Room::toStringAdmin(){
    stringstream ss, ss1;
    for(auto res : users){
        ss1 << res.toStringAdmin();
    }
    ss << " Room data: " << " [number] "  << number << " [status] " << status << 
            " [price] " << price << " [max capactiy] " << maxCapacity << " [capacity] " << capacity << 
            " [reservations] " << "{" << ss1.str() << "} ";
    return ss.str();
}