#include <vector>
#include <iomanip>
#include <algorithm>
#include <random>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

struct student {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egz;
    double vidurkis_val;
    double mediana_val;
    void vidurkis ();
    void mediana ();
};
bool get_int_input (int &balas, bool minusvienas = false); // paima int inputa is userio, grazina `True` jeigu pavyko; `False` jeigu ne.
bool get_name_input (string &vard, string&pav); // get input string; if `-1` break loop
void randominiai_pazymiai (student &s, const int &k);
void duomenu_ivedimas (student &studentas);
void skaityti_is_failo (vector<student> &studentai, const string &failo_pav);
void spausdinti_i_faila (vector<student>& studentai, const string& failo_pav);
void spausdinti_i_terminal (vector<student>& studentai);
void generuoti_studentus (vector<student>& studentai, const int &paz_k);
void sutvarkyti_studentus (vector<student>& studentai, const int &k, string failo_pav = "output");
void imti_random_varda_pavarde (student& s, const vector<string>& vardai_vyr, const vector<string>& pavardes_vyr, const vector<string>& vardai_mot, const vector<string>& pavardes_mot);

int stulpelio_plotis (const string& tekstas, int plotis) {
    int simboliu_kiekis = 0;
    for (size_t i = 0; i < tekstas.size(); ++i) {
        if ((static_cast<unsigned char>(tekstas[i]) & 0xC0) != 0x80) {
            ++simboliu_kiekis;
        }
    }
    return plotis + static_cast<int>(tekstas.size()) - simboliu_kiekis;
}

bool get_name_input (string &vard, string &pav) {
    cin >> vard >> pav;
    if (vard == "-1" || pav == "-1") {return 0;} else {return 1;}
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
void student::mediana () { // ikelti funkcijas i struktura ?
    if (nd.empty()) {mediana_val = egz * .6; return;}
    auto pazymiai = nd;
    sort(pazymiai.begin(), pazymiai.end());\
    double mediana;
    if (pazymiai.size() % 2 == 1) {
        mediana = pazymiai[pazymiai.size() / 2];
    } else {
        size_t vidurys = pazymiai.size() / 2;
        mediana = (pazymiai[vidurys - 1] + pazymiai[vidurys]) / 2.0;
    }
    mediana_val = mediana * .4 + egz * .6;
};
void student::vidurkis () {
    if (nd.empty()) {vidurkis_val = egz * .6; return;}
    double galutinis = 0;
    for (int pazymys : nd) galutinis += pazymys;
    galutinis /= nd.size();
    vidurkis_val = galutinis * .4 + egz * .6;
}
void randominiai_pazymiai (student &s, const int &k = 10) {
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
    auto start = chrono::high_resolution_clock::now();
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
    chrono::duration<double> diff = chrono::high_resolution_clock::now() - start;
    cout << " | " << failo_pav << " Failo skaitymas uztruko: " << diff.count() << " s.\n";
}
void spausdinti_i_faila (vector<student>& studentai, const string& failo_pav) {
    auto start = chrono::high_resolution_clock::now();
    ofstream f(failo_pav);
    if (!f.is_open()) {
        cout << "neapvyko atidaryti failo: " << failo_pav << endl;
        return;
    }
    f << left << setw(30) << "Vardas"
         << setw(30) << "Pavarde"
         << setw(20) << "Galutinis (vid.)"
         << setw(20) << "Galutinis (med.)" << '\n';
    f << string(100, '-') << '\n';
    f << fixed << setprecision(2);
    for (const auto &i : studentai) {
        f << left << setw(stulpelio_plotis(i.vardas, 30)) << i.vardas
             << setw(stulpelio_plotis(i.pavarde, 30)) << i.pavarde
             << setw(20) << i.vidurkis_val
             << setw(20) << i.mediana_val << '\n';
    }
    f.close();
    chrono::duration<double> diff = chrono::high_resolution_clock::now() - start;
    cout << " | " << failo_pav << " Failo rasymas uztruko: " << diff.count() << " s.\n";
}
void spausdinti_i_terminal (vector<student>& studentai) {
    cout << left << setw(30) << "Vardas"
         << setw(30) << "Pavarde"
         << setw(20) << "Galutinis (vid.)"
         << setw(20) << "Galutinis (med.)" << '\n';
    cout << string(100, '-') << '\n';
    cout << fixed << setprecision(2);
    for (const auto &i : studentai) {
        cout << left << setw(stulpelio_plotis(i.vardas, 30)) << i.vardas
             << setw(stulpelio_plotis(i.pavarde, 30)) << i.pavarde
             << setw(20) << i.vidurkis_val
             << setw(20) << i.mediana_val << '\n';
    }
}
void generuoti_studentus (vector<student>& studentai, const int &paz_k) {
    int kiekis;
    cout << "iveskite studentu kieki: ";
    while (true) if (!get_int_input(kiekis)) continue; else break;

    ifstream vv("assets/vardai_vyr"), pv("assets/pavardes_vyr");
    ifstream vm("assets/vardai_mot"), pm("assets/pavardes_mot");
    vector<string> vardai_vyr, pavardes_vyr, vardai_mot, pavardes_mot;
    string line;
    while (getline(vv, line)) vardai_vyr.push_back(line);
    while (getline(pv, line)) pavardes_vyr.push_back(line);
    while (getline(vm, line)) vardai_mot.push_back(line);
    while (getline(pm, line)) pavardes_mot.push_back(line);
    vv.close(); pv.close(); vm.close(); pm.close();
    
    for (int i = 0; i < kiekis; ++i) {
        student s;
        imti_random_varda_pavarde(s, vardai_vyr, pavardes_vyr, vardai_mot, pavardes_mot);
        randominiai_pazymiai(s, paz_k);
        studentai.push_back(s);
    }
}
void imti_random_varda_pavarde (student& s, const vector<string>& vardai_vyr, const vector<string>& pavardes_vyr, const vector<string>& vardai_mot, const vector<string>& pavardes_mot) {
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 1); // cia istraukiau is cppreference.com
    if (distrib(gen) == 0) { // vyras
        std::uniform_int_distribution<> distrib_vardas(0, vardai_vyr.size() - 1);
        std::uniform_int_distribution<> distrib_pavarde(0, pavardes_vyr.size() - 1);
        s.vardas = vardai_vyr[distrib_vardas(gen)];
        s.pavarde = pavardes_vyr[distrib_pavarde(gen)];
    } else { // moteris
        std::uniform_int_distribution<> distrib_vardas(0, vardai_mot.size() - 1);
        std::uniform_int_distribution<> distrib_pavarde(0, pavardes_mot.size() - 1);
        s.vardas = vardai_mot[distrib_vardas(gen)];
        s.pavarde = pavardes_mot[distrib_pavarde(gen)];
    }
}
void sutvarkyti_studentus (vector<student>& studentai, const int &k, string failo_pav) {
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
        spausdinti_i_faila(galutinis_over5, failo_pav + "_islaike.txt");
        spausdinti_i_faila(galutinis_below5, failo_pav + "_neislaike.txt");
    }
}
