#include <iostream>
#include <fstream>
#include <map>
using namespace std;

int main() {
    ifstream input("morse.in");
    ofstream output("morse.out");

   map<string, char> vardnica = {
    {".-", 'A'},
    {"-...", 'B'},
    {"-.-.", 'C'},
    {"-..", 'D'},
    {".", 'E'},
    {"..-.", 'F'},
    {"--.", 'G'},
    {"....", 'H'},
    {"..", 'I'},
    {".---", 'J'},
    {"-.-", 'K'},
    {".-..", 'L'},
    {"--", 'M'},
    {"-.", 'N'},
    {"---", 'O'},
    {".--.", 'P'},
    {"--.-", 'Q'},
    {".-.", 'R'},
    {"...", 'S'},
    {"-", 'T'},
    {"..-", 'U'},
    {"...-", 'V'},
    {".--", 'W'},
    {"-..-", 'X'},
    {"-.--", 'Y'},
    {"--..", 'Z'},
    {"-----", '0'},
    {".----", '1'},
    {"..---", '2'},
    {"...--", '3'},
    {"....-", '4'},
    {".....", '5'},
    {"-....", '6'},
    {"--...", '7'},
    {"---..", '8'},
    {"----.", '9'},
    {".-.-.-", '.'},
    {"--..--", ','},
    {"---...", ':'},
    {"..--..", '?'},
    {"-....-", '-'},
    {"-..-.", '/'},
    {".----.", ' '}, // Tukšums
    {"|", '\n'}      // Simbola beigas
};

    // string word;
    // input >> a;
    char it;
    input >> it;
    string final;
    while (input) {
        string word;
        while (it != '|') {
            word += it;
            input >> it;
        }
        input >> it;
        for (auto a : vardnica){
            if (a.first == word){
                // cout << a.second;
                final += a.second;
            }
            else if (word == "!") {
                final += "!"; 
            }
            // cout << it.first << ": " << it.second << endl;
        }
            
        // cout << word << endl;
    }
    cout << final;
    output << final;
}