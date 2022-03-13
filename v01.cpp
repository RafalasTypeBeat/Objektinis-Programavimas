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
    int hw[3], egzam;
    double rez = 0;
    int mediana;
};

int main()
{
    char out;
    mokinys mokinys1;
    cout << "Iveskite mokinio varda: ";
    cin >> mokinys1.name;
    cout << "Iveskite mokinio pavarde: ";
    cin >> mokinys1.surename;
    
    
    
    cout << "Iveskite namu darbo rezultata: " << endl;
    for (int i = 0; i < 3; i++)
    {
        cin >> mokinys1.hw[i];
        mokinys1.rez += mokinys1.hw[i];
    }
    cout << "Iveskite egzamino rezultata: ";
    cin >> mokinys1.egzam;
    cout << "Isvesti vidurki ar mediana? V/M ";
    while (out != 'V' && out != 'M') cin >> out;
    cout << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(39) << "Galutinis (Vid.) / Galutinis (Med.)" <<endl;
    cout << "---------------------------------------------------------------------"<<endl;

    
    cout << setw(15) << mokinys1.name << setw(15) << mokinys1.surename;
    if(out == 'V') 
    {
        mokinys1.rez = (mokinys1.rez + mokinys1.egzam) / 4;
        cout << setw(7) << std::setprecision(3) << mokinys1.rez;
    }
    else
    {
        cout << setw(26) << std::setprecision(3) << (float(mokinys1.hw[1] + mokinys1.hw[2]))/2;
    }
    
}