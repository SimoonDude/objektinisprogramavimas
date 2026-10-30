#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <list>

using namespace std;

struct dict {
    vector<string> vardai_vyr;
    vector<string> pavardes_vyr;
    vector<string> vardai_mot;
    vector<string> pavardes_mot;
};

struct student {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egz;
    double vidurkis_val;
    double mediana_val;
    void vidurkis ();
    void mediana ();
    void imti_random_varda_pavarde (dict &v_p);
    void print () const;
    void print_file (ofstream &f) const;
    void randominiai_pazymiai (const int &k = 10);
    void duomenu_ivedimas ();
};

bool get_int_input (int &balas, bool minusvienas = false); // paima int inputa is userio, grazina `True` jeigu pavyko; `False` jeigu ne.
bool get_name_input (string &vard, string&pav); // get input string; if `-1` break loop
void randominiai_pazymiai (student &s, const int &k);
void skaityti_is_failo (vector<student> &studentai, const string &failo_pav);
void spausdinti_i_faila (const vector<student>& studentai, const string& failo_pav, bool debug = 0);
void spausdinti_i_terminal (vector<student>& studentai);
void generuoti_studentus (const int &paz_k, const int &k, string failo_pav = "0");
void sutvarkyti_studentus (vector<student>& studentai, const int &k, string failo_pav = "output", int c = 0);
void kaip_rusiuoti (int &c);
void rusiuoti (vector<student>& studentai, const int& c);
void debugger (vector<student>& studentai, const int& c);
int stulpelio_plotis (const string& tekstas, int plotis);
bool vargsunas (const student& s);

struct l_dict {
    list<string> vardai_vyr;
    list<string> pavardes_vyr;
    list<string> vardai_mot;
    list<string> pavardes_mot;
};
struct l_student {
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
    void randominiai_pazymiai (const int &k = 10);
    void duomenu_ivedimas ();
    void imti_random_varda_pavarde (l_dict &v_p);
};

void skaityti_is_failo (list<l_student> &studentai, const string &failo_pav);
void spausdinti_i_faila (list<l_student>& studentai, const string& failo_pav, bool debug = 0);
void spausdinti_i_terminal (list<l_student>& studentai);
void l_generuoti_studentus (const int &paz_k, string failo_pav = "0");
void sutvarkyti_studentus (list<l_student>& studentai, const int &k, string failo_pav = "output", int c = 0);
void rusiuoti (list<l_student>& studentai, const int& c);
void debugger (list<l_student>& studentai, const int& c);
bool l_vargsunas (const l_student& s);