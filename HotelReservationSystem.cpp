#include<iostream>
#include<vector>
using namespace std;
//room class jo room ki details show krega
class Room{
    int number;
    float price;
    string type,facilities;

    Room(int n,float p,string t,string f){
        number=n;
        price=p;
        type=t;
        facilities=f;
    }
    void display(){
        cout<<"Room "<<number<<" ("<<type<<") - Rs."<<price<<endl<<"Facilities- "<<facilities;
    }
};
//view room function
void viewRooms(const vector<Room>&rooms){
    
}
//book room function
void vookRoom(const vector<Room>&rooms){
    
}
//cancel booking function
void cancelBooking(const vector<Room>&rooms){
    
}
//update booking function
void updateBooking(const vector<Room>&rooms){
    
}
//viewMy booking function
void viewMyBooking(const vector<Room>&rooms){
    
}



int main(){
    //list of rooms available
    vector<Room>rooms={
        Room{101,"Single",1500,"AC, TV & Breakfast"},
        Room{102,"Double",3000,"AC, Wifi, TV & Breakfast"},
        Room{103,"Suite",4500,"AC, Wifi, TV, Breakfast & more luxury facilities like Jacuzzi and Sauna"}
    };
    //pehle user ko welcome krna hai aur uske baad pucho ki kya service chahiye
    cout<<endl<<endl;
    cout<<"-----------------------------"<<endl<<"  WELCOME TO PARADISE HOTEL"<<endl<<"-----------------------------"<<endl<<endl;
    cout<<"Thankyou for choosing us!"<<endl<<"What services you would like to consider:"<<endl<<endl;
    cout<<"1. View Rooms"<<"\n"<<"2. Book Room"<<"\n"<<"3. Cancel Booking"<<"\n"<<"4. Update Bookings"<<"\n"<<"5. View Bookings"<<"\n"<<"6. Exit";
    //ab input lo ki user konsi service lena chahta hai
    int n;
    cin>>n;
    switch(n){
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
            cout<<"Thank you, See you again!";
            break;
        default:
            cout<<"Invalid Entry, Try again!";
    }
}