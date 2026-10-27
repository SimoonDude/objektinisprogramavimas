#include "1uzd_def.h"
#include "1uzd_papildai.h"
#include "1uzd_list.h"

using namespace std;

int main() {
    int c, k = 0, l, paz_k;
    string failo_pav = "0"; 

    // gal iskelti meniu i papildus ar dar kur
    while (true) { // meniu
        cout << "\n1. Ivesti studentu duomenis ranka"
                "\n2. Apdoroti duomenis is failo"
                "\n3. Generuoti pazymius studentams"
                "\n4. Generuoti studentus (ir pazymius)"
                "\n5. Debug"
                "\nPasirinkite: ";
        string choice; cin >> choice;
        try {
            c = stoi(choice);
            if (c == 1 || c == 2 || c == 3 || c == 4 || c == 5) {break;} 
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
    if (k == 2) {
        cout << "Isvesties failo pavadinimas?:\n";
        while (true) {
            try {
                cin >> failo_pav;
                ofstream f(failo_pav);
                if (!f.is_open()) throw;
                else {f.close(); break;}
            } catch (...) {
                cout << "nepavyko atidaryti failo: " << failo_pav << endl;
                continue;
            }
        }
    }
    while (true && c == 5) {
        cout << "Naudoti std::vector (1) ar std::list (2) ?: ";
        string choice; cin >> choice;
        try {
            l = stoi(choice);
            if (l == 1 || l == 2) {break;}
            else {cout << "\n\n\n"; continue;}
        } catch (...) {
            cout << "\n\n\n"; continue;
        }
    }

    vector<student> studentai;
    list<l_student> l_studentai;

    if (c == 3 || c == 4) { // pasirinkta generuoti, kiek studentu?
        cout << "pazymiu/ivertinimu kiekis: "; 
        while (true) if (!get_int_input(paz_k)) continue; else break;
    }
    else if (c == 2) { // pasirinkta skaityti is failo
        string failo_pav;
        system("cd"); system("dir *.txt");
        cout << "iveskite duomenu failo pavadinima : "; cin >> failo_pav;
        skaityti_is_failo(studentai, failo_pav);
    }   
    else if (c == 5) {// Testavimas su dideliu studentu kiekiu
        int r; kaip_rusiuoti(r);
        if (l == 1) debugger(studentai, r);
        else if (l == 2) debugger(l_studentai, r);        
        return 0;
    }
    if (c == 4) { // jeigu pasirinkta generuoti viska
        generuoti_studentus(paz_k, k, failo_pav);
        return 0;
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
                studentas.duomenu_ivedimas();
                break;
            case 3:
                studentas.randominiai_pazymiai(paz_k);
                break;
        }
        studentai.push_back(studentas);
        cerr << "objekto `student *` adresas: " << &studentai.back() << '\n';
    }
    sutvarkyti_studentus(studentai, k, failo_pav);
    return 0;
}