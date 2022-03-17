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


void input(mokinys *mok, int i);
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

void input(mokinys* mok, int i)
{ 
    mokinys* temp;
    int *tempI; 
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
        cout << "Ar norite automatiskai generuoti namu darbu rezultatus?(T/N) ";
        while (outhwrand != 'T' && outhwrand != 'N') cin >> outhwrand;
        if (outhwrand == 'T')
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
            outhw = '0';
            mok[i].hw = new int[j];
            while (outhw != 'N')
            {
                cout << "Iveskite pazymi: ";
                cin >> mok[i].hw[j - 1];
                outhw = '0';
                cout << "Ar norite ivesti dar pazymiu?(T/N)";
                while (outhw != 'T' && outhw != 'N') cin >> outhw;
                if(outhw == 'T')
                {    
                    tempI = new int[j];
                    for (int k = 0; k < j; k++)
                        mok[i].hw[k] = tempI[k];
                    j++;    //papildomas pazymys
                    delete[] mok[i].hw;  
                    mok[i].hw = new int[j];
                    for (int k = 0; k < j - 1; k++)
                        tempI[k] = mok[i].hw[k];

                    delete[] tempI;
                }
            } 
        }
        mok[i].size = j; //kiek i-tasis mokinys turi pazymiu
        outegzrand = '0';
        cout << "Ar norite automatiskai generuoti egzmino rezultata?(T/N)";
        while (outegzrand != 'T' && outegzrand != 'N') cin >> outegzrand;
        if (outegzrand == 'T') mok[i].egzam = randP();

        else
        {
            cout << "Iveskite egzamino rezultata: ";
            cin >> mok[i].egzam;
        }

        outaddmok = '0';
        cout << "Ar norite prideti dar viena mokini?(T/N)? ";
        while (outaddmok != 'T' && outaddmok != 'N') cin >> outaddmok;
        if (outaddmok == 'T')
        {
            temp = new mokinys[i + 1];
            for (int l = 0; l <= i; l++)
                temp[l] = mok[l];
            delete[] mok;
            i++;
            mok = new mokinys[i + 1];

            for (int l = 0; l < i; l++)
                mok[l] = temp[l];
            delete[] temp;  //delete temp
        }
    }
}

void print(int i, mokinys* mok)
{
    std::streamsize prec = cout.precision();
    cout << "Pavarde" << setw(15) << "Vardas" << setw(39) << "Galutinis (Vid.) / Galutinis (Med.)" <<endl;
    cout << "---------------------------------------------------------------------"<<endl;
    double temp;
    for (int j = 0; j <= i; j++)
    {
        cout <<  mok[j].name << setw(15) << mok[j].surename;
        temp = 0;

        for (int g = 0; g < j; g++)
        {
            temp += mok[j].hw[g];
        }

        cout << setw(8) << std::setprecision(3) << (0.6 * mok[j].egzam + 0.4 * temp) / mok[j].size << std::setprecision(prec);
        int vid = mok[j].size / 2;
        mok[j].mediana = mok[j].size % 2 == 0 ? (mok[j].hw[vid - 1] + mok[j].hw[vid]) / 2
                                              : mok[j].hw[vid];
        cout << setw(26) << std::setprecision(3) << mok[j].mediana << std::setprecision(prec) << endl;
    }
}

int randP()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);
    return dist(mt);
}