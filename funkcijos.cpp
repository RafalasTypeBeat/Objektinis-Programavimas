#include "funkcijos.h"
#include "mokiniai.h"
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
        temp.hw.pop_back();
        in.clear();
    }
    return in;
}

istream& readData(istream& in, mokinys& temp)
{
    in >> temp.name >> temp.surename;
    readHw(in, temp);
    return in;
}

bool compareName(const mokinys&x , const mokinys& y)
{
    return x.name < y.name;
}

void input(vector<mokinys>& mok, int vieta)
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

void print(vector<mokinys>& mok)
{
    cout <<setw(15)<< "Vardas" << setw(15) << "Pavarde" << setw(45) << "Galutinis (Vid.) / Galutinis (Med.)" <<endl;
    cout << "---------------------------------------------------------------------"<<endl;
    for (const auto& M : mok)
    {
        cout << setw(15) << M.name << setw(15) << M.surename;
        cout << setw(14) << std::fixed << std::setprecision(2) << galutinis(M.egzam, M.hw, vidurkis);
        cout << setw(19) << std::fixed << std::setprecision(2) << galutinis(M.egzam, M.hw, mediana) << endl;
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