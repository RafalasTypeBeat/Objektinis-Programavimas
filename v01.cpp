#include <iostream>
#include <string>
#include <iomanip>

using std::string;
using std::cin;
using std::cout;
using std::setw;

struct mokinys
{
    string name = "", surename = "";
    int hw, egzam;
    float rez;
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
    cout << setw(15) << mokinys1.name << setw(15) << mokinys1.surename << setw(20) << "Galutinis (Vid.)";
    cout << "-----------------------------------"
}