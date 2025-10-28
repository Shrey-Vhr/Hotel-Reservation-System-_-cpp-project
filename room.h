#ifndef ROOM_H  //agar roo.h deefine nahi hua abi tak
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
    
    //ye exist yha krte h par inka code kahi aur hoga isliye 3 dots aarhe hai
    //constructor
    Room(int n, float p, string t, string f);

    //display krne ke liye function call
    void display();
};

//ye rooms ki detail leke vector me store karega
void viewRooms(const vector<Room>& rooms);

#endif  //end of file