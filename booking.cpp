#include "booking.h"
#include "admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <limits>
using namespace std;

void bookRoom(vector<Room>& rooms){
    string name, phone;
    int roomNo;
    cout<<"\nEnter your name: ";
    cin.ignore(100, '\n');//maximum number of characters to ignore.. 100.. safe no. hai.. name 100 ch se bada nai hoga
    getline(cin, name);
    cout<<"Enter phone number: ";
    cin>>phone;
    while(phone.length() != 10){
        cout<<"Invalid! Phone number must be exactly 10 digits.\n";
        cout<<"Enter again: ";
        cin>>phone;
    }
    cout<<"Enter room number to book: ";
    cin>>roomNo;
    //check room availability
    bool roomFound=false;
    float roomPrice=0;
    string roomType="", roomFacilities="";
    int roomIndex=-1;
    
    for(int i=0;i<rooms.size();i++){
        if(rooms[i].number==roomNo) {
            //room ki details store krlo del krne se pehle
            roomPrice=rooms[i].price;
            roomType=rooms[i].type;
            roomFacilities=rooms[i].facilities;
            roomFound=true;
            roomIndex=i;
        }
    }
    
    if(!roomFound){
        cout<<"Room "<<roomNo<<" not found or already booked!\n";
        return;
    }
    
    // room book hogya hai to ab usko available rooms se hata do
    rooms.erase(rooms.begin()+roomIndex);
    saveRoomsToFile(rooms); // nayi file ko save krdo available rooms ki

    // booking details ko bookings.txt me save krdo.. append mode me
    ofstream fout("bookings.txt", ios::app);
    fout<<"Name: "<<name<<"\n"
         <<"Phone: "<<phone<<"\n"
         <<"Room: "<<roomNo<<"\n"
         <<"Room Price: "<<roomPrice<<"\n"
         <<"Room Type: "<<roomType<<"\n"
         <<"Room Facilities: "<<roomFacilities<<"\n"
         <<"-----------------------------\n";
    fout.close();

    cout<<"Booking confirmed for "<<name<<"!\n";
}


void cancelBooking(vector<Room>& rooms){
    string phone;
    cout<<"\nEnter your phone number to cancel booking: ";
    cin>>phone;
    while(phone.length() != 10){
        cout<<"Invalid! Phone number must be exactly 10 digits.\n";
        cout<<"Enter again: ";
        cin>>phone;
    }

    ifstream fin("bookings.txt");
    ofstream fout("temp.txt");

    // The strategy to "delete" a booking from a file is to:
    // 1. Read from the original file (bookings.txt).
    // 2. Write all the bookings we want to KEEP to a new file (temp.txt).
    // 3. Skip writing the booking we want to cancel.
    // 4. Finally, replace bookings.txt with temp.txt.
    if (!fin) {
        cout<<"No bookings found.\n";
        return;
    }

    string line, block, ph;
    bool found=false;
    int roomNo=0;
    float roomPrice=0;
    string roomType="", roomFacilities="";

    while(getline(fin, line)){
        if(line.empty()) continue;// blank lines skip krdo
        // block me ek booking ki saari details jayengi
        block+=line + "\n";  // jis line pe hai usko add krte jao block me
        
        
        if (line.find("-----------------------------") != string::npos) {

            //find phone no. 
            //size_t is used because it is suitable for representing sizes and positions in strings
            size_t pos=block.find("Phone: ");
            if(pos != string::npos){
                size_t start=pos + 7;// actual phone number 7 ke baad start hoga
                size_t end=block.find('\n', start);// jo next newline hoga wahi end hoga
                if (end==string::npos) end = block.size();
                ph=block.substr(start,end - start);// ye line start se end tak ka substring lega

                // ye characters hidden hote hai jo file me unknowingly aate hai.. these are unwanted and need to be removed 
                ph.erase(remove(ph.begin(), ph.end(), '\r'), ph.end());
                ph.erase(remove(ph.begin(), ph.end(), '\n'), ph.end());
            }

            if(ph == phone){
                found=true;
                
                //extracting room details from booking
                size_t roomPos=block.find("Room: ");
                if(roomPos != string::npos){
                    size_t rStart=roomPos + 6;
                    size_t rEnd=block.find('\n', rStart);
                    if(rEnd == string::npos) rEnd=block.size();
                    string roomStr=block.substr(rStart, rEnd - rStart);
                    roomNo=stoi(roomStr);// string to int
                }
                
                size_t pricePos=block.find("Room Price: ");
                if(pricePos != string::npos){
                    size_t pStart=pricePos + 12;
                    size_t pEnd=block.find('\n', pStart);
                    if(pEnd==string::npos) pEnd=block.size();
                    string priceStr=block.substr(pStart, pEnd - pStart);
                    roomPrice= stof(priceStr);// string to float
                }
                
                size_t typePos=block.find("Room Type: ");
                if(typePos != string::npos){
                    size_t tStart=typePos + 11;
                    size_t tEnd=block.find('\n', tStart);
                    if (tEnd==string::npos) tEnd=block.size();
                    roomType=block.substr(tStart, tEnd - tStart);
                }
                
                size_t facilitiesPos=block.find("Room Facilities: ");
                if(facilitiesPos!=string::npos){
                    size_t fStart=facilitiesPos + 16;
                    size_t fEnd=block.find('\n', fStart);
                    if(fEnd==string::npos) fEnd=block.size();
                    roomFacilities=block.substr(fStart, fEnd - fStart);
                }
                
                //yeh booking cancel ho chuki hai ab isko file me write nahi karna
                //balki isko available rooms me wapas add karna hai
                if(roomNo != 0){
                    rooms.push_back(Room(roomNo, roomPrice, roomType, roomFacilities));
                    saveRoomsToFile(rooms);
                }
            }else{
                //this is not the booking we're looking for... so we keep it by writing it to temp.txt.
                fout<< block;
            }

            //reset for next booking
            block.clear();
            ph.clear();
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
        cout<<"Booking cancelled successfully!\n";
    }else{
        cout<<"No booking found for this phone number.\n";
    }
}


void updateBooking(vector<Room>& rooms){
    string phone;
    cout<<"\nEnter your phone number to update booking: ";
    cin>>phone;
    while(phone.length() != 10){
        cout<<"Invalid! Phone number must be exactly 10 digits.\n";
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

    int oldRoomNo=0;
    string bookingName, bookingPhone;

    while(getline(fin,line)){
        if(line.empty()) continue;
        block+=line + "\n";
        if(line.find("-----------------------------") != string::npos) {
            size_t pos=block.find("Phone: ");
            if (pos!=string::npos) {
                size_t start=pos + 7;
                size_t end=block.find('\n', start);
                if (end==string::npos) end=block.size();
                ph=block.substr(start, end - start);
                ph.erase(remove(ph.begin(), ph.end(), '\r'), ph.end());
                ph.erase(remove(ph.begin(), ph.end(), '\n'), ph.end());
            }

            if(ph == phone){
                found=true;

                size_t namePos=block.find("Name: ");
                if (namePos!=string::npos) {
                    size_t nStart=namePos + 6;
                    size_t nEnd=block.find('\n', nStart);
                    if(nEnd==string::npos) nEnd=block.size();
                    bookingName=block.substr(nStart, nEnd - nStart);
                }

                bookingPhone=ph;

                size_t roomPos=block.find("Room: ");
                if(roomPos!=string::npos){
                    size_t rStart=roomPos + 6;
                    size_t rEnd=block.find('\n', rStart);
                    if(rEnd==string::npos) rEnd=block.size();
                    oldRoomNo=stoi(block.substr(rStart, rEnd - rStart));
                }

                cout<<"Enter new room number to book: ";
                int newRoomNo;
                cin>>newRoomNo;

                
                int newRoomIndex=-1;
                for(int i=0; i<rooms.size(); ++i){
                    if(rooms[i].number==newRoomNo){
                        newRoomIndex=i;
                        break;
                    }
                }

                if(newRoomIndex!=-1){
                    Room newRoomDetails = rooms[newRoomIndex]; //to get the new room's details

                    //new records
                    fout<<"Name: "<<bookingName<<"\n"
                         <<"Phone: "<<bookingPhone<<"\n"
                         <<"Room: "<<newRoomDetails.number<<"\n"
                         <<"Room Price: "<<newRoomDetails.price<<"\n"
                         <<"Room Type: "<<newRoomDetails.type<<"\n"
                         <<"Room Facilities: "<<newRoomDetails.facilities<<"\n"
                         <<"-----------------------------\n";

                    //remove the new room from the list of available rooms
                    rooms.erase(rooms.begin() + newRoomIndex);

                    //we need to find old room details from the booking block to restore it
                    float oldRoomPrice=0;
                    string oldRoomType, oldRoomFacilities;
                    size_t pricePos=block.find("Room Price: ");
                    if(pricePos!=string::npos){
                        size_t pStart=pricePos + 12;
                        size_t pEnd=block.find('\n', pStart);
                        if(pEnd==string::npos) pEnd=block.size();
                        oldRoomPrice=stof(block.substr(pStart, pEnd - pStart));
                    }
                    size_t typePos=block.find("Room Type: ");
                    if(typePos!=string::npos) {
                        size_t tStart=typePos + 11;
                        size_t tEnd=block.find('\n', tStart);
                        if(tEnd==string::npos) tEnd=block.size();
                        oldRoomType=block.substr(tStart, tEnd - tStart);
                    }
                    size_t facPos=block.find("Room Facilities: ");
                    if(facPos!=string::npos) {
                        size_t fStart=facPos + 16;
                        size_t fEnd=block.find('\n', fStart);
                        if(fEnd==string::npos) fEnd = block.size();
                        oldRoomFacilities=block.substr(fStart, fEnd - fStart);
                    }

                    if(oldRoomNo != 0){
                        //add the old room back to the list of available rooms
                        rooms.push_back(Room(oldRoomNo, oldRoomPrice, oldRoomType, oldRoomFacilities));
                    }

                    saveRoomsToFile(rooms); // Save all changes to rooms.txt
                    cout<<"Booking updated successfully!\n";

                }else{ //agr naya room available nahi hai
                    cout<<"Room "<<newRoomNo<<" is not available. Update failed.\n";
                    fout<<block; //write the original... unchanged booking back to the temp file
                }
            }else{
                fout<<block; //not the booking we're looking for.. so just copy it to the temp file
            }
            block.clear();
            ph.clear();
        }
    }

    fin.close();
    fout.close();

    if(found){
        remove("bookings.txt");
        rename("temp.txt", "bookings.txt");
    }else{
        cout<<"No booking found for this phone number.\n";
        remove("temp.txt");
    }
}


void viewMyBookings(){
    string phone;
    cout<<"\nEnter your phone number to view your bookings: ";
    cin>>phone;
    while(phone.length() != 10){
        cout<<"Invalid! Phone number must be exactly 10 digits.\n";
        cout<<"Enter again: ";
        cin>>phone;
    }

    ifstream fin("bookings.txt");
    if(!fin){
        cout<<"No booking records found yet.\n";
        return;
    }

    //this function simply reads through the bookings file and prints any matching records.
    string line;
    bool found=false;

    string block;

     while(getline(fin,line)){
        if(line.empty()) continue;
        block+=line + "\n";
        if(line.find("-----------------------------") != string::npos) {
            string ph;
            size_t pos=block.find("Phone: ");
            if(pos!=string::npos){
                size_t start=pos + 7;
                size_t end=block.find('\n', start);
                if(end==string::npos) end=block.size();
                ph=block.substr(start, end - start);
                ph.erase(remove(ph.begin(), ph.end(), '\r'), ph.end());
                ph.erase(remove(ph.begin(), ph.end(), '\n'), ph.end());
            }

            //agr user ka entered phone no. match kr jata hai to us booking ko print krdo
            if(ph == phone){
                if(!found){
                    cout<<"\n=== Your Bookings ===\n";
                }
                cout<<block<<"\n";
                found=true; //mark that we found at least one booking
            }
            block.clear();
        }
    }

    fin.close();

    if(!found){
        cout<<"No bookings found for this phone number.\n";
    }
}
