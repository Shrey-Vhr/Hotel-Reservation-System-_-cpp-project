#include "booking.h"
#include <iostream>
#include <fstream>
#include <sstream>
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
    cout << "Enter room number to book: ";
    cin >> roomNo;

    ofstream fout("bookings.txt", ios::app);
    fout << "Name: " << name << "\n"
         << "Phone: " << phone << "\n"
         << "Room: " << roomNo << "\n"
         << "-----------------------------\n";
    fout.close();

    cout << "Booking confirmed for " << name << "!\n";
}

// Cancel booking
void cancelBooking() {
    string phone;
    cout<<"\nEnter your phone number to cancel booking: ";
    cin>>phone;

    ifstream fin("bookings.txt");
    ofstream fout("temp.txt");

    if(!fin){
        cout<<"No bookings found.\n";
        return;
    }

    string line;
    bool skip=false, found=false;

    while(getline(fin, line)){
        if(line.find("Phone: ")!=string::npos) {
            string ph=line.substr(7);
            if(ph==phone) {
                skip=true;
                found=true;
            }
        }
        if(!skip) fout<<line<<"\n";
        if(line.find("-----------------------------")!=string::npos)
            skip=false;
    }

    fin.close();
    fout.close();

    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    if(found)
        cout<<"Booking cancelled successfully.\n";
    else
        cout<<"No booking found for this phone number.\n";
}

void updateBooking() {
    string phone;
    cout<<"\nEnter your phone number to update booking: ";
    cin>>phone;

    ifstream fin("bookings.txt");// reading
    ofstream fout("temp.txt");//writing in temp file.. agr present nahi hogi to create kr dega

    if(!fin){// if file doesnt exist
        cout<<"No bookings found.\n";
        return;
    }

    string line;
    bool found=false; // to check if ph no. matched in bookings file or not
    string newRoom;

    while(getline(fin,line)){// reads the file line by line until the end.. reads ph no., name, etc etc
        if(line.find("Phone: ")!=string::npos){// agr nth position se pehle pehel ph no. milgya
            string ph=line.substr(7);// kyunki ph me sirf no. store karna hai aur wo 8th character se shuru hota h
            
            if(ph==phone){
                found=true;
                fout<<line<<"\n";// insert the same phone no. into temp file

                //replace the old line with new one
                getline(fin,line);//reads the line which contains old room info
                cout<<"Enter new room number: ";
                cin>>newRoom;
                fout<<"Room: "<<newRoom<<"\n";
            }
        }
        fout<<line<<"\n";
    }

    fin.close();
    fout.close();

    remove("bookings.txt");
    rename("temp.txt","bookings.txt");

    if(found)
        cout<<"Booking updated successfully!\n";
    else
        cout<<"No booking found for this phone number.\n";
}

void viewMyBookings(){
    string phone;
    cout<<"\nEnter your phone number to view your bookings: ";
    cin>>phone;

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
        if(line.find("Name:")!=string::npos){
            name = line.substr(line.find("Name:") + 6);//username 7th character se start hora h
        }
        //agr phone milta h to usme se phone no. read n store krlo
        else if(line.find("Phone:")!=string::npos){
            ph = line.substr(line.find("Phone:") + 7);//phone no. 8th character se start hora h
        }
        //agr room milta h to usme se room no. read n store krlo
        else if(line.find("Room:")!=string::npos){
            room = line.substr(line.find("Room:") + 6);//room no. 7th character se start hora h

            //Once we have all details, check if phone matches
            if (ph == phone) {
                cout<<"Name: "<<name<<endl;
                cout<<"Phone: "<<ph<<endl;
                cout<<"Room: "<<room<<endl;
                cout<<"-----------------------------\n";
                found=true;
            }
        }
        else if (line.find("-----------------------------") != string::npos) {
            // reset for next booking safely
            name = "";
            ph = "";
            room = "";
        }
    }

    fin.close();

    if(!found){
        cout<<"No bookings found for this phone number.\n";
    }
}

