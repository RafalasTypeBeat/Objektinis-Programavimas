#include <iostream>
#include <string>
#include <iomanip>

using std::string;
using std::cin;
using std::cout;
using std::setw;
using std::endl;

struct mokinys
{
    string name = "", surename = "";
    int hw, egzam;
    double rez;
};

int main()
{
    mokinys mokinys1;
    cout << "Iveskite mokinio varda: ";
    cin >> mokinys1.name;
    cout << "Iveskite mokinio pavarde: ";
    cin >> mokinys1.surename;
    cout << "Iveskite namu darbo rezultata: ";
    cin >> mokinys1.hw;
    cout << "Iveskite egzamino rezultata: ";
    cin >> mokinys1.egzam;
    cout << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(20) << "Galutinis (Vid.)"<<endl;
    cout << "--------------------------------------------------"<<endl;
    mokinys1.rez = ((float)(mokinys1.hw + mokinys1.egzam)) / 2;
    cout << setw(15) << mokinys1.name << setw(15) << mokinys1.surename <<setw(7) << std::setprecision(3) << mokinys1.rez;
}