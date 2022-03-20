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


void input(mokinys *mok, int &i);
void print(int i, mokinys* mok);
int randP();

int main()
{
    mokinys* mok = new mokinys[1];
    int temp, i = 0;
    input(mok, i);
    print(i, mok);
    delete[] mok;
}

void input(mokinys *mok, int &i)
{ 
    mokinys* temp;
    int* tempI = nullptr; 
    int j;
    char outhw, outhwrand, outegzrand, outaddmok;
    i = 0;
    while (outaddmok != 'N')
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
        cout<<mok[i].size;
        outegzrand = '0';
        cout << "Ar norite automatiskai generuoti egzmino rezultata?(T/N)";
        while (outegzrand != 't' && outegzrand != 'n') cin >> outegzrand;
        if (outegzrand == 't') mok[i].egzam = randP();

        else
        {
            cout << "Iveskite egzamino rezultata: ";
            cin >> mok[i].egzam;
        }

        outaddmok = '0';
        cout << "Ar norite prideti dar viena mokini?(T/N)? ";
        while (outaddmok != 't' && outaddmok != 'n') cin >> outaddmok;
        if (outaddmok == 't')
        {
            temp = new mokinys[i + 1];
            for (int l = 0; l <= i; l++)
            {
                temp[l].hw = new int [mok[l].size];
                temp[l] = mok[l];
                 for (int g = 0; g < mok[l].size; g++)
                {
                    temp[l].hw[g] = mok[l].hw[g];
                }
                     //allocate mem to arr in temp struct
            }
           
            
            // delete[] mok->hw;
            delete[] mok;
            cout<<i;
            i++;
            cout<<i;
            mok = new mokinys[i + 1];

            for (int l = 0; l < i; l++)
            {
                mok[l].hw = new int[temp[l].size];
                mok[l] = temp[l];
                for (int g = 0; g < mok[l].size; g++)
                {
                    mok[l].hw[g] = temp[l].hw[g];
                }
            }
            // delete[] temp->hw;
            delete[] temp;  //delete temp
        }
    }
}

void print(int i, mokinys* mok)
{
    cout<<i;
    cout << "Pavarde" << setw(15) << "Vardas" << setw(39) << "Galutinis (Vid.) / Galutinis (Med.)" <<endl;
    cout << "---------------------------------------------------------------------"<<endl;
    double temp;
    for (int j = 0; j <= i; j++)
    {
        cout <<  mok[j].name << setw(17) << mok[j].surename;
        temp = 0;

        for (int g = 0; g < mok[j].size; g++)
        {
            temp += mok[j].hw[g];
        }

        cout << setw(13) << std::setprecision(3) << (0.6 * mok[j].egzam + ((0.4 * temp) / mok[j].size));
        int vid = mok[j].size / 2;
        mok[j].mediana = mok[j].size % 2 == 0 ? (mok[j].hw[vid - 1] + mok[j].hw[vid]) / 2
                                              : mok[j].hw[vid];
        cout << setw(17) << std::setprecision(3) << mok[j].mediana << endl;
    }
}

int randP()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);
    return dist(mt);
}