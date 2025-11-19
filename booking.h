// agar booking.h included nhi hai pehle se to kardo
#ifndef BOOKING_H
#define BOOKING_H

#include "room.h"
#include <vector>
using namespace std;
//sirf iske liye room ki details ki zarurat hai
void bookRoom(vector<Room>& rooms);
//in sab ke liye rooms show krne ki nahi zarurat
void cancelBooking(vector<Room>& rooms);
void updateBooking(vector<Room>& rooms);
void viewMyBookings();

#endif