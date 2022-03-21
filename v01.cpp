#include <iostream>
#include <string>
#include <iomanip>
#include <random>

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
    int size;
    double mediana;
};


void input(struct mokinys *mok, int &i);
// void print(int i,struct mokinys *mok);
int randP();

int main()
{
    mokinys *mok;
    mok = new mokinys[1];
    int temp, i = 0;
    input(mok, i);
    delete[] mok;
}

void input(struct mokinys *mok, int &i)
{ 
    mokinys* temp = nullptr;
    int* tempI = nullptr; 
    int j;
    char outhw, outhwrand, outegzrand, outaddmok;
    i = 0;
    while (outaddmok != 'n')
    {
        j = 1;
        cout << "Iveskite mokinio varda: ";
        cin >> mok[i].name;
        cout << "Iveskite mokinio pavarde: ";
        cin >> mok[i].surename;
        outhwrand = '0';
        cout << "Ar norite automatiskai generuoti namu darbu rezultatus?(t/n) ";
        while (outhwrand != 't' && outhwrand != 'n') cin >> outhwrand;
        if (outhwrand == 't')
        {
            mok[i].hw = new int[5];
            mok[i].size = 5;
            for (int g = 0; g < 5; g++)
            {
                mok[i].hw[g] = randP();
            }
        }
        else
        {
            cout << "Kiek pazymiu turi mokinys? ";
            cin >> mok[i].size;
            outhw = '0';
            cout << "Iveskite pazymius: ";
            mok[i].hw = new int[mok[i].size];
            for (int f = 0; f < mok[i].size; f++)
            {
                cin>>mok[i].hw[f];
            }
        }
        outegzrand = '0';
        cout << "Ar norite automatiskai generuoti egzmino rezultata?(t/n)";
        while (outegzrand != 't' && outegzrand != 'n') cin >> outegzrand;
        if (outegzrand == 't') mok[i].egzam = randP();

        else
        {
            cout << "Iveskite egzamino rezultata: ";
            cin >> mok[i].egzam;
        }

        outaddmok = '0';
        cout << "Ar norite prideti dar viena mokini?(t/n)? ";
        while (outaddmok != 't' && outaddmok != 'n') cin >> outaddmok;
        if (outaddmok == 't')
        {
            temp = new mokinys[i + 1];
            for (int l = 0; l <= i; l++)
            {
                temp[l].hw = new int [mok[l].size];//allocate mem to arr in temp struct
                temp[l] = mok[l];
                 for (int g = 0; g < mok[l].size; g++)
                {
                    
                    temp[l].hw[g] = mok[l].hw[g];
                }
            }
           
            
            delete[] mok;
            i++;
            mok = new mokinys[i + 1];
            
            for (int l = 0; l < i; l++)
            {
                
                mok[l].hw = new int[temp[l].size];
                mok[l] = temp[l];
                
                for (int g = 0; g < mok[l].size; g++)
                {
                    mok[l].hw[g] = temp[l].hw[g];
                }
                //delete[] temp[l].hw;
            }
            
            delete[] temp;  //delete temp
        }
    }
    cout << "Pavarde" << setw(15) << "Vardas" << setw(39) << "Galutinis (Vid.) / Galutinis (Med.)" <<endl;
    cout << "---------------------------------------------------------------------"<<endl;
    double calc;
    for (int j = 0; j <= i; j++)
    {
        cout <<  mok[j].name << setw(17) << mok[j].surename;
        calc = 0;

        for (int g = 0; g < mok[j].size; g++)
        {
            calc += mok[j].hw[g];
        }

        cout << setw(13) << std::fixed <<std::setprecision(2) << (0.6 * mok[j].egzam + ((0.4 * calc) / mok[j].size));
        int vid = mok[j].size / 2;
        mok[j].mediana = mok[j].size % 2 == 0 ? (mok[j].hw[vid - 1] + mok[j].hw[vid]) / 2
                                              : mok[j].hw[vid];
        cout << setw(20) <<std::fixed<< std::setprecision(2) << mok[j].mediana << endl;
    }
}

int randP()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);
    return dist(mt);
}