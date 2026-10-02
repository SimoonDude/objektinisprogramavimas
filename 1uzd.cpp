#include "1uzd_papildai.h"
using namespace std;

int main() {
    int c, k = 0, paz_k;
    while (true) { // meniu
        cout << "\n1. Ivesti studentu duomenis ranka\n2. Skaityti is failo\n3. Generuoti pazymius\n4. Generuoti studentus\nPasirinkite: ";
        string choice; cin >> choice;
        try {
            c = stoi(choice);
            if (c == 1 || c == 2 || c == 3 || c == 4 || c == 5) {break;} // jeigu 5, mes testuosime nuo 10k iki 1 milijono studentu
            else {cout << "\n\n\n"; continue;}
        } catch (...) {
            cout << "\n\n\n"; continue;
        }
    }
    while (true && c != 5) {
        cout << "Isvesti i terminal (1) ar i faila (2) ?: ";
        string choice; cin >> choice;
        try {
            k = stoi(choice);
            if (k == 1 || k == 2) {break;}
            else {cout << "\n\n\n"; continue;}
        } catch (...) {
            cout << "\n\n\n"; continue;
        }
    }
    vector<student> studentai;

    if (c == 3 || c == 4) { // pasirinkta generuoti
        cout << "pazymiu/ivertinimu kiekis: "; 
        while (true) if (!get_int_input(paz_k)) continue; else break;
    }
    else if (c == 2) { // skaityti is failor
        string failo_pav;
        system("cd"); system("dir *.txt");
        cout << "iveskite duomenu failo pavadinima : "; cin >> failo_pav;
        skaityti_is_failo(studentai, failo_pav);
    }   
    else if (c == 5) {
        // Testavimas su dideliu studentu kiekiu
        skaityti_is_failo(studentai, "studentai10000.txt");
        sutvarkyti_studentus(studentai, 2, "output");
        studentai.clear();
        cout << "\n";
        skaityti_is_failo(studentai, "studentai100000.txt");
        sutvarkyti_studentus(studentai, 2, "output");
        studentai.clear();
        cout << "\n";
        skaityti_is_failo(studentai, "studentai1000000.txt");
        sutvarkyti_studentus(studentai, 2, "output");
        studentai.clear();
        return 0;
    }
    if (c == 4) { // jeigu pasirinkimas i faila gen
        generuoti_studentus(studentai, paz_k);
    }
    
    while (c == 1 || c == 3) { // while pats arba paz. generuoti
        student studentas;
        cout << "vardas pavarde:\n";
        if (!get_name_input(studentas.vardas, studentas.pavarde)) {
            if (studentai.size() == 0) {cout << "nera studentu, programa baigia darba.\n"; return 0;}
            break;
        }
        switch (c) {
            case 1:
                duomenu_ivedimas(studentas);
                break;
            case 3:
                randominiai_pazymiai(studentas, paz_k);
                break;
        }
        studentai.push_back(studentas);
    }
    sutvarkyti_studentus(studentai, k, "output");
    return 0;
}