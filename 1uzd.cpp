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
void duomenu_ivedimas (student &studentas);
void skaityti_is_failo (vector<student> &studentai, const string &failo_pav);
void spausdinti_i_faila (vector<student>& studentai, const string& failo_pav);
void spausdinti_i_terminal (vector<student>& studentai);
void generuoti_randominius (vector<student>& studentai, const int &paz_k);

int main() {
    int c, k = 0, paz_k;
    while (true) { // meniu
        cout << "\n1. Ivesti studentu duomenis ranka\n2. Skaityti is failo\n3. Generuoti pazymius i terminal\n4. Generuoti studentus i faila\nPasirinkite: ";
        string choice; cin >> choice;
        try {
            c = stoi(choice);
            if (c == 1 || c == 2 || c == 3 || c == 4) {break;}
            else {cout << "\n\n\n"; continue;}
        } catch (...) {
            cout << "\n\n\n"; continue;
        }
    }
    vector<student> studentai;

    if (c == 3 || c == 4) { // pasirinkta: generuoti i console OR generuoti i faila
        cout << "pazymiu/ivertinimu kiekis: "; 
        while (true) if (!get_int_input(paz_k)) continue; else break;
    }
    else if (c == 2) { // skaityti is failo
        string failo_pav;
        system("cd"); system("dir *.txt");
        cout << "iveskite failo pavadinima: "; cin >> failo_pav;
        skaityti_is_failo(studentai, failo_pav);
    }   
    else if (c == 4) { // jeigu pasirinkimas i faila gen
        string failo_pav;
        system("cd"); system("dir *.txt");
        cout << "iveskite isvedimui failo pavadinima: "; cin >> failo_pav;
        generuoti_randominius(studentai, paz_k);
    }
    
    while (c == 1 || c == 3) { // jeigu pasirinkimas paciam arba generuoti i console
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
            case 2:
                randominiai(studentas, paz_k);
                break;
        }
        studentai.push_back(studentas);
    }
    sort(studentai.begin(), studentai.end(), 
        [](const student  &a, const student &b) {return a.pavarde < b.pavarde;});
    spausdinti_i_terminal(studentai);
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
void duomenu_ivedimas (student &studentas) {
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
    f.close();
}
void spausdinti_i_faila (vector<student>& studentai, const string& failo_pav) {
    ofstream f(failo_pav);
    if (!f.is_open()) {
        cout << "neapvyko atidaryti failo: " << failo_pav << endl;
        return;
    }
    f << left << setw(15) << "Vardas"
         << setw(15) << "Pavarde"
         << setw(20) << "Galutinis (vid.)"
         << setw(20) << "Galutinis (med.)\n";
    f << string(70, '-') << '\n';
    f << fixed << setprecision(2);
    for (const auto &i : studentai) {
        cout << left << setw(15) << i.vardas
             << setw(15) << i.pavarde
             << setw(20) << i.vidurkis()
             << setw(20) << i.mediana() << '\n';
    }
    f.close();
}
void spausdinti_i_terminal (vector<student>& studentai) {
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
void generuoti_randominius (vector<student>& studentai, const int &paz_k) {
    int kiekis;
    cout << "iveskite studentu kieki: ";
    while (true) if (!get_int_input(kiekis)) continue; else break;
    // ifstream vardai_vyr("assets/vardai_vyr"), pavardes_vyr("assets/pavardes_vyr");
    // ifstream vardai_mot("assets/vardai_mot"), pavardes_mot("assets/pavardes_mot");
    for (int i = 0; i < kiekis; ++i) {
        student s;
        s.vardas = "Vardas" + to_string(i + 1);
        s.pavarde = "Pavarde" + to_string(i + 1);
        randominiai(s, paz_k);
    }
}