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

    cout << "✅ Booking confirmed for " << name << "!\n";
}

// Cancel booking
void cancelBooking() {
    string phone;
    cout << "\nEnter your phone number to cancel booking: ";
    cin >> phone;

    ifstream fin("bookings.txt");
    ofstream fout("temp.txt");

    if (!fin) {
        cout << "⚠️ No bookings found.\n";
        return;
    }

    string line;
    bool skip = false, found = false;

    while (getline(fin, line)) {
        if (line.find("Phone: ") != string::npos) {
            string ph = line.substr(7);
            if (ph == phone) {
                skip = true;
                found = true;
            }
        }
        if (!skip) fout << line << "\n";
        if (line.find("-----------------------------") != string::npos)
            skip = false;
    }

    fin.close();
    fout.close();

    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    if (found)
        cout << "✅ Booking cancelled successfully.\n";
    else
        cout << "❌ No booking found for this phone number.\n";
}

// Placeholder for future updates
void updateBooking() {
    cout << "\nFeature under development!\n";
}

void viewMyBookings() {
    cout << "\nFeature under development!\n";
}
