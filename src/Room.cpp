#include "../include/Room.hpp"
using namespace std;

int Room::count{0};

Room::Room(string number, int price, int maxCapacity, int _capacity)
    : number(number), price(price), maxCapacity(maxCapacity){
    capacity = maxCapacity;
    status = NOT_FULL;
}

void Room::removeAllReservation(){
    for(int i = 0; i < users.size(); i++){
        users.erase(users.begin()+i);
    }
    status = NOT_FULL;
}

bool Room::hasConflict(Reservation* newRes){
    int start = newRes->getInterval(1);
    int end = newRes->getInterval(0);
    int wanted_beds = newRes->getNumOfBeds();
    int total_beds = 0;
    for (auto reserve : users){
        int res1 = reserve.getInterval(1);
        int res2 = reserve.getInterval(0);
       
        bool time_confilct = (res1 <= start & start <= res2) | (res1 <= end & end <= res2);
        if( time_confilct )
            total_beds += reserve.getNumOfBeds();
    }
    if( wanted_beds > maxCapacity - total_beds )
            return true;
    return false;
}

int Room::findNumOfreserveById(int id){
    int n = 0;
    for(int i = 0; i < users.size(); i++){
        if(users[i].getUserId() == id){
            n++;
        } ;
    }
    return n;
}

void Room::removeReservationById(int id, int n){
    int x = 0;
    for(int i = 0; i < users.size(); i++){
        if(users[i].getUserId() == id & x < n){
            users.erase(users.begin()+i);
            x++;
        }
    }
}

void Room::addReservation(Reservation* rs){
    capacity -= rs->getNumOfBeds();
    if(capacity == 0)
        status = FULL;
    users.push_back(*rs);
}

bool Room::numMatches(string _num){
    if(_num == number){
        return true;
    }else return false;
}



string Room::toString(){
    stringstream ss, ss1;
    for(auto res : users){
        ss1 << res.toString() ;
    }
    ss << " Room data: " << " [number] "  << number << " [status] " << status << 
            " [price] " << price << " [max capactiy] " << maxCapacity <<  
            " [reservations] " << "\n{" << ss1.str() << "} \n";
    return ss.str();
}

string Room::toStringAdmin(){
    stringstream ss, ss1;
    for(auto res : users){
        ss1 << res.toStringAdmin();
    }
    ss << " Room data: " << " [number] "  << number << " [status] " << status << 
            " [price] " << price << " [max capactiy] " << maxCapacity <<  
            " [reservations] " << "\n{" << ss1.str() << "} \n";
    return ss.str();
}