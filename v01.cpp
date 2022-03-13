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
    int* hw = nullptr;
    int egzam;
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
    
    
    int temp, i = 0, size;
    cout << "Kiek namu darbu rezultatu norite ivesti? "; cin>>size;
    mokinys1.hw = new int[size];
    cout << "Iveskite namu darbu rezultatatus: " << endl;
    for(; i < size; i++)
    {
        cin >> temp;
        if (temp > 0 && temp <= 10)
        { 
            mokinys1.hw[i] = temp;
        }
    }
    
    cout << "Iveskite egzamino rezultata: ";
    cin >> mokinys1.egzam;
    cout << "Isvesti vidurki ar mediana? V/M ";
    while (out != 'V' && out != 'M') cin >> out;
    cout << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(39) << "Galutinis (Vid.) / Galutinis (Med.)" <<endl;
    cout << "---------------------------------------------------------------------"<<endl;
    cout << setw(15) << mokinys1.name << setw(15) << mokinys1.surename;
    temp = 0;
    if(out == 'V') 
    {
        for (i = 0; i < size; i++)
        {
            temp += mokinys1.hw[i];
        }
        mokinys1.rez = (float(temp + mokinys1.egzam)) / (size + 1);
        cout << setw(8) << std::setprecision(3) << mokinys1.rez;
    }
    else
    {
        if(size % 2 == 0)
        cout << setw(26) << std::setprecision(3) <<  mokinys1.hw[size / 2];
        else if (size == 0) cout << setw(26) << mokinys1.egzam;
        else if (size == 1) cout << setw(26) << std::setprecision(3) << (float(mokinys1.hw[0] + mokinys1.egzam))/2;
        else
        cout << setw(26) << std::setprecision(3) << (float(mokinys1.hw[(size + 1) / 2] + mokinys1.hw[(size - 1) / 2]) / 2);
    }
    
}