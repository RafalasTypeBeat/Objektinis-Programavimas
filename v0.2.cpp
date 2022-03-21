#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <vector>
#include <fstream>

using std::string;
using std::cin;
using std::cout;
using std::setw;
using std::endl;
using std::ifstream;
using std::ofstream;

struct mokinys
{
    string name = "", surename = "";
    std::vector<int> hw;
    int egzam;
    int size = 0;
    double mediana;
};
int randP();
void input(std::vector<mokinys>& mok, int &vieta);
void print(std::vector<mokinys> mok, int vieta);

int main()
{
    std::vector<mokinys> mok;
    int vieta = 0, choice; 
    cout<<"Ar norite duomenis ivesti ranka ar skaityti is failo?(1/2)";
    while(choice != 0 && choice!= 1)cin>>choice;
    if (choice == 1)
    {
        input(mok, vieta);
        print(mok, vieta);
    }
    else
    {
        ifstream in("kursiokai.txt");
    }
}

void read(std::vector<mokinys>& mok, int &vieta, ifstream &in)
{
    in.ignore(1000, '\n');
    int pazSk;
    cout<<"Po kiek pazymiu turi mokiniai?: ";
    cin>>pazSk;
    while (!in.eof())
    {
        mok.push_back(mokinys());
        in>>mok[vieta].name>>mok[vieta].surename;
        mok[vieta].hw.push_back(pazSk);
        for (int i = 0; i < pazSk; i++)
        {
            in>>mok[vieta].hw[i];
        }
    }
    
}

void input(std::vector<mokinys>& mok, int &vieta)
{ 
    char outhw, outhwrand, outegzrand, outaddmok;
    vieta = 0;
    int nd, ndsize;
    while (outaddmok != 'n')
    {
        ndsize = 0;
        cout << "Iveskite mokinio varda: ";
        mok.push_back(mokinys());
        cin >> mok[vieta].name;
        cout << "Iveskite mokinio pavarde: ";
        cin >> mok[vieta].surename;
        outhwrand = '0';
        cout << "Ar norite automatiskai generuoti namu darbu rezultatus?(t/n) ";
        while (outhwrand != 't' && outhwrand != 'n') cin >> outhwrand;
        if (outhwrand == 't')
        {
            mok[vieta].size = 5;
            for (int g = 0; g < 5; g++)
            {
                mok[vieta].hw.push_back(randP());
            }
        }
        else
        {
            cout << "Iveskite pazymius: ";
            while(cin >> nd)
            {
                mok[vieta].hw.push_back(nd);
                ndsize++;
            }
            mok[vieta].size = ndsize;
            std::cin.clear();
            //std::cin.ignore(INT_MAX);
        }
        outegzrand = '0';
        cout << "Ar norite automatiskai generuoti egzmino rezultata?(t/n)";
        while (outegzrand != 't' && outegzrand != 'n') cin >> outegzrand;
        if (outegzrand == 't') mok[vieta].egzam = randP();

        else
        {
            cout << "Iveskite egzamino rezultata: ";
            cin >> mok[vieta].egzam;
        }

        outaddmok = '0';
        cout << "Ar norite prideti dar viena mokini?(t/n)? ";
        while (outaddmok != 't' && outaddmok != 'n') cin >> outaddmok;
        if(outaddmok == 't')vieta++;
    }
}

void print(std::vector<mokinys> mok, int vieta)
{
    cout << "Pavarde" << setw(15) << "Vardas" << setw(39) << "Galutinis (Vid.) / Galutinis (Med.)" <<endl;
    cout << "---------------------------------------------------------------------"<<endl;
    double temp;
    int vid;
    for (int j = 0; j <= vieta; j++)
    {
        cout <<  mok[j].surename << setw(17) << mok[j].name;
        temp = 0;

        for (int g = 0; g < mok[j].size; g++)
        {
            temp += mok[j].hw[g];
        }
        cout << setw(13) << std::fixed << std::setprecision(2) << (0.6 * mok[j].egzam + ((0.4 * temp) / mok[j].size));
        vid = mok[j].size / 2;
        mok[j].mediana = mok[j].size % 2 == 0 ? (mok[j].hw[vid - 1] + mok[j].hw[vid]) / 2
                                              : mok[j].hw[vid];
        cout << setw(18) << std::fixed << std::setprecision(2) << mok[j].mediana << endl;
    }
}

int randP()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);
    return dist(mt);
}