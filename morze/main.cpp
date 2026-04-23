#include <iostream>
#include <fstream>
#include <map>
using namespace std;

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
        {".----.", ' '},
        {"|", ' '}
    };

char tulkojums(string word, map<string, char>& vardnica) {
    if (word.empty()) return 0;

    if (vardnica.count(word)) {
        return vardnica[word];
    }

    return '!';
}

int main() {
    ifstream input("morse.in");
    ofstream output("morse.out");
    
    string final = "";
    string word = "";
    char it;

    while (input.get(it)) {
        if (it == '|') {
            if (!word.empty()) {
                final += tulkojums(word, vardnica);
                word = "";
            }
        } else if (it == '.' || it == '-') {
            word += it;
        }
    }
    
    if (!word.empty()) {
        final += '!'; 
    }

    cout << final;
    output << final;

    return 0;
}