#include "1uzd_def.h"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <random>

void l_student::mediana () { // ikelti funkcijas i struktura ?
    if (nd.empty()) {mediana_val = egz * .6; return;}
    auto pazymiai = nd;
    pazymiai.sort();
    double mediana;
    if (pazymiai.size() % 2 == 1) {
        auto vidurys = pazymiai.begin();
        std::advance(vidurys, pazymiai.size() / 2);
        mediana = *vidurys;
    } else {
        auto vidurys = pazymiai.begin();
        std::advance(vidurys, pazymiai.size() / 2);
        auto ankstesnis = std::prev(vidurys);
        mediana = (*ankstesnis + *vidurys) / 2.0;
    }
    mediana_val = mediana * .4 + egz * .6;
};
void l_student::vidurkis () {
    if (nd.empty()) {vidurkis_val = egz * .6; return;}
    double galutinis = 0;
    for (int pazymys : nd) galutinis += pazymys;
    galutinis /= nd.size();
    vidurkis_val = galutinis * .4 + egz * .6;
}
void l_student::print () const {
    cout << left << setw(stulpelio_plotis(vardas, 30)) << vardas
            << setw(stulpelio_plotis(pavarde, 30)) << pavarde
            << setw(20) << vidurkis_val
            << setw(20) << mediana_val << '\n';
}
void l_student::print_file (ofstream &f) const {
    f << left << setw(stulpelio_plotis(vardas, 30)) << vardas
            << setw(stulpelio_plotis(pavarde, 30)) << pavarde
            << setw(20) << vidurkis_val
            << setw(20) << mediana_val << '\n';

}
void l_student::randominiai_pazymiai (const int &k) {
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 10); // cia istraukiau is cppreference.com
    for(int i = 0; i < k; ++i) {
        nd.push_back(distrib(gen));
    }
    egz = distrib(gen);
}
void l_student::duomenu_ivedimas () {
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
void l_student::imti_random_varda_pavarde (l_dict &v_p) {
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 1); // cia istraukiau is cppreference.com
    if (distrib(gen) == 0) { // vyras
        std::uniform_int_distribution<> distrib_vardas(0, v_p.vardai_vyr.size() - 1);
        std::uniform_int_distribution<> distrib_pavarde(0, v_p.pavardes_vyr.size() - 1);
        auto vardas_it = std::next(v_p.vardai_vyr.begin(), distrib_vardas(gen));
        auto pavarde_it = std::next(v_p.pavardes_vyr.begin(), distrib_pavarde(gen));
        vardas = *vardas_it;
        pavarde = *pavarde_it;
    } else { // moteris
        std::uniform_int_distribution<> distrib_vardas(0, v_p.vardai_mot.size() - 1);
        std::uniform_int_distribution<> distrib_pavarde(0, v_p.pavardes_mot.size() - 1);
        auto vardas_it = std::next(v_p.vardai_mot.begin(), distrib_vardas(gen));
        auto pavarde_it = std::next(v_p.pavardes_mot.begin(), distrib_pavarde(gen));
        vardas = *vardas_it;
        pavarde = *pavarde_it;
    }
}


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
        l_student s;
        row >> s.vardas >> s.pavarde;
        int balas;
        while (row >> balas) {
            s.nd.push_back(balas);
        }
        if (!s.nd.empty()) {
            s.egz = s.nd.back();
            s.nd.pop_back();
        }
        studentai.push_back(s);
    }
    f.close();
    chrono::duration<double> diff = chrono::high_resolution_clock::now() - start;
    cout << " | " << failo_pav << " Failo skaitymas uztruko: " << diff.count() << " s.\n";
}

void spausdinti_i_faila (list<l_student>& studentai, const string& failo_pav, bool debug) {
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

void spausdinti_i_terminal (list<l_student>& studentai) {
    cout << left << setw(30) << "Vardas"
         << setw(30) << "Pavarde"
         << setw(20) << "Galutinis (vid.)"
         << setw(20) << "Galutinis (med.)" << '\n';
    cout << string(100, '-') << '\n';
    cout << fixed << setprecision(2);
    for (const auto &i : studentai) {
        i.print();
    }
}

void l_generuoti_studentus (const int &paz_k, string failo_pav) {
    int kiekis;
    cout << "iveskite studentu kieki: ";
    while (true) if (!get_int_input(kiekis)) continue; else break;
    bool to_file = (failo_pav != "0") ? 1 : 0;

    ifstream vv("assets/vardai_vyr"), pv("assets/pavardes_vyr");
    ifstream vm("assets/vardai_mot"), pm("assets/pavardes_mot");
    string line; l_dict v_p;
    while (getline(vv, line)) v_p.vardai_vyr.push_back(line);
    while (getline(pv, line)) v_p.pavardes_vyr.push_back(line);
    while (getline(vm, line)) v_p.vardai_mot.push_back(line);
    while (getline(pm, line)) v_p.pavardes_mot.push_back(line);
    vv.close(); pv.close(); vm.close(); pm.close();
    
    ofstream f;
    if (to_file) f.open(failo_pav);
    else f.close();

    for (int i = 0; i < kiekis; ++i) {
        l_student s;
        s.imti_random_varda_pavarde(v_p);
        s.randominiai_pazymiai(paz_k);
        if (to_file) s.print_file(f);
        else         s.print();
    }
    if (to_file) f.close();
}

void rusiuoti (list<l_student>& studentai, const int& c) {
    if (c == 1) {
        studentai.sort(
            [](const l_student &a, const l_student &b) {return a.pavarde < b.pavarde;});
    } else if (c == 2) {
        studentai.sort(
            [](const l_student &a, const l_student &b) {return a.vidurkis_val > b.vidurkis_val;});
    }
}
bool l_vargsunas (const l_student& s) {
    return s.vidurkis_val < 5;
};
void sutvarkyti_studentus (list<l_student>& studentai, const int &k, string failo_pav, int c) {
    for (auto &s : studentai) {
        s.vidurkis();
        s.mediana();
    }
    // if c not passed, ask for c
    if (c == 0) kaip_rusiuoti(c);
    rusiuoti(studentai, c);

    if (k == 1) {
        spausdinti_i_terminal(studentai);
    } else if (k == 2) {
        spausdinti_i_faila(studentai, failo_pav);
    } else if (k == 3) {
        auto start = chrono::high_resolution_clock::now();

        // auto newEnd = std::remove_if(
        //     studentai.begin(),
        //     studentai.end(),
        //     l_vargsunas
        // );
        // list<l_student> galutinis_bezlow5;
        // std::copy(newEnd, studentai.end(), std::back_inserter(galutinis_below5));
        // studentai.erase(newEnd, studentai.end());

        list<l_student> galutinis_below5;
        for (auto it = studentai.begin(); it != studentai.end();) {
            if (l_vargsunas(*it)) {
                auto studentas = it++;
                galutinis_below5.splice(galutinis_below5.end(), studentai, studentas);
            } else {
                ++it;
            }
        }

        chrono::duration<double> diff = chrono::high_resolution_clock::now() - start;
        cout << " | Studentu skirstymas i dvi grupes uztruko: " << diff.count() << " s.\n";
        spausdinti_i_faila(studentai, failo_pav + "_islaike.txt", 1);
        spausdinti_i_faila(galutinis_below5, failo_pav + "_neislaike.txt", 1);
    }
}
void debugger (list<l_student>& studentai, const int& c) {
    skaityti_is_failo(studentai, "studentai10000.txt");
    sutvarkyti_studentus(studentai, 3, "10000", c);
    studentai.clear();
    cout << "\n";
    skaityti_is_failo(studentai, "studentai100000.txt");
    sutvarkyti_studentus(studentai, 3, "100000", c);
    studentai.clear();
    cout << "\n";
    skaityti_is_failo(studentai, "studentai1000000.txt");
    sutvarkyti_studentus(studentai, 3, "1000000", c);
    studentai.clear();
}