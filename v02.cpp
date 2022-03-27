#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <chrono>

using std::string;
using std::cin;
using std::cout;
using std::setw;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using hrClock = std::chrono::high_resolution_clock;
using std::istream;

struct mokinys
{
    string name = "", surename = "";
    vector<double> hw;
    int egzam;
    int size = 0;
    double mediana;
};

void input(vector<mokinys>& mok, int &vieta);
void print(vector<mokinys> mok, int vieta);
void read(vector<mokinys>& mok, int &vieta, ifstream &in);
double mediana(vector<double> hw);
double vidurkis(vector<double> hw);
double galutinis(double egz, double hw);
double galutinis(double egz, const vector<double>& hw, double (*kriterijus)(vector<double>) = mediana);

int main()
{
    vector<mokinys> mok;
    mokinys temp;
    int vieta = 0, choice; 
    cout<<"Ar norite duomenis ivesti ranka ar skaityti is failo?(1/2)";
    while(choice != 1 && choice!= 2)cin>>choice; 
    if (choice == 1)
    {
        input(mok, vieta);
    }
    else
    {
        ifstream in("kursiokai.txt");
        while (readData(cin, temp))
        {
            mok.push_back(temp);
        }
        

    }
    try
        {
            print(mok, vieta);
        }
        catch(std::domain_error)
        {
            cout<<endl<<"Privalote ivesti pazymius i vektoriu! ";
            return 1;
        }
        return 0;
}


istream& readHw(istream& in, mokinys& temp)
{
    if(in)
    {
        temp.hw.clear();
        double x, count = 0;
        while(in >> x)
        {
            temp.hw.push_back(x);
            count++;
        } 
        temp.egzam = temp.hw[count - 1];
        temp.hw.erase(temp.hw.end() - 1);
        in.clear();
    }
    return in;
}

istream& readData(istream& in, mokinys& temp)
{
    in >> temp.name >> temp.surename;
    readHw(in, temp);
}


// void read(vector<mokinys>& mok, int &vieta, ifstream &in)
// {
//     in.ignore(1000, '\n');
//     int pazSk, paz;
//     string test;
//     cout<<"Po kiek pazymiu turi mokiniai?: ";
//     cin>>pazSk;

//     while (!in.eof())
//     {

//         mok.push_back(mokinys());
//         if(in>>test)
//         {
//             mok[vieta].name = test;
//             in>>mok[vieta].surename;
//             in.clear();
//         }
//         else break;
//         mok[vieta].hw.clear();
//         for (int i = 0; i < pazSk; i++)
//         {
//             in>>paz;
//             mok[vieta].hw.push_back(paz);
//             //cout<<mok[vieta].hw[i];
//         }
//         in>>mok[vieta].egzam;
//         in.clear();
//         vieta++;
//         if(in.eof())break;
//     }
//     in.close();
// }

void input(vector<mokinys>& mok, int &vieta)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);
    char outhwrand, outegzrand, outaddmok;
    vieta = 0;
    int nd, ndsize, temprand;
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
                mok[vieta].hw.push_back(dist(mt));
                cout<<mok[vieta].hw[g];
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
        if (outegzrand == 't') mok[vieta].egzam = dist(mt);

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

void print(vector<mokinys> mok, int vieta)
{
    cout <<setw(15)<< "Vardas" << setw(15) << "Pavarde" << setw(45) << "Galutinis (Vid.) / Galutinis (Med.)" <<endl;
    cout << "---------------------------------------------------------------------"<<endl;
    for (int j = 0; j <= vieta; j++)
    {
        cout << setw(15) << mok[j].name << setw(15) << mok[j].surename;
        cout << setw(14) << std::fixed << std::setprecision(2) << galutinis(mok[j].egzam, mok[j].hw, vidurkis);
        cout << setw(19) << std::fixed << std::setprecision(2) << galutinis(mok[j].egzam, mok[j].hw, mediana) << endl;
    }
}

double mediana(vector<double> hw)
{
    typedef vector<int>::size_type vecSize;
    vecSize size = hw.size();
    if (size == 0)
        throw std::domain_error("Negalima skaiciuoti medianos, kai vektorius tuscias! ");
    sort(hw.begin(), hw.end());
    vecSize vid = size / 2;
    return size % 2 == 0 ? (hw[vid] + hw[vid - 1]) / 2 : hw[vid];
}

double vidurkis(vector<double> hw)
{
    if (hw.size() == 0)
        throw std::domain_error("Negalima skaiciuoti vidurkio, kai vektorius tuscias! ");
    return std::accumulate(hw.begin(), hw.end(), 0.0) / hw.size();
}

double galutinis(double egz, double hw)
{
    return 0.6 * egz + 0.4 * hw;
}

double galutinis(double egz, const vector<double>& hw, double (*kriterijus)(vector<double>))
{
    if(hw.size() == 0)
        throw std::domain_error("Negalima skaiciuoti galutinio ivertinimo, nes nera namu darbu ivertinimu! ");
    return galutinis(egz, kriterijus(hw));
}