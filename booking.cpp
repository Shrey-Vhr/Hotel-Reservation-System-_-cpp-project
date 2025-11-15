#include "booking.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

// Book a room and save in bookings.txt
void bookRoom(const vector<Room>& rooms) {
    string name, phone;
    int roomNo;
    cout << "\nEnter your name: ";
    cin >> ws;
    getline(cin, name);
    cout << "Enter phone number: ";
    cin >> phone;
    while (phone.length() != 10) {
    cout << "Invalid! Phone number must be EXACTLY 10 digits.\n";
    cout << "Enter again: ";
    cin >> phone;
    }

    cout << "Enter room number to book: ";
    cin >> roomNo;

    ofstream fout("bookings.txt", ios::app);// input output stream , append.. append isliye taki pichla data na udjaye aur file ko modify krein naki rewrite
    fout << "Name: " << name << "\n"
         << "Phone: " << phone << "\n"
         << "Room: " << roomNo << "\n"
         << "-----------------------------\n";
    fout.close();

    cout<<"Booking confirmed for "<<name<<"!\n";
}

// Cancel booking
void cancelBooking() {
    string phone;
    cout << "\nEnter your phone number to cancel booking: ";
    cin >> phone;
    while (phone.length() != 10) {
    cout << "Invalid! Phone number must be EXACTLY 10 digits.\n";
    cout << "Enter again: ";
    cin >> phone;
    }

    ifstream fin("bookings.txt");
    ofstream fout("temp.txt");

    if (!fin) {
        cout << "No bookings found.\n";
        return;
    }

    string line, block, ph;
    bool found = false;

    while (getline(fin, line)) {
        if (line.empty()) continue;

        block += line + "\n";  // store each line into current booking block

        // If this line is the separator → block is complete
        if (line.find("-----------------------------") != string::npos) {

            // 1. Find the phone number inside the current block
            size_t pos = block.find("Phone: "); // stores the index returned by find.. size_t is unsigned integer type and can never be -ve
            if (pos != string::npos){// agar phine word milgya to...
                ph = block.substr(pos + 7, block.find("\n", pos) - (pos + 7));

                // Clean hidden characters
                ph.erase(remove(ph.begin(), ph.end(), '\r'), ph.end());
                ph.erase(remove(ph.begin(), ph.end(), '\n'), ph.end());
            }

            // 2. Compare with the phone number user entered
            if (ph == phone) {
                found = true;
            } else {
                // Write this block to temp file
                fout << block;
            }

            // Reset for next booking
            block.clear();
            ph.clear();
        }
    }

    fin.close();
    fout.close();

    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    if (found)
        cout << "Booking cancelled successfully!\n";
    else
        cout << "No booking found for this phone number.\n";
}


void updateBooking(){
    string phone;
    cout<<"\nEnter your phone number to update booking: ";
    cin>>phone;
    while (phone.length() != 10) {
    cout << "Invalid! Phone number must be EXACTLY 10 digits.\n";
    cout << "Enter again: ";
    cin >> phone;
    }

    ifstream fin("bookings.txt");
    ofstream fout("temp.txt");

    if(!fin){
        cout<<"No bookings found.\n";
        return;
    }

    string line, newRoom;
    bool found=false;
    bool skipNextLine=false; // flag to skip old Room line

    while(getline(fin,line)){
        //Skip empty lines for safety
        if(line.empty()) continue;

        //Skip writing the old Room line after updating
        if(skipNextLine){
            skipNextLine=false;
            continue;
        }

        if(line.find("Phone: ") != string::npos){
            string ph = line.substr(7);
            ph.erase(remove(ph.begin(), ph.end(),'\r'), ph.end());
            ph.erase(remove(ph.begin(), ph.end(),'\n'), ph.end());

            if(ph == phone){
                found=true;
                fout<<line<<"\n";//keep phone line as is

                //Now skip the next Room line and replace with new
                getline(fin, line); // read the next line (old Room)
                skipNextLine=false; // already skipped manually

                cout<<"Enter new room number: ";
                cin>>newRoom;
                fout<<"Room: "<<newRoom<<"\n";// write new room number
                continue; // skip to next iteration
            }
        }

        // Normal line writing for all other cases
        fout<<line<<"\n";
    }

    fin.close();
    fout.close();

    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    if(found)
        cout<<"Booking updated successfully!\n";
    else
        cout<<"No booking found for this phone number.\n";
}


void viewMyBookings(){
    string phone;
    cout<<"\nEnter your phone number to view your bookings: ";
    cin>>phone;
    while (phone.length() != 10) {
    cout << "Invalid! Phone number must be EXACTLY 10 digits.\n";
    cout << "Enter again: ";
    cin >> phone;
    }

    ifstream fin("bookings.txt");
    if(!fin){
        cout<<"No booking records found yet.\n";
        return;
    }

    string line;
    bool found=false;

    cout<<"\n=== Your Bookings ===\n";

    //temp variables to hold n view booking details
    string name, ph, room;

     while(getline(fin,line)){
        //agr name milta h to usme se username read n store krlo
        if (line.find("Name:") != string::npos) {
            name = line.substr(6);//username 7th character se start hora h
        }
        //agr phone milta h to usme se phone no. read n store krlo
        else if (line.find("Phone:") != string::npos) {
            ph = line.substr(7);//phone no. 8th character se start hora h
            ph.erase(remove(ph.begin(), ph.end(), '\r'), ph.end());
            ph.erase(remove(ph.begin(), ph.end(), '\n'), ph.end());

        } 
        //agr room milta h to usme se room no. read n store krlo
        else if(line.find("Room:") != string::npos){
            room = line.substr(6);//room no. 7th character se start hora h
        
            //Once we have all details, check if phone matches
            if(ph == phone){
                cout<<"Name: "<<name<<endl;
                cout<<"Phone: "<<ph<<endl;
                cout<<"Room: "<<room<<endl;
                cout<<"-----------------------------\n";
                found=true;
            }
        }
        else if(line.find("-----------------------------") != string::npos) {
            //reset for next booking
            name.clear();
            ph.clear();
            room.clear();
        }
    }

    fin.close();

    if(!found){
        cout<<"No bookings found for this phone number.\n";
    }
}

