#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Booking {
    int bookingID;
    string name;
    string flightNo;
    string date;
    string seatNo;
};

struct Index {
    int bookingID;
    long pos;
};

vector<Index> indexTable;

// Load index
void loadIndex() {
    indexTable.clear();
    ifstream file("index.txt");

    Index temp;
    while(file >> temp.bookingID >> temp.pos) {
        indexTable.push_back(temp);
    }
    file.close();
}

// Save index
void saveIndex() {
    ofstream file("index.txt");

    for(auto &i : indexTable) {
        file << i.bookingID << " " << i.pos << endl;
    }
    file.close();
}

// Add booking
void addBooking() {
    Booking b;

    cout << "Enter BookingID Name FlightNo Date SeatNo:\n";
    cin >> b.bookingID >> b.name >> b.flightNo >> b.date >> b.seatNo;

    ofstream file("data.txt", ios::app);
    long pos = file.tellp();

    file << b.bookingID << " "
         << b.name << " "
         << b.flightNo << " "
         << b.date << " "
         << b.seatNo << endl;

    file.close();

    indexTable.push_back({b.bookingID, pos});

    sort(indexTable.begin(), indexTable.end(),
         [](Index a, Index b) {
             return a.bookingID < b.bookingID;
         });

    saveIndex();

    cout << "Booking Added!\n";
}

// Search booking
void searchBooking() {
    int id;
    cout << "Enter Booking ID: ";
    cin >> id;

    for(auto &i : indexTable) {
        if(i.bookingID == id) {
            ifstream file("data.txt");
            file.seekg(i.pos);

            Booking b;
            file >> b.bookingID >> b.name >> b.flightNo
                 >> b.date >> b.seatNo;

            cout << "\nBooking Found:\n";
            cout << b.bookingID << " "
                 << b.name << " "
                 << b.flightNo << " "
                 << b.date << " "
                 << b.seatNo << endl;

            file.close();
            return;
        }
    }

    cout << "Booking Not Found!\n";
}

// Display all bookings
void displayAll() {
    ifstream file("data.txt");
    Booking b;

    cout << "\nAll Bookings:\n";

    while(file >> b.bookingID >> b.name >> b.flightNo
               >> b.date >> b.seatNo) {
        cout << b.bookingID << " "
             << b.name << " "
             << b.flightNo << " "
             << b.date << " "
             << b.seatNo << endl;
    }

    file.close();
}

int main() {
    loadIndex();

    int choice;

    do {
        cout << "\n1. Add Booking\n2. Search Booking\n3. Display All\n4. Exit\nEnter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addBooking(); break;
            case 2: searchBooking(); break;
            case 3: displayAll(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice\n";
        }

    } while(choice != 4);

    return 0;
}
