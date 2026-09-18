#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;
struct student {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egz;
    double galutinis;
    double mediana; // ikelti funkcijas i struktura ?
};
bool get_int_input (int &balas, bool minusvienas = false); // paima int inputa is userio, grazina `True` jeigu pavyko; `False` jeigu ne.
double mediana (student &s);
double galutinis (student &s);
void randominiai (student &s, const int &k);
void duomenu_vedimas (student &studentas);
void skaityti_is_failo (vector<student> &studentai, const string &failo_pav);
int main() {
    int c, k = 0, paz_k;
    while (true) { // meniu
        cout << "\n1. Ivesti studentu duomenis ranka\n2. Generuoti duomenis\n3. Skaityti is failo\n\nPasirinkite: ";
        string choice; cin >> choice;
        try {
            c = stoi(choice);
            if (c == 1 || c == 2 || c == 3) {break;}
            else {cout << "\n\n\n"; continue;}
        } catch (...) {
            cout << "\n\n\n"; continue;
        }
    }
    vector<student> studentai;
    if (c == 1 || c == 2) {
        cout << "kiek studentu?: "; while (true) if (!get_int_input(k)) continue; else break;
        if (k == 0) {cout << "nera studentu, programa baigia darba.\n"; return 0;}
    }
    else if (c == 2) {cout << "pazymiu/ivertinimu kiekis: "; while (true) if (!get_int_input(paz_k)) continue; else break;}
    else if (c == 3) {
        string failo_pav;
        cout << "iveskite failo pavadinima: "; cin >> failo_pav;
        skaityti_is_failo(studentai, failo_pav);
    }   
    for (int i = 0; c != 3 && i < k; ++i) {
        student studentas;
        cout << "vardas pavarde:\n"; cin >> studentas.vardas >> studentas.pavarde;
        switch (c) {
            case 1:
                duomenu_vedimas(studentas);
                break;
            case 2:
                randominiai(studentas, paz_k);
                break;
        };
        studentas.galutinis = galutinis(studentas);
        studentas.mediana = mediana(studentas);
        studentai.push_back(studentas);
    }
    sort(studentai.begin(), studentai.end(), 
        [](const student  &a, const student &b) {return a.pavarde < b.pavarde;});
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

bool get_int_input (int &balas, bool minusvienas) { // paima int inputa is userio, grazina `True` jeigu pavyko; `False` jeigu ne.
    string b; cin >> b;
    try {
        balas = stoi(b);
        if (balas > 0 || (minusvienas && balas == -1)) {return 1;} else {throw 1;}
    } catch (...) {
        cout << "turi priklausyti naturaliu skaiciu aibei.\n";
        return 0;
    }
}
double mediana (student &s) { // ikelti funkcijas i struktura ?
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
double galutinis (student &s) {
    s.galutinis = 0;
    for (auto &i : s.nd) s.galutinis += i;
    if(s.nd.size() != 0){ 
        s.galutinis /= s.nd.size();
    } else {
        s.galutinis = 0;
    }
    s.galutinis = s.galutinis * .4 + s.egz * .6;
    return s.galutinis;
}
void randominiai (student &s, const int &k = 10) {
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 10); // cia istraukiau is cppreference.com
    for(int i = 0; i < k; ++i) {
        s.nd.push_back(distrib(gen));
    }
    s.egz = distrib(gen);
};
void duomenu_vedimas (student &studentas) {
    cout << "veskite namu darbu pazymius, baigus iveskite -1:\n";
    while(true) {
        int balas;
        if (!get_int_input(balas, 1)) continue;
        if (balas == -1) break;
        studentas.nd.push_back(balas);
    }
    cout << "egzamino rez.:\n";
    get_int_input(studentas.egz);
}
void skaityti_is_failo (vector<student> &studentai, const string &failo_pav) {
    ifstream f(failo_pav);
    if (!f.is_open()) {
        cout << "nepavyko atidaryti failo: " << failo_pav << endl;
        return;
    }
    string line;
    getline(f, line);
    while (getline(f, line)) {
        if (line.empty()) continue;
        istringstream row(line);
        student s;
        row >> s.vardas >> s.pavarde;
        int balas;
        while (row >> balas) {
            s.nd.push_back(balas);
        }
        s.egz = s.nd.back(); s.nd.pop_back();
        s.galutinis = galutinis(s);
        s.mediana = mediana(s);
        studentai.push_back(s);
    }
}