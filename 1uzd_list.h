#include <string>
#include <list>
#include <fstream>
#include <random>

#include "1uzd_papildai.h"

class l_student {
    public:
    std::string vardas;
    std::string pavarde;
    std::list<int> nd;
    int egz;
    double vidurkis_val;
    double mediana_val;
    void vidurkis ();
    void mediana ();
    void print () const;
    void print_file (std::ofstream &f) const;

    void randominiai_pazymiai (const int &k = 10) {
        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(1, 10); // cia istraukiau is cppreference.com
        for(int i = 0; i < k; ++i) {
            nd.push_back(distrib(gen));
        }
        egz = distrib(gen);
    }
    void duomenu_ivedimas () {
        cout << "veskite namu darbu pazymius, baigus iveskite -1:\n";
        while(true) {
            int balas;
            if (!get_int_input(balas, 1)) continue;
            if (balas == -1) break;
            nd.push_back(balas);
        }
        cout << "egzamino rez.:\n";
        get_int_input(egz);
    }

};

void skaityti_is_failo (list<l_student> &studentai, const string &failo_pav) {
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

void spausdinti_i_faila (list<student>& studentai, const string& failo_pav, bool debug) {
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
        i.print_file(f);
    }
    f.close();
    if (debug) {
        chrono::duration<double> diff = chrono::high_resolution_clock::now() - start;
        cout << " | " << failo_pav << " Failo rasymas uztruko: " << diff.count() << " s.\n";
    } 
}