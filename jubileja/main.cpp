#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Darbinieks {
    string vards;
    string uzvards;
    int day;
    int month;
    int year;
};


int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

long long dateToTotalDays(int d, int m, int y) {
    long long total = 0;

    total += (long long)y * 365;

    for (int i = 0; i < m - 1; i++) {
        total += monthDays[i];
    }

    total += d;

    return total;
}
int main() {

    ifstream input("anniversary.in");
    ofstream output("anniversary.out");
    
    char temp = 'X';
    char cmd, dot;
    int month, day, year;

    Darbinieks masivs[364];

    while (input >> cmd) {
        if (cmd == 'P') {
            string vards;
            string uzvards; 
            int vieta = 0;
            
            input >> vards >> uzvards >> day >> dot >> month >> dot >> year;
            long long time = dateToTotalDays(day, month, year);

            for (int i = 0; i < month - 1; i++) {
                vieta += monthDays[i];
            }
            vieta += day;
            Darbinieks darbinieks = {vards, uzvards, day, month, year};

            for (int i = 1; i < 365; i++) {
                if (i == vieta) {
                    masivs[i] = darbinieks;
            }

            // cout << masivs.vards << " " << masivs.year << endl;
            }
            // cout << darbinieks.vards << " " << darbinieks.year << endl;
            // cout << vards << " " << uzvards << " " << time << endl;
        } else if (cmd == 'D') {

            input >> day >> dot >> month >> dot >> year;
            long long time = dateToTotalDays(day, month, year);
            
            // cout << time << endl;
        } else if (cmd == 'X') break;
    }
    
    input.close();
    output.close();
    return 0;
}