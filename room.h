#ifndef ROOM_H  //agar room h define nahi hua abi tak
#define ROOM_H  //to usko define krdo

//Header files
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Room {
public:
    int number;
    float price;
    string type;
    string facilities;
    
    //constructor
    Room(int n, float p, string t, string f);

    //display krne ke liye function call
    void display() const;//so it does not change or modify anything
};

//ye rooms ki detail leke vector me store karega
void viewAllRooms(const vector<Room>& rooms);

#endif  //end of file