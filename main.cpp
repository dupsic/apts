#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int TABLE_SIZE = 20011; // Pirmskaitlis vārdiem un skaitļiem

struct Recenzents {
    string vards;
    int pseidonimi[50];
    int skaits = 0;
    Recenzents* next = nullptr; // Kolīzijām vārdu tabulā
};

struct PseidonimaMezgla {
    int vertiba;
    Recenzents* ipasnieks;
    PseidonimaMezgla* next = nullptr; // Kolīzijām skaitļu tabulā
};

Recenzents* vardsTabula[TABLE_SIZE] = {nullptr};
PseidonimaMezgla* skaitlisTabula[TABLE_SIZE] = {nullptr};

// Hash funkcijas
int hashV(string s) {
    unsigned int h = 0;
    for (char c : s) h = h * 31 + c;
    return h % TABLE_SIZE;
}

int hashS(int x) {
    unsigned int ux = (x < 0) ? -x : x;
    return ux % TABLE_SIZE;
}

// Funkcija, lai pārbaudītu, vai pseidonīms jau pieder šim recenzentam
bool jauIrSim(Recenzents* r, int ps) {
    if (!r) return false;
    for (int i = 0; i < r->skaits; i++) {
        if (r->pseidonimi[i] == ps) return true;
    }
    return false;
}

// Funkcija, lai atrastu, kam pieder pseidonīms
Recenzents* kuraPseidonims(int ps) {
    int idx = hashS(ps);
    PseidonimaMezgla* temp = skaitlisTabula[idx];
    while (temp) {
        if (temp->vertiba == ps) return temp->ipasnieks;
        temp = temp->next;
    }
    return nullptr;
}

void insert(string vards, int n, ifstream& in, ofstream& out) {
    int vPs[100]; // Pagaidu masīvs nolasīšanai
    for (int i = 0; i < n; i++) in >> vPs[i];

    int vIdx = hashV(vards);
    Recenzents* r = vardsTabula[vIdx];
    while (r && r->vards != vards) r = r->next;

    // 1. Validācija
    int jauniUnikali = 0;
    for (int i = 0; i < n; i++) {
        Recenzents* ipasnieks = kuraPseidonims(vPs[i]);
        if (ipasnieks && ipasnieks != r) { out << "no" << endl; return; }
        
        // Pārbaudām, vai šis ir jauns pseidonīms (nav dublikāts ievadē vai esošajos)
        bool dublikatsIevade = false;
        for (int j = 0; j < i; j++) if (vPs[i] == vPs[j]) dublikatsIevade = true;
        
        if (!dublikatsIevade && !jauIrSim(r, vPs[i])) jauniUnikali++;
    }

    int kopskaits = (r ? r->skaits : 0) + jauniUnikali;
    if (kopskaits > 50) { out << "no" << endl; return; }

    // 2. Izpilde
    if (!r) {
        r = new Recenzents;
        r->vards = vards;
        r->next = vardsTabula[vIdx];
        vardsTabula[vIdx] = r;
    }

    for (int i = 0; i < n; i++) {
        if (!jauIrSim(r, vPs[i])) {
            r->pseidonimi[r->skaits++] = vPs[i];
            int sIdx = hashS(vPs[i]);
            PseidonimaMezgla* pm = new PseidonimaMezgla;
            pm->vertiba = vPs[i];
            pm->ipasnieks = r;
            pm->next = skaitlisTabula[sIdx];
            skaitlisTabula[sIdx] = pm;
        }
    }
    out << "ok" << endl;
}

void remove(int key, ofstream& out) {
    int sIdx = hashS(key);
    PseidonimaMezgla* tempS = skaitlisTabula[sIdx];
    Recenzents* r = nullptr;
    while (tempS) {
        if (tempS->vertiba == key) { r = tempS->ipasnieks; break; }
        tempS = tempS->next;
    }

    if (!r) { out << "no" << endl; return; }

    // Izdzēšam visus pseidonīmus no skaitļu tabulas
    for (int i = 0; i < r->skaits; i++) {
        int ps = r->pseidonimi[i];
        int idx = hashS(ps);
        PseidonimaMezgla *curr = skaitlisTabula[idx], *prev = nullptr;
        while (curr) {
            if (curr->vertiba == ps) {
                if (!prev) skaitlisTabula[idx] = curr->next;
                else prev->next = curr->next;
                delete curr;
                break;
            }
            prev = curr; curr = curr->next;
        }
    }

    // Izdzēšam no vārdu tabulas
    int vIdx = hashV(r->vards);
    Recenzents *currV = vardsTabula[vIdx], *prevV = nullptr;
    while (currV) {
        if (currV->vards == r->vards) {
            if (!prevV) vardsTabula[vIdx] = currV->next;
            else prevV->next = currV->next;
            delete currV;
            out << "ok" << endl;
            return;
        }
        prevV = currV; currV = currV->next;
    }
}

int main() {
    ifstream in("reviewers.in");
    ofstream out("reviewers.out");


    char cmd;
    while (in >> cmd) {
        if (cmd == 'I') {
            string v; int n;
            in >> v >> n;
            insert(v, n, in, out);
        } else if (cmd == 'D') {
            int k; in >> k;
            remove(k, out);
        } else if (cmd == 'L') {
            int k; in >> k;
            Recenzents* r = kuraPseidonims(k);
            if (r) out << r->vards << endl;
            else out << "no" << endl;
        }
    }
    return 0;
}