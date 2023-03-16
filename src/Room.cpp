#include "../include/Room.hpp"
using namespace std;

//int Room::count{0};

Room::Room(string number, int price, int maxCapacity, int _capacity)
    : number(number), price(price), maxCapacity(maxCapacity){
    capacity = maxCapacity;
    status = NOT_FULL;
}
int Room::getPrice()
{
    return price;
}

int Room::getCapacity()
{
    return capacity;
}
int Room::getMaxCapacity()
{
    return maxCapacity;
}
bool Room::hasConflict(Reservation* newRes){
    int start = newRes->getStartInterval();
    int end = newRes->getEndInterval();
    int wanted_beds = newRes->getNumOfBeds();
    int total_beds = 0;
    //cout << start << " " << end << endl;
    for (auto reserve : users){
        int res1 = reserve.getStartInterval();
        int res2 = reserve.getEndInterval();
        /*cout <<"* " << res1 << " " << res2 << endl;
        cout << (res1 <= start & start <= res2);
        cout << (res1 <= end & end <= res2);
        cout << ((res1 <= start & start <= res2) | (res1 <= end & end <= res2)) << endl;*/
        
        bool time_confilct = (res1 <= start & start <= res2) | (res1 <= end & end <= res2);
        if( time_confilct )
            total_beds += reserve.getNumOfBeds();
        //cout << total_beds << endl;
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
void Room::modify(string number,int newMaxCapacity,int newPrice)
{
    if(numMatches(number))
        maxCapacity = newMaxCapacity;
        price = newPrice ;

}