#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;
struct student {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egz;
    double galutinis;
    double mediana; // ikelti funkcija i struktura ?
};
bool get_int_input (int &balas);
double mediana (student &s);
student randominiai (student &s, const int &k);
void duomenu_vedimas (student &studentas);
int main() {
    int c, k, paz_k;
    while (true) { // meniu
        cout << "\n1. Ivesti studentu duomenis ranka\n2. Generuoti duomenis\n\nPasirinkite:";
        string choice; cin >> choice;
        try {
            c = stoi(choice);
            if (c == 2 || c == 3) {break;}
            else {cout << "\n\n\n"; continue;}
        } catch (...) {
            cout << "\n\n\n"; continue;
        }
    }
    vector<student> studentai;
    cout << "kiek studentu?: "; while (true) if (!get_int_input(k)) continue; else break;
    if (k == 0) {cout << "nera studentu, programa baigia darba.\n"; return 0;}
    if (c == 2) {cout << "pazymiu/ivertinimu kiekis: "; while (true) if (!get_int_input(paz_k)) continue; else break;}
    for (int i = 0; i < k; ++i) {
        student studentas;
        cout << "vardas pavarde:\n"; cin >> studentas.vardas >> studentas.pavarde;
        switch (c) {
            case 1:
                duomenu_vedimas(studentas);
            case 2:
                randominiai(studentas, paz_k);
        };
        for (auto &i : studentas.nd) studentas.galutinis += i;
        if(studentas.nd.size() != 0){ 
            studentas.galutinis /= studentas.nd.size(); // dalyba is nulio?
        } else {
            studentas.galutinis = 0;
        }
        cout << "egzamino rez.:\n";
        cin >> studentas.egz;
        studentas.galutinis = studentas.galutinis * 0.4 + studentas.egz * 0.6;
        studentas.mediana = mediana(studentas);
        studentai.push_back(studentas);
    }
    cout << left << setw(15) << "Vardas"
         << setw(15) << "Pavarde"
         << setw(20) << "Galutinis (vid.)"
         << setw(20) << "Galutinis (med.)\n";
    cout << string(70, '-') << '\n';
    cout << fixed << setprecision(2);
    for (const auto &i : studentai) {
        cout << left << setw(15) << i.vardas
             << setw(15) << i.pavarde
             << setw(20) << i.galutinis
             << setw(20) << i.mediana << '\n';
    }
}

bool get_int_input (int &balas) { // paima int inputa is userio, grazina `True` jeigu pavyko; `False` jeigu ne.
    string b; cin >> b;
    try {
        balas = stoi(b);
        if (balas > 0) {return 1;} else {throw;}
    } catch (...) {
        cout << "turi priklausyti naturaliu skaiciu aibei.\n";
        return 0;
    }
}
double mediana (student &s) { // ikelti funkcija i struktura ?
    int dydis = s.nd.size();
    if (dydis == 0) {return 0;}
    sort(s.nd.begin(), s.nd.end());
    if (dydis % 2 == 0) {
        s.mediana = s.nd[dydis/2] * .4 + s.egz * .6; // cia irgi galimai? dalyba is nulio
    } else {
        s.mediana = (s.nd[floor(dydis/2.0)] + s.nd[ceil(dydis/2.0)])/2 * .4 + s.egz * .6;
    }
    return s.mediana;
};
student randominiai (student &s, const int &k = 10) {
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 10); // cia istraukiau is cppreference.com
    for(int i = 0; i < k; ++i) {
        s.nd.push_back(distrib(gen));
    }
    return s;
};
void duomenu_vedimas (student &studentas) {
    cout << "veskite namu darbu pazymius, baigus iveskite -1:\n";
    while(true) {
        int balas;
        if (!get_int_input(balas)) continue;
        if (balas == -1) break;
        studentas.nd.push_back(balas);
    }
}