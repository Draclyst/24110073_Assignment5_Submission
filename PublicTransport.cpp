#include <iostream>
#include <string>
using namespace std;

class Bus{
    protected:
        string route;
        int capacity;
        bool status;
        string timeStatus;
    public:
    Bus(string r, int c, bool s): route(r), capacity(c), status(s) {}
    virtual double calculateTravelTime(double distance, double speed) { //calculates travel time in hours
        if(speed <= 0) {
            cout<<"Speed cannot be < 0"<<endl;
            return -1;
        }
        return distance / speed;
    }
    virtual double calculateOccupancy(int currentPassengers) { 
        if(capacity <= 0) {
            cout<<"Capacity cannot be < 0"<<endl;
            return -1;
        }
        return static_cast<double>(currentPassengers) / capacity;
    }
    void showOccupancy(int currentPassengers) {
        double occupancy = calculateOccupancy(currentPassengers);
        if (occupancy >= 0) {
            cout << "Occupancy for " << route << ": " << occupancy * 100 << "%" << endl;
        }
    }
    bool isInService() {
        return status;
    }
    string getTimeStatus() {
        return timeStatus;
    }
    virtual void displayInfo() { //includes new functionality status
        cout << "Normal Bus - Route: " << route << ", Capacity: " << capacity << ", Status: " << (status ? "In Service" : "Out of Service") << ", Time Status: " << timeStatus << endl;
    }
    void setTimeStatus(string ts){
        timeStatus = ts;
        if (!status) {
            timeStatus = "N/A";
        } else {
            timeStatus = ts;
        }
    }
    void TravelTime(double distance, double speed) {
        double time = calculateTravelTime(distance, speed);
        if (time >= 0) {
            cout<<"Travel time for " << route << ": " << time << " hours." << endl;
        }
    }
};

class ExpressBus : public Bus {
    private:
    double speed; //higher speed for express
    public:
    ExpressBus(string r, int c, bool s, double sp): Bus(r, c, s), speed(sp) {}
    double calculateTravelTime(double distance) { 
        if (speed <= 0) {
            cout<<"Speed cannot be < 0"<<endl;
        }
        return distance / speed;
    }
    double calculateOccupancy(int currentPassengers) { //new method
        if (capacity <= 0) {
            cout << "Capacity cannot be < 0" << endl;
            return -1;
        }
        return (static_cast<double>(currentPassengers) / capacity) * 100;
    }
    void showOccupancy(int currentPassengers) { //new method
        double occupancy = calculateOccupancy(currentPassengers);
        if (occupancy >= 0) {
            cout << "Occupancy for " << route << ": " << occupancy << "%" << endl;
        }
    }
    void displayInfo() {
        cout << "Express Bus - Route: " << route << ", Capacity: " << capacity << ", Speed: " << speed << " km/h, Status: " << (status ? "In Service" : "Out of Service") << ", Time Status: " << timeStatus << endl;
    }
    void TravelTime(double distance) {
        double time = calculateTravelTime(distance);
        if (time >= 0) {
            cout << "Travel time for " << route << ": " << time << " hours." << endl;
        }
    }
};
class Passenger{
    private:
    string name;
    int age;
    int ID;
    bool bookedTicket;
    string busType;
    public:
    Passenger(string n, int a, int id, bool bt, string btype): name(n), age(a), ID(id), bookedTicket(bt), busType(btype) {}
    bool bookTicket(string btype) {
        if(!bookedTicket) {
            bookedTicket = true;
            busType = btype;
            cout << "Passenger " << name << " has a booked ticket for " << busType<< endl;
            return true;
        } else {
            cout << "Already booked a ticket for " << busType<< endl;
        } return false;
    }
    bool cancelTicket() {
        if(bookedTicket) {
            bookedTicket = false;
            cout<< name << " cancelled the ticket for " << busType<< endl;
            return true;
        }
        else {
            cout << "No ticket to cancel." <<endl;
            return false;
        }
    }
    bool isTicketBooked(){
        return bookedTicket;
    }
    void displayInfo() {
        cout << "Passenger Name: " << name << ", Age: " << age << ", ID: " << ID << ", Ticket Booked: " << (bookedTicket ? "Yes" : "No") << ", Bus Type: " << busType << endl;
    }
};
class Schedule{
    public:
    string vehicleID;
    string arrivalTime;
    string departureTime;
    Schedule(string vID, string at, string dt): vehicleID(vID), arrivalTime(at), departureTime(dt) {}
    void displayInfo() {
        cout <<"ID: " << vehicleID << ", Arrival: " <<arrivalTime <<", Departure: " << departureTime << endl;
    }
};
class Station{
    private:
    string name;
    string location;
    string type;
    public:
    Station(string n, string l, string t): name(n), location(l), type(t) {}
    void displayInfo() {
        cout << "Station Name: " << name << ", Location: " << location << ", Type: " << type << endl;
    }
};

int main(){
    Station st1("Front Gate Station", "HCMUTE", "Bus/Express");
    st1.displayInfo();
    Bus bus1("Route X", 50, true);
    bus1.setTimeStatus("Delayed");
    bus1.displayInfo();
    Schedule sch1("Bus1", "10:00 AM", "10:30 AM");
    sch1.displayInfo();
    bus1.TravelTime(100, 40); // 100 km at 40 km/h
    bus1.showOccupancy(25);
    ExpressBus ebus("Route Y", 30, false, 60);
    ebus.setTimeStatus("On time");
    ebus.displayInfo();
    ExpressBus ebus2("Route Z", 30, true, 80);
    ebus2.setTimeStatus("On time");
    ebus2.displayInfo();
    Schedule sch2("ExpressBus2", "3:00 PM", "3:20 PM");
    sch2.displayInfo();
    ebus2.TravelTime(160);
    ebus2.showOccupancy(10);
    Passenger p1("Charlie", 28, 123, false, "Express Bus");
    p1.displayInfo();
    p1.bookTicket("Express");
    p1.displayInfo();
    p1.cancelTicket();
    Passenger p2("Phuc", 19, 240, true, "Bus");
    p2.displayInfo();
    return 0;
}
