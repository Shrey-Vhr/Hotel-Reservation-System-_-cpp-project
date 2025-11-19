#include "room.h"
#include <iostream>
using namespace std;

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
void viewAllRooms(const vector<Room>& rooms) {
    if(rooms.empty()){
        cout<<"\nNo rooms available.\n";
        return;
    }
    
    cout<<"\n===== ALL ROOMS =====\n";
    for(int i = 0; i < rooms.size(); i++){
        rooms[i].display();
    }
}