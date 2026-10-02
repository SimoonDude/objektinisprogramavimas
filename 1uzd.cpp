#include "1uzd_papildai.h"
using namespace std;

int main() {
    int c, k = 0, paz_k;
    while (true) { // meniu
        cout << "\n1. Ivesti studentu duomenis ranka\n2. Skaityti is failo\n3. Generuoti pazymius\n4. Generuoti studentus\nPasirinkite: ";
        string choice; cin >> choice;
        try {
            c = stoi(choice);
            if (c == 1 || c == 2 || c == 3 || c == 4) {break;}
            else {cout << "\n\n\n"; continue;}
        } catch (...) {
            cout << "\n\n\n"; continue;
        }
    }
    while (true) {
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

    for (auto &s : studentai) {
        s.vidurkis();
        s.mediana();
    }

    sort(studentai.begin(), studentai.end(), 
        [](const student  &a, const student &b) {return a.vidurkis_val > b.vidurkis_val;});
    
    if (k == 1) {
        spausdinti_i_terminal(studentai);
    } else if (k == 2) {
        auto start = chrono::high_resolution_clock::now();
        vector<student> galutinis_over5, galutinis_below5;
        for (const auto &s : studentai) {
            if (s.vidurkis_val >= 5) {galutinis_over5.push_back(s);}
            else {galutinis_below5.push_back(s);}
        }
        chrono::duration<double> diff = chrono::high_resolution_clock::now() - start;
        cout << " | Studentu skirstymas i dvi grupes uztruko: " << diff.count() << " s.\n";
        string failo_pav;
        cout << "iveskite failo pavadinima isvedimui (islaikiusiems): "; cin >> failo_pav;
        spausdinti_i_faila(galutinis_over5, failo_pav);
        cout << "iveskite failo pavadinima isvedimui (neislaikiusiems): "; cin >> failo_pav;
        spausdinti_i_faila(galutinis_below5, failo_pav);
    }
    return 0;
}