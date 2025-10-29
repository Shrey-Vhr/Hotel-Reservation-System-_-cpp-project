#include "room.h"
#include <iostream>
using namespace std;

//Constructor define
//:: is scope resolution operator
Room::Room(int n,float p,string t,string f) {
    number=n;
    price=p;
    type=t;
    facilities=f;
}
//Function to display room info
void Room::display() const{
    cout<<"Room "<<number<<" ("<<type<<") - Rs."<<price<<endl;
    cout<<"Facilities: "<<facilities<<"\n\n";
}

//Show all available rooms
void viewRooms(const vector<Room>& rooms) {
    cout << "\n=== Available Rooms ===\n";
    for (int i = 0; i < rooms.size(); i++) {
    rooms[i].display();
    }
}