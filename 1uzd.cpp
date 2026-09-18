#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;
struct student {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egz;
    double galutinis;
    double mediana;
};
int main() {
    vector<student> studentai;
    student studentas{};

    cout << "vardas, pavarde\n"; cin >> studentas.vardas; cin >> studentas.pavarde;
    cout << "iveskite 5 namu d pazymius\n"; studentas.nd.resize(5);
    for (auto &i : studentas.nd) cin >> i;
    for (auto &i : studentas.nd) studentas.galutinis += i;
    studentas.galutinis /= 5;
    cout << "egz rez:";
    cin >> studentas.egz;
    studentas.galutinis = studentas.galutinis * 0.4 + studentas.egz * 0.6;
    sort(studentas.nd.begin(), studentas.nd.end());
    studentas.mediana = (studentas.nd[2] + studentas.nd[3]) / 2.0 * 0.4 + studentas.egz * 0.6;
    studentai.push_back(studentas);
    cout << left << setw(15) << "Vardas"
         << setw(15) << "Pavarde"
         << setw(20) << "Galutinis (vid.)\n"
         << setw(20) << "Galutinis (med.)\n";
    cout << string(50, '-') << '\n';
    cout << fixed << setprecision(2);
    for (const auto &i : studentai) {
        cout << left << setw(15) << i.vardas
             << setw(15) << i.pavarde
             << setw(20) << i.galutinis
             << setw(20) << i.mediana << '\n';
    }
}
