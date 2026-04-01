#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;


const int TABLE_SIZE = 20011; 

struct recenzents {
    string vards;
    int pseidonimi[50];
    int skaits = 0;
    recenzents* next = nullptr; // Kolīzijām vārdu tabulā
};

// struktūra prieks atras meklesanas
struct pseidonimaMezgla {
    int vertiba;
    recenzents* ipasnieks;      // Norāde uz galveno objektu (ietaupa atmiņu)
    pseidonimaMezgla* next = nullptr; // Kolīzijām skaitļu tabulā
};

// Divas hash tabulas
recenzents* vardsTabula[TABLE_SIZE];
pseidonimaMezgla* skaitlisTabula[TABLE_SIZE];

// Hash funkcija vārdam (string)
int hashVardam(string s) {
    unsigned int h = 0;
    for (char c : s) h = h * 31 + c;
    return h % TABLE_SIZE;
}

// Hash funkcija pseidonīmam (int)
int hashSkaitlim(int x) {
    return (x < 0 ? -x : x) % TABLE_SIZE;
}

void insert(string vards, int* jauniPseidonimi, int n) {
    int vIdx = hashVardam(vards);
    recenzents* r = vardsTabula[vIdx];

    // 1. Pārbaudām, vai recenzents jau eksistē
    while (r != nullptr) {
        if (r->vards == vards) break;
        r = r->next;
    }

    // 2. Ja neeksistē, izveidojam jaunu
    if (r == nullptr) {
        r = new recenzents;
        r->vards = vards;
        r->next = vardsTabula[vIdx];
        vardsTabula[vIdx] = r;
    }

    // 3. Pievienojam jaunos pseidonīmus gan recenzentam, gan skaitļu tabulai
    for (int i = 0; i < n; i++) {
        int ps = jauniPseidonimi[i];
        
        // Pievienojam recenzenta masīvā (ja ir vieta)
        if (r->skaits < 50) {
            r->pseidonimi[r->skaits++] = ps;
        }

        // Pievienojam skaitļu hash tabulā ātrai "L" meklēšanai
        int sIdx = hashSkaitlim(ps);
        pseidonimaMezgla* pm = new pseidonimaMezgla;
        pm->vertiba = ps;
        pm->ipasnieks = r; // Norāde uz to pašu recenzentu
        pm->next = skaitlisTabula[sIdx];
        skaitlisTabula[sIdx] = pm;
    }
}

void lookup(int sk) {
    int sIdx = hashSkaitlim(sk);
    pseidonimaMezgla* temp = skaitlisTabula[sIdx];

    while (temp != nullptr) {
        if (temp->vertiba == sk) {
            cout << temp->ipasnieks->vards << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "NOT FOUND" << endl;
}
recenzents* vardsTabula[10007];
pseidonimaMezgla* skaitlisTabula[10007];
// const int TABLE_SIZE = 10000;

// hash funkcija
int hashFunction(string vards) {
    int hash = 0;
    for (char c : vards) hash += c;
    return hash % TABLE_SIZE;
}

void pievienot(string vards, int skaitlis) {
    int idx = hashFunction(vards);
    recenzents* temp = tabula[idx];

    // Meklējam, vai jau ir
    while (temp != nullptr) {
        if (temp->vards == vards) {
            if (temp->pseidonimuSkaits < 50) {
                temp->pseidonimi[temp->pseidonimuSkaits++] = skaitlis;
            }
            return;
        }
        temp = temp->next;
    }

    // Ja nav, taisām jaunu
    recenzents* jaunais = new recenzents;
    jaunais->vards = vards;
    jaunais->pseidonimi[jaunais->pseidonimuSkaits++] = skaitlis;
    jaunais->next = tabula[idx]; // Pieliek saraksta sākumā
    tabula[idx] = jaunais;
}
void paraditPseidonimus(string vards) {
    int idx = hashFunction(vards);
    recenzents* temp = tabula[idx];

    while (temp != nullptr) {
        if (temp->vards == vards) {
            cout << vards << " pseidonimi ir: ";
            for (int i = 0; i < temp->pseidonimuSkaits; i++) {
                cout << temp->pseidonimi[i] << " ";
            }
            cout << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Recenzents netika atrasts." << endl;
}

int main() {

    ifstream input("reviewers.in");
    ofstream output("reviewers.out");

    
    string vards; // recenzenta vards
    int pseidonimuSkaits; 
    int pseidonimi[50];
    int pseidonims;
    string line; // lai saprastu kad fails beidzas

    // unordered_map<string, recenzents>* recenzenti = new unordered_map<string, recenzents>[10000];


    char darbiba; // insert or delete or look
    

    while (input) {
        input >> darbiba;
        // cout << darbiba;
        if (darbiba == 73){ // INSERT
            input >> vards >> pseidonimuSkaits;
            for (int i = 1; i<=pseidonimuSkaits;i++){
                input >> pseidonims;
                pievienot(vards, pseidonims);
            }
            paraditPseidonimus(vards);
            output << "ok" << endl;

            // vajag vel no?
        }
        else if (darbiba == 76) { // LOOK UP
            cout << "meklejam" << pseidonims << endl;
            input >> pseidonims; 
            
        }
        // else if (darbiba == 68) { // DELETE
        //     cout << "daram delete" << endl;
        // }
        // input >> darbiba;
    }

    
    // int pseidonims;
    // if (darbiba == 73){
    //     input >> darbiba >> vards >> arrayCount;
    //     cout << vards;
    //     cout << "Insert darbiba" << endl;
    //     for (int i = 1; i <= arrayCount;i++) {
    //         recenzents r;
    //         input >> pseidonims;
    //         // r.
    //         // map = 
    //         cout << vards << ": " << pseidonims << endl;

    //         // array.push(map);
    //     }
    // }

    // delete recenzenti;
    input.close();
    output.close();
    return 0;
}
