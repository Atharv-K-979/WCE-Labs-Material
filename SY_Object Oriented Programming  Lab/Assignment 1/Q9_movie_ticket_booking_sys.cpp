#include <iostream>
#include <string>
using namespace std;

class MovieTicket {
private:
    string movieName;
    int seatNumber;
    double ticketPrice;

public:
    void bookTicket() {
        cout << "Enter Movie Name: ";
        cin.ignore();
        getline(cin, movieName);
        cout << "Enter Seat Number: ";
        cin >> seatNumber;
        cout << "Enter Ticket Price: ";
        cin >> ticketPrice;
    }

    void displayBookingDetails() {
        cout << "\nTicket Details\n";
        cout << "Movie Name: " << movieName << "\n";
        cout << "Seat Number: " << seatNumber << "\n";
        cout << "Ticket Price: " << ticketPrice << "\n";
    }
};

int main() {
    MovieTicket ticket;
    ticket.bookTicket();
    ticket.displayBookingDetails();
    return 0;
}
