#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

static int p = 0;

class Bus {
    char busn[5], driver[10], arrival[5], depart[5], from[10], to[10];
    char seat[8][4][10]; // 8 rows x 4 columns

public:
    void install();
    void allotment();
    void empty();
    void show();
    void avail();
    void position(int i);
} bus[10]; // Can have up to 10 buses

void vline(char ch) {
    for (int i = 0; i < 80; i++)
        cout << ch;
    cout << endl;
}

void Bus::install() {
    cout << "Enter bus no: ";
    cin >> bus[p].busn;
    cout << "Enter Driver's name: ";
    cin >> bus[p].driver;
    cout << "Arrival time: ";
    cin >> bus[p].arrival;
    cout << "Departure time: ";
    cin >> bus[p].depart;
    cout << "From: ";
    cin >> bus[p].from;
    cout << "To: ";
    cin >> bus[p].to;
    bus[p].empty();
    p++;
}

void Bus::allotment() {
    int seatNo;
    char number[5];

    cout << "Enter bus no: ";
    cin >> number;

    int n;
    for (n = 0; n < p; n++) {
        if (strcmp(bus[n].busn, number) == 0)
            break;
    }

    if (n == p) {
        cout << "Enter correct bus no.\n";
        return;
    }

    cout << "Enter seat number (1–32): ";
    cin >> seatNo;

    if (seatNo < 1 || seatNo > 32) {
        cout << "Invalid seat number. Only 32 seats available.\n";
        return;
    }

    int row = (seatNo - 1) / 4;
    int col = (seatNo - 1) % 4;

    if (strcmp(bus[n].seat[row][col], "Empty") == 0) {
        cout << "Enter passenger's name: ";
        cin >> bus[n].seat[row][col];
    } else {
        cout << "Seat already reserved.\n";
    }
}

void Bus::empty() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 4; j++)
            strcpy(seat[i][j], "Empty");
}

void Bus::show() {
    char number[5];
    cout << "Enter bus no: ";
    cin >> number;

    int n;
    for (n = 0; n < p; n++) {
        if (strcmp(bus[n].busn, number) == 0)
            break;
    }

    if (n == p) {
        cout << "Enter correct bus no.\n";
        return;
    }

    vline('*');
    cout << "Bus no: " << bus[n].busn
         << "\nDriver: " << bus[n].driver
         << "\nArrival: " << bus[n].arrival
         << "\nDeparture: " << bus[n].depart
         << "\nFrom: " << bus[n].from
         << "\nTo: " << bus[n].to << endl;
    vline('*');

    bus[n].position(n);

    for (int i = 0, seatNum = 1; i < 8; i++) {
        for (int j = 0; j < 4; j++, seatNum++) {
            if (strcmp(bus[n].seat[i][j], "Empty") != 0)
                cout << "Seat " << seatNum << " reserved for " << bus[n].seat[i][j] << endl;
        }
    }
}

void Bus::position(int n) {
    int s = 1, emptyCount = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            cout.width(5);
            cout.fill(' ');
            cout << s << ".";
            cout.width(10);
            cout.fill(' ');
            cout << bus[n].seat[i][j];
            s++;
        }
        cout << endl;
    }

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 4; j++)
            if (strcmp(bus[n].seat[i][j], "Empty") == 0)
                emptyCount++;

    cout << "\nTotal empty seats: " << emptyCount << " in Bus No: " << bus[n].busn << endl;
}

void Bus::avail() {
    for (int n = 0; n < p; n++) {
        vline('*');
        cout << "Bus no: " << bus[n].busn
             << "\nDriver: " << bus[n].driver
             << "\nArrival: " << bus[n].arrival
             << "\nDeparture: " << bus[n].depart
             << "\nFrom: " << bus[n].from
             << "\nTo: " << bus[n].to << endl;
        vline('*');
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n\nBus Reservation System Menu\n";
        cout << "1. Install\n";
        cout << "2. Reservation\n";
        cout << "3. Show\n";
        cout << "4. Buses Available\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bus[p].install(); break;
            case 2: bus[p].allotment(); break;
            case 3: bus[0].show(); break;
            case 4: bus[0].avail(); break;
            case 5: exit(0);
            default: cout << "Invalid choice!\n";
        }
    }

    return 0;
}
