// g++ main.cpp room.cpp booking.cpp -o hotel
// ./hotel

#include <iostream>
#include <vector>
#include "room.h"
#include "booking.h"
using namespace std;

int main() {
    vector<Room>rooms= {
        Room(101,1500,"Single","AC, TV & Breakfast"),
        Room(102,3000,"Double","AC, Wifi, TV & Breakfast"),
        Room(103,4500,"Suite","AC, Wifi, TV, Breakfast, Jacuzzi & Sauna")
    };
    //pehle user ko welcome krna hai aur uske baad pucho ki kya service chahiye
    cout << "\n-----------------------------";
    cout << "\n  WELCOME TO PARADISE HOTEL";
    cout << "\n-----------------------------\n";
    cout << "Thank you for choosing us!\n";
    //ab input lo ki user konsi service lena chahta hai
    int choice;
    do{
        cout<<"\n===== MAIN MENU =====\n";
        cout<<"1. View Rooms\n";
        cout<<"2. Book Room\n";
        cout<<"3. Cancel Booking\n";
        cout<<"4. Update Booking\n";
        cout<<"5. View My Bookings\n";
        cout<<"6. Exit\n";
        cout<<"Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                viewRooms(rooms);
                break;
            case 2:
                bookRoom(rooms);
                break;
            case 3:
                cancelBooking();
                break;
            case 4:
                updateBooking();
                break;
            case 5:
                viewMyBookings();
                break;
            case 6:
                cout << "Thank you! See you again.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } 
    while(choice!=6);//choice=6 hone par user ne exit leliya to dobara options show nahi karenge

    return 0;
}
