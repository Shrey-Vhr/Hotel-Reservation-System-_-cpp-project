#ifndef ADMIN_H
#define ADMIN_H

#include "room.h"
#include <vector>
using namespace std;

//admin ka login function
bool adminLogin();

//room functions
void addRoom(vector<Room>& rooms);
void removeRoom(vector<Room>& rooms);
void updateRoom(vector<Room>& rooms);
void viewAllRooms(const vector<Room>& rooms);

//booking functions
void viewAllBookings();
void removeBooking(vector<Room>& rooms);

void loadRoomsFromFile(vector<Room>& rooms);
void saveRoomsToFile(const vector<Room>& rooms);

#endif