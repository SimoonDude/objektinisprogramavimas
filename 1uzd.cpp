#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>

using namespace std;
struct student {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egz;
    double vidurkis () const;
    double mediana () const;
};
bool get_int_input (int &balas, bool minusvienas = false); // paima int inputa is userio, grazina `True` jeigu pavyko; `False` jeigu ne.
bool get_name_input (string &vard, string&pav); // get input string; if `-1` break loop
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
    if (c == 2) {cout << "pazymiu/ivertinimu kiekis: "; while (true) if (!get_int_input(paz_k)) continue; else break;}
    else if (c == 3) {
        string failo_pav;
        system("cd"); system("dir *.txt");
        cout << "iveskite failo pavadinima: "; cin >> failo_pav;
        skaityti_is_failo(studentai, failo_pav);
    }   
    while (true) {
        student studentas;
        cout << "vardas pavarde:\n";
        if (!get_name_input(studentas.vardas, studentas.pavarde)) {
            if (studentai.size() == 0) {cout << "nera studentu, programa baigia darba.\n"; return 0;}
            break;
        }
        switch (c) {
            case 1:
                duomenu_vedimas(studentas);
                break;
            case 2:
                randominiai(studentas, paz_k);
                break;
        };
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
             << setw(20) << i.vidurkis()
             << setw(20) << i.mediana() << '\n';
    }
}
bool get_name_input (string &vard, string &pav) {
    cin >> vard >> pav;
    if (vard != "-1" || pav != "-1") {return 1;} else {return 0;}
};
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
double student::mediana () const { // ikelti funkcijas i struktura ?
    if (nd.empty()) return egz * .6;
    auto pazymiai = nd;
    sort(pazymiai.begin(), pazymiai.end());\
    double mediana;
    if (pazymiai.size() % 2 == 1) {
        mediana = pazymiai[pazymiai.size() / 2];
    } else {
        size_t vidurys = pazymiai.size() / 2;
        mediana = (pazymiai[vidurys - 1] + pazymiai[vidurys]) / 2.0;
    }
    return mediana * .4 + egz * .6;
};
double student::vidurkis () const {
    if (nd.empty()) return egz * .6; 
    double galutinis = 0;
    for (int pazymys : nd) galutinis += pazymys;
    galutinis /= nd.size();
    return galutinis * .4 + egz * .6;
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
        studentai.push_back(s);
    }
}