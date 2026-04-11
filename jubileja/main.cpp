#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct darbinieks {
    string vards;
    string uzvards;
    // datums;
};

int main() {

    ifstream input("anniversary.in");
    ofstream output("anniversary.out");
    
    char temp = 'X';
    char cmd;

    while (input >> cmd) {
        if (cmd == 'P') {
            string vards;
            string uzvards; 
            string date;

            // need to figure out how to get date
            
            input >> vards >> uzvards >> date;
            cout << vards << " " << uzvards << " " << date << endl;
        } else if (cmd == 'D') {
            string date; 
            input >> date;
            cout << "D " << date << endl; 
        } else if (cmd == 'X') break;
    }
    
    input.close();
    output.close();
    return 0;
}