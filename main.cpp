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

// Funkcija, lai atrastu, kam pieder pseidonīms
Recenzents* atrastIpasnieku(int pseidonims) {
    int index = hashSkaitlim(pseidonims);
    PseidonimaMezgla* temp = skaitlisTabula[index];
    while (temp) {
        if (temp->vertiba == pseidonims) return temp->ipasnieks;
        temp = temp->next;
    }
    return nullptr;
}



void insert(string vards, int n, ifstream& in, ofstream& out) {
    int pagaiduMasivs[100]; // Pagaidu masīvs nolasīšanai
    for (int i = 0; i < n; i++) in >> pagaiduMasivs[i];

    int vIdx = hashVardam(vards);
    Recenzents* r = vardsTabula[vIdx];
    while (r && r->vards != vards) r = r->next;

    // 1. Validācija
    int jauniUnikali = 0;
    for (int i = 0; i < n; i++) {
        Recenzents* ipasnieks = atrastIpasnieku(pagaiduMasivs[i]);
        if (ipasnieks && ipasnieks != r) { out << "no" << endl; return; }
        
        // Pārbaudām, vai šis ir jauns pseidonīms (nav dublikāts ievadē vai esošajos)
        bool dublikatsIevade = false;
        for (int j = 0; j < i; j++) if (pagaiduMasivs[i] == pagaiduMasivs[j]) dublikatsIevade = true;
        
        if (!dublikatsIevade && !jauPieder(r, pagaiduMasivs[i])) jauniUnikali++;
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
        if (!jauPieder(r, pagaiduMasivs[i])) {
            r->pseidonimi[r->skaits++] = pagaiduMasivs[i];
            int sIdx = hashSkaitlim(pagaiduMasivs[i]);
            PseidonimaMezgla* pm = new PseidonimaMezgla;
            pm->vertiba = pagaiduMasivs[i];
            pm->ipasnieks = r;
            pm->next = skaitlisTabula[sIdx];
            skaitlisTabula[sIdx] = pm;
        }
    }
    out << "ok" << endl;
}

void remove(int key, ofstream& out) {
    int sIdx = hashSkaitlim(key);
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
        int idx = hashSkaitlim(ps);
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
    int vIdx = hashVardam(r->vards);
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
            Recenzents* r = atrastIpasnieku(k);
            if (r) out << r->vards << endl;
            else out << "no" << endl;
        }
    }
    return 0;
}