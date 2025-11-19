// g++ main.cpp room.cpp booking.cpp admin.cpp -o hotel
// ./hotel

#include <iostream>
#include <vector>
#include "room.h"
#include "booking.h"
#include "admin.h"
using namespace std;

int main(){
    vector<Room> rooms;
    
    //load rooms from file
    loadRoomsFromFile(rooms);
    
    cout<<"\n-----------------------------";
    cout<<"\n  WELCOME TO PARADISE HOTEL";
    cout<<"\n-----------------------------\n";
    
    int userType;
    do{
        cout<<"\n===== SELECT USER TYPE =====\n";
        cout<<"1. User\n";
        cout<<"2. Admin\n";
        cout<<"3. Exit\n";
        cout<<"Enter your choice: ";
        cin>>userType;
        
        if(userType == 1){
            // USER PANEL
            int choice;
            do {
                cout<<"\n===== USER MENU =====\n";
                cout<<"1. View Rooms\n";
                cout<<"2. Book Room\n";
                cout<<"3. Cancel Booking\n";
                cout<<"4. Update Booking\n";
                cout<<"5. View My Bookings\n";
                cout<<"6. Back to Main Menu\n";
                cout<<"Enter your choice: ";
                cin>>choice;
                
                switch(choice){
                    case 1:
                        viewAllRooms(rooms);
                        break;
                    case 2:
                        bookRoom(rooms);
                        break;
                    case 3:
                        cancelBooking(rooms);
                        break;
                    case 4:
                        updateBooking(rooms);
                        break;
                    case 5:
                        viewMyBookings();
                        break;
                    case 6:
                        break;
                    default:
                        cout<<"Invalid choice. Try again.\n";
                }
            } while(choice != 6);
            
        }else if(userType == 2){
            // ADMIN PANEL
            if(adminLogin()){
                int adminChoice;
                do {
                    cout<<"\n===== ADMIN MENU =====\n";
                    cout<<"1. Add Room\n";
                    cout<<"2. Remove Room\n";
                    cout<<"3. Update Room\n";
                    cout<<"4. View All Rooms\n";
                    cout<<"5. View All Bookings\n";
                    cout<<"6. Remove Booking\n";
                    cout<<"7. Back to Main Menu\n";
                    cout<<"Enter your choice: ";
                    cin >> adminChoice;
                    
                    switch(adminChoice) {
                        case 1:
                            addRoom(rooms);
                            break;
                        case 2:
                            removeRoom(rooms);
                            break;
                        case 3:
                            updateRoom(rooms);
                            break;
                        case 4:
                            viewAllRooms(rooms);
                            break;
                        case 5:
                            viewAllBookings();
                            break;
                        case 6:
                            removeBooking(rooms);
                            break;
                        case 7:
                            break;
                        default:
                            cout<<"Invalid choice. Try again.\n";
                    }
                } while(adminChoice != 7);
            }
        }else if(userType == 3){
            cout<<"Thank you! See you again.\n";
        } else {
            cout<<"Invalid choice. Try again.\n";
        }
    }while(userType != 3);
    
    return 0;
}