#include "admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
using namespace std;

const string ADMIN_PASSWORD="admin123";

bool adminLogin(){
    string password;
    int attempts=3;
    
    cout<<"\n===== ADMIN LOGIN =====\n";
    
    while(attempts>0){
        cout<<"Enter admin password (Attempts left: " << attempts << "): ";
        cin>>password;
        
        if(password==ADMIN_PASSWORD){
            cout<<"Login successful!\n";
            return true;
        }else{
            attempts--;
            if(attempts>0) {
                cout<<"Incorrect password. Try again.\n";
            }else{
                cout<<"Access denied. Too many failed attempts.\n";
            }
        }
    }
    return false;
}
// this function loads room details from rooms.txt into the rooms vector for admin operations
void loadRoomsFromFile(vector<Room>& rooms) {
    ifstream fin("rooms.txt");
    if(!fin){
        return;
    }
    rooms.clear();
    string line;
    int number=0;
    float price=0;
    string type="", facilities="";
    
    while(getline(fin, line)){
        if(line.empty()) continue;
        
        if(line.find("Room: ") != string::npos){
            number=stoi(line.substr(6));
        }
        else if(line.find("Price: ") != string::npos){
            price=stof(line.substr(7));
        }
        else if(line.find("Type: ") != string::npos){
            type=line.substr(6);
        }
        else if(line.find("Facilities: ") != string::npos){
            facilities=line.substr(12);
        }
        else if(line.find("-----------------------------") != string::npos){
            if(number != 0){
                rooms.push_back(Room(number, price, type, facilities));
                //reset for next room
                number=0;
                price=0;
                type="";
                facilities="";
            }
        }
    }
    
    //for handling case where last room doesnt hv separator
    if(number != 0){
        rooms.push_back(Room(number, price, type, facilities));
    }
    fin.close();
}
// this function saves the current rooms vector to rooms.txt after any admin modifications
void saveRoomsToFile(const vector<Room>& rooms){
    ofstream fout("rooms.txt");//fout is used for writing to file
    for(int i = 0; i < rooms.size(); i++){
        fout<<"Room: "<<rooms[i].number<<"\n"
            <<"Price: "<<rooms[i].price<<"\n"
            <<"Type: "<<rooms[i].type<<"\n"
            <<"Facilities: "<<rooms[i].facilities<<"\n"
            <<"-----------------------------\n";
    }
    fout.close();
}

void addRoom(vector<Room>& rooms){
    int number;
    float price;
    string type, facilities;
    
    cout<<"\n===== ADD NEW ROOM =====\n";
    cout<<"Enter room number: ";
    cin>>number;
    
    //check if room no. already exists
    for(int i=0; i<rooms.size(); i++){
        if(rooms[i].number==number){
            cout<<"Room number "<<number<<" already exists!\n";
            return;
        }
    }
    
    cout<<"Enter price per night: ";
    cin>>price;
    cout<<"Enter room type (Single, Double, Suite): ";
    cin.ignore();
    getline(cin, type);
    cout<<"Enter facilities (AC, TV, Wifi, Breakfast, Jacuzzi): ";
    getline(cin, facilities);
    
    rooms.push_back(Room(number, price, type, facilities));
    saveRoomsToFile(rooms);
    cout<<"Room added successfully!\n";
}

void removeRoom(vector<Room>& rooms){
    if(rooms.empty()){
        cout<<"\nNo rooms available to remove.\n";
        return;
    }
    
    int roomNo;
    cout<<"\n===== REMOVE ROOM =====\n";
    cout<<"Enter room number to remove: ";
    cin>>roomNo;
    
    int roomIndex=-1;
    for(int i=0; i<rooms.size(); i++){
        if(rooms[i].number==roomNo){
            roomIndex=i;
            break;
        }
    }
    
    if(roomIndex!=-1){
        rooms.erase(rooms.begin()+roomIndex);
        saveRoomsToFile(rooms);
        cout<<"Room "<<roomNo<<" removed successfully!\n";
    }else{
        cout<<"Room "<<roomNo<<" not found!\n";
    }
}

void updateRoom(vector<Room>& rooms) {
    if(rooms.empty()){
        cout<<"\nNo rooms available to update.\n";
        return;
    }
    
    int roomNo;
    cout<<"\n===== UPDATE ROOM =====\n";
    cout<<"Enter room number to update: ";
    cin>>roomNo;
    
    for(int i=0; i<rooms.size(); i++){
        if(rooms[i].number==roomNo){
            cout<<"\nCurrent details:\n";
            rooms[i].display();
            int choice;
            cout<<"What would you like to update?\n";
            cout<<"1. Price\n";
            cout<<"2. Type\n";
            cout<<"3. Facilities\n";
            cout<<"4. All\n";
            cout<<"Enter choice: ";
            cin>>choice;
            
            if(choice==1 || choice==4){
                cout<<"Enter new price: ";
                cin>>rooms[i].price;
            }
            if(choice==2 || choice==4){
                cout<<"Enter new type: ";
                cin.ignore();
                getline(cin, rooms[i].type);
            }
            if(choice==3 || choice==4){
                cout<<"Enter new facilities: ";
                cin.ignore();
                getline(cin, rooms[i].facilities);
            }
            
            saveRoomsToFile(rooms); //save changes to file
            cout<<"Room updated successfully!\n";
            return;
        }
    }
    
    cout<<"Room "<<roomNo<<" not found!\n";
}



void viewAllBookings() {
    ifstream fin("bookings.txt"); // Open bookings file to read
    if(!fin){//file exists nhi krti
        cout<<"\nNo booking records found.\n";
        return;
    }
    
    cout<<"\n===== ALL BOOKINGS =====\n";
    string line;
    int count=0;
    
    while(getline(fin, line)){
        if(line.find("-----------------------------") != string::npos){
            count++;
            cout<<"\n";
        }else{
            cout<<line<<"\n";
        }
    }
    
    fin.close();
    
    if(count==0){
        cout<<"No bookings found.\n";
    } else {
        cout<<"\nTotal bookings: "<<count<<"\n";
    }
}

void removeBooking(vector<Room>& rooms){
    string phone;
    cout<<"\n===== REMOVE BOOKING =====\n";
    cout<<"Enter phone number of booking to remove: ";
    cin>>phone;
    while(phone.length()!= 10){
        cout<<"Invalid! Phone number must be EXACTLY 10 digits.\n";
        cout<<"Enter again: ";
        cin>>phone;
    }

    ifstream fin("bookings.txt");
    ofstream fout("temp.txt");

    if(!fin){
        cout<<"No bookings found.\n";
        return;
    }

    string line, block, ph;
    bool found=false;
    string bookingName = "";
    int roomNo=0;
    float roomPrice=0;
    string roomType="", roomFacilities="";

    while(getline(fin, line)){
        if(line.empty()) continue;
        block+=line+"\n";
        if(line.find("-----------------------------") != string::npos){
            size_t pos = block.find("Phone: ");
            if (pos != string::npos) {
                size_t start = pos + 7;
                size_t end = block.find('\n', start);
                if (end == string::npos) end = block.size();
                ph = block.substr(start, end - start);
                ph.erase(remove(ph.begin(), ph.end(), '\r'), ph.end());
                ph.erase(remove(ph.begin(), ph.end(), '\n'), ph.end());
            }
            if(ph == phone){
                found=true;
                size_t namePos = block.find("Name: ");
                if (namePos != string::npos) {
                    size_t nStart = namePos + 6;
                    size_t nEnd = block.find('\n', nStart);
                    if (nEnd == string::npos) nEnd = block.size();
                    bookingName = block.substr(nStart, nEnd - nStart);
                    bookingName.erase(remove(bookingName.begin(), bookingName.end(), '\r'), bookingName.end());
                    bookingName.erase(remove(bookingName.begin(), bookingName.end(), '\n'), bookingName.end());
                }
                
                // Extract room details to restore
                size_t roomPos = block.find("Room: ");
                if (roomPos != string::npos) {
                    size_t rStart = roomPos + 6;
                    size_t rEnd = block.find('\n', rStart);
                    if (rEnd == string::npos) rEnd = block.size();
                    string roomStr = block.substr(rStart, rEnd - rStart);
                    roomStr.erase(remove(roomStr.begin(), roomStr.end(), '\r'), roomStr.end());
                    roomStr.erase(remove(roomStr.begin(), roomStr.end(), '\n'), roomStr.end());
                    roomNo = stoi(roomStr);
                }
                
                size_t pricePos = block.find("Room Price: ");
                if (pricePos != string::npos) {
                    size_t pStart = pricePos + 12;
                    size_t pEnd = block.find('\n', pStart);
                    if (pEnd == string::npos) pEnd = block.size();
                    string priceStr = block.substr(pStart, pEnd - pStart);
                    priceStr.erase(remove(priceStr.begin(), priceStr.end(), '\r'), priceStr.end());
                    priceStr.erase(remove(priceStr.begin(), priceStr.end(), '\n'), priceStr.end());
                    roomPrice = stof(priceStr);
                }
                
                size_t typePos = block.find("Room Type: ");
                if (typePos != string::npos) {
                    size_t tStart = typePos + 11;
                    size_t tEnd = block.find('\n', tStart);
                    if (tEnd == string::npos) tEnd = block.size();
                    roomType = block.substr(tStart, tEnd - tStart);
                    roomType.erase(remove(roomType.begin(), roomType.end(), '\r'), roomType.end());
                    roomType.erase(remove(roomType.begin(), roomType.end(), '\n'), roomType.end());
                }
                
                size_t facilitiesPos = block.find("Room Facilities: ");
                if (facilitiesPos != string::npos) {
                    size_t fStart = facilitiesPos + 16;
                    size_t fEnd = block.find('\n', fStart);
                    if (fEnd == string::npos) fEnd = block.size();
                    roomFacilities = block.substr(fStart, fEnd - fStart);
                    //remove function removes /n /r characters from whole string
                    roomFacilities.erase(remove(roomFacilities.begin(), roomFacilities.end(), '\r'), roomFacilities.end());
                    roomFacilities.erase(remove(roomFacilities.begin(), roomFacilities.end(), '\n'), roomFacilities.end());
                }
                
                //restore room to avail list
                if(roomNo!=0){
                    rooms.push_back(Room(roomNo, roomPrice, roomType, roomFacilities));
                    saveRoomsToFile(rooms);
                }
            }else{
                //write this block to temp file
                fout<<block;
            }
            block.clear();
            ph.clear();
            bookingName.clear();
            roomNo=0;
            roomPrice=0;
            roomType="";
            roomFacilities="";
        }
    }

    fin.close();
    fout.close();

    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    if(found){
        cout<<"Booking removed successfully";
        if(!bookingName.empty()){
            cout<<" for "<<bookingName;
        }
        cout<<"!\n";
    }else{
        cout<<"No booking found for this phone number.\n";
    }
}