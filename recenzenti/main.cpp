#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int TABLE_SIZE = 20011;

struct Recenzents {
    string vards;
    int pseidonimi[50];
    int skaits = 0;
    Recenzents* next = nullptr;
};

struct PseidonimaMezgla {
    int vertiba;
    Recenzents* ipasnieks;
    PseidonimaMezgla* next = nullptr;
};

Recenzents* vardsTabula[TABLE_SIZE] = {nullptr};
PseidonimaMezgla* skaitlisTabula[TABLE_SIZE] = {nullptr};

// Hash funkcijas
int hashVardam(string vards) {
    unsigned int hashSumma = 0;
    for (char c : vards) hashSumma = hashSumma * 31 + c;
    return hashSumma % TABLE_SIZE;
}

int hashSkaitlim(int skaitlis) {
    unsigned int pozitivsSkaitlis = (skaitlis < 0) ? -skaitlis : skaitlis;
    return pozitivsSkaitlis % TABLE_SIZE;
}

// parbaude vai pseidonims jau pieder sim recenzentam
bool jauPieder(Recenzents* r, int pseidonims) {
    if (!r) return false;
    for (int i = 0; i < r->skaits; i++) {
        if (r->pseidonimi[i] == pseidonims) return true;
    }
    return false;
}

// lai atrastu, kam pieder pseidonims
Recenzents* atrastIpasnieku(int pseidonims) {
    int index = hashSkaitlim(pseidonims);
    PseidonimaMezgla* temp = skaitlisTabula[index];
    while (temp) {
        if (temp->vertiba == pseidonims) return temp->ipasnieks;
        temp = temp->next;
    }
    return nullptr;
}

void insert(string vards, int daudzums, ifstream& in, ofstream& out) {
    int pagaiduMasivs[100];
    for (int i = 0; i < daudzums; i++) in >> pagaiduMasivs[i];

    int vardaIndekss = hashVardam(vards);
    Recenzents* r = vardsTabula[vardaIndekss];
    while (r && r->vards != vards) r = r->next;

    // validacija
    int jauniUnikaliPseidonimi = 0;
    for (int i = 0; i < daudzums; i++) {
        Recenzents* ipasnieks = atrastIpasnieku(pagaiduMasivs[i]);
        if (ipasnieks && ipasnieks != r) { 
            out << "no" << endl;
            return; 
        }
        
        // parbaudam vai sis ir jauns pseidonims
        bool dublikatsIevade = false;
        for (int j = 0; j < i; j++) if (pagaiduMasivs[i] == pagaiduMasivs[j]) dublikatsIevade = true;
        
        if (!dublikatsIevade && !jauPieder(r, pagaiduMasivs[i])) jauniUnikaliPseidonimi++;
    }

    int kopskaits = (r ? r->skaits : 0) + jauniUnikaliPseidonimi;
    if (kopskaits > 50) { 
        out << "no" << endl; 
        return; 
    }

    // izpilde
    if (!r) {
        r = new Recenzents;
        r->vards = vards;
        r->next = vardsTabula[vardaIndekss];
        vardsTabula[vardaIndekss] = r;
    }

    for (int i = 0; i < daudzums; i++) {
        if (!jauPieder(r, pagaiduMasivs[i])) {
            r->pseidonimi[r->skaits++] = pagaiduMasivs[i];
            int skaitlaIndekss = hashSkaitlim(pagaiduMasivs[i]);
            PseidonimaMezgla* jaunsMezgls = new PseidonimaMezgla;
            jaunsMezgls->vertiba = pagaiduMasivs[i];
            jaunsMezgls->ipasnieks = r;
            jaunsMezgls->next = skaitlisTabula[skaitlaIndekss];
            skaitlisTabula[skaitlaIndekss] = jaunsMezgls;
        }
    }
    out << "ok" << endl;
}

void remove(int key, ofstream& out) {
    int skaitlaIndekss = hashSkaitlim(key);
    PseidonimaMezgla* mezglsSkTabula = skaitlisTabula[skaitlaIndekss];
    Recenzents* r = nullptr;
    while (mezglsSkTabula) {
        if (mezglsSkTabula->vertiba == key) { 
            r = mezglsSkTabula->ipasnieks; 
            break; 
        }
        mezglsSkTabula = mezglsSkTabula->next;
    }

    if (!r) { 
        out << "no" << endl; 
        return; 
    }

    // izdzesam visus pseidonimus no skaitļu tabulas
    for (int i = 0; i < r->skaits; i++) {
        int konkretaisPseidonims = r->pseidonimi[i];
        int pasreizejaIndekss = hashSkaitlim(konkretaisPseidonims);
        PseidonimaMezgla *pasreizejais = skaitlisTabula[pasreizejaIndekss];
        PseidonimaMezgla *ieprieksejais = nullptr;        
        while (pasreizejais) {
            if (pasreizejais->vertiba == konkretaisPseidonims) {
                if (!ieprieksejais) skaitlisTabula[pasreizejaIndekss] = pasreizejais->next;
                else ieprieksejais->next = pasreizejais->next;
                delete pasreizejais;
                break;
            }
            ieprieksejais = pasreizejais; 
            pasreizejais = pasreizejais->next;
        }
    }

    // izdzesam no vardu tabulas
    int vardaIndekss = hashVardam(r->vards);
    Recenzents *pasreizejsVards = vardsTabula[vardaIndekss];
    Recenzents *ieprieksejsVards = nullptr;

    while (pasreizejsVards) {
        if (pasreizejsVards->vards == r->vards) {
            if (!ieprieksejsVards) vardsTabula[vardaIndekss] = pasreizejsVards->next;
            else ieprieksejsVards->next = pasreizejsVards->next;
            delete pasreizejsVards;
            out << "ok" << endl;
            return;
        }
        ieprieksejsVards = pasreizejsVards;
        pasreizejsVards = pasreizejsVards->next;
    }
}

int main() {
    ifstream in("reviewers.in");
    ofstream out("reviewers.out");


    char cmd;
    while (in >> cmd) {
        if (cmd == 'I') {
            string vards; 
            int skaits;
            in >> vards >> skaits;
            insert(vards, skaits, in, out);
        } else if (cmd == 'D') {
            int pseidonims; 
            in >> pseidonims;
            remove(pseidonims, out);
        } else if (cmd == 'L') {
            int pseidonims; 
            in >> pseidonims;
            Recenzents* r = atrastIpasnieku(pseidonims);
            if (r) out << r->vards << endl;
            else out << "no" << endl;
        }
    }
    return 0;
}