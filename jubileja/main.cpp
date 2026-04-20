#include <iostream>
#include <fstream>

using namespace std;

struct Darbinieks {
    char vards[31];
    char uzvards[31];
    int date, month, year;
};

Darbinieks visi[10001];
int kopskaits = 0;

bool irVienadi(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' || s2[i] != '\0') {
        char c1 = (s1[i] >= 'A' && s1[i] <= 'Z') ? s1[i] + 32 : s1[i];
        char c2 = (s2[i] >= 'A' && s2[i] <= 'Z') ? s2[i] + 32 : s2[i];
        if (c1 != c2) return false;
        i++;
    }
    return true;
}

int dienaGada(int date, int month) {
    int menesaDienas[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int result = 0;
    for (int i = 1; i < month; i++) result += menesaDienas[i];
    return result + date;
}

int main() {
    ifstream in("anniversary.in");
    ofstream out("anniversary.out");

    char cmd, dot;
    while (in >> cmd && cmd != 'X') {
        if (cmd == 'P') {
            char vards[31], uzvards[31];
            int date, month, year;
            in >> vards >> uzvards >> date >> dot >> month >> dot >> year;

            bool dubultais = false;
            for (int i = 0; i < kopskaits; i++) {
                if (irVienadi(visi[i].vards, vards) && irVienadi(visi[i].uzvards, uzvards) && 
                    visi[i].date == date && visi[i].month == month && visi[i].year == year) {
                    dubultais = true;
                    break;
                }
            }

            if (!dubultais && kopskaits < 10000) {
                int j = 0;
                while ((visi[kopskaits].vards[j] = vards[j]) != '\0') j++;
                j = 0;
                while ((visi[kopskaits].uzvards[j] = uzvards[j]) != '\0') j++;
                visi[kopskaits].date = date; 
                visi[kopskaits].month = month; 
                visi[kopskaits].year = year;
                kopskaits++;
            }
        } 
        else if (cmd == 'D') {
            int sodienasDate, sodienasMonth, sodienYear;
            in >> sodienasDate >> dot >> sodienasMonth >> dot >> sodienYear;

            int sodien = dienaGada(sodienasDate, sodienasMonth);
            int minDienasLidz = 366;

            for (int i = 0; i < kopskaits; i++) {
                int dzimsanasDiena = dienaGada(visi[i].date, visi[i].month);
                int starpiba;
                if (dzimsanasDiena >= sodien) starpiba = dzimsanasDiena - sodien;
                else starpiba = 365 - sodien + dzimsanasDiena;

                if (starpiba < minDienasLidz) minDienasLidz = starpiba;
            }

            Darbinieks* jubilari[10001];
            int jSk = 0;
            int jubDate = 0, jubMonth = 0;

            for (int i = 0; i < kopskaits; i++) {
                int dzDiena = dienaGada(visi[i].date, visi[i].month);
                int starpiba;
                if (dzDiena >= sodien) starpiba = dzDiena - sodien;
                else starpiba = 365 - sodien + dzDiena;

                if (starpiba == minDienasLidz) {
                    jubilari[jSk++] = &visi[i];
                    jubDate = visi[i].date; 
                    jubMonth = visi[i].month;
                }
            }

            int svinibuGads = sodienYear;
            if (dienaGada(jubDate, jubMonth) < sodien) svinibuGads++;

            // kartosana (vecums -> uzvards -> vards)
            for (int i = 0; i < jSk - 1; i++) {
                for (int j = 0; j < jSk - i - 1; j++) {
                    int vecums1 = svinibuGads - jubilari[j]->year;
                    int vecums2 = svinibuGads - jubilari[j+1]->year;
                    bool mainit = false;

                    if (vecums1 < vecums2) mainit = true; // vecakie vispirms
                    else if (vecums1 == vecums2) {
                        int k = 0;
                        while (true) {
                            char c1 = (jubilari[j]->uzvards[k] >= 'A' && jubilari[j]->uzvards[k] <= 'Z') ? jubilari[j]->uzvards[k] + 32 : jubilari[j]->uzvards[k];
                            char c2 = (jubilari[j+1]->uzvards[k] >= 'A' && jubilari[j+1]->uzvards[k] <= 'Z') ? jubilari[j+1]->uzvards[k] + 32 : jubilari[j+1]->uzvards[k];
                            if (c1 > c2) { mainit = true; break; }
                            if (c1 < c2) break;
                            if (c1 == '\0') {

                                int m_ind = 0;
                                while (true) {
                                    char v1_c = (jubilari[j]->vards[m_ind] >= 'A' && jubilari[j]->vards[m_ind] <= 'Z') ? jubilari[j]->vards[m_ind] + 32 : jubilari[j]->vards[m_ind];
                                    char v2_c = (jubilari[j+1]->vards[m_ind] >= 'A' && jubilari[j+1]->vards[m_ind] <= 'Z') ? jubilari[j+1]->vards[m_ind] + 32 : jubilari[j+1]->vards[m_ind];
                                    if (v1_c > v2_c) { mainit = true; break; }
                                    if (v1_c < v2_c) break;
                                    if (v1_c == '\0') break;
                                    m_ind++;
                                }
                                break;
                            }
                            k++;
                        }
                    }
                    if (mainit) {
                        Darbinieks* temp = jubilari[j];
                        jubilari[j] = jubilari[j+1];
                        jubilari[j+1] = temp;
                    }
                }
            }

            if (jubDate < 10) out << "0"; 
            out << jubDate << ".";
            if (jubMonth < 10) out << "0"; 
            out << jubMonth << "." << svinibuGads << endl;

            for (int i = 0; i < jSk; i++) {
                out << (svinibuGads - jubilari[i]->year) << " " << jubilari[i]->vards << " " << jubilari[i]->uzvards << endl;
            }
        }
    }
    in.close();
    out.close();
    return 0;
}