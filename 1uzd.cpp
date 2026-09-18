#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct student {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egz;
    double galutinis;
};
int main() {
    vector<student> studentai;
    student studentas;
    cout << "vardas, pavarde\n"; cin >> studentas.vardas; cin >> studentas.pavarde;
    studentas.nd.resize(5);
    cout << "iveskite 5 namu d pazymius\n";
    for (auto &i : studentas.nd) {
        cin >> i;
    }
    cout << "egz rez:";
    cin >> studentas.egz;
    // studentas.galutinis = 0.6 *  + 0.4 * studentas.egz;
    studentai.push_back(studentas);
    for (auto &i : studentai) {
        cout << i.pavarde << ' ' << i.vardas << ' ' << i.egz << '\n';
    }
}
