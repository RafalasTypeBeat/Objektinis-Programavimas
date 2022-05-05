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

void generate(int &FileSkc)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);
    //auto start = hrClock::now();
    int MokiniuSkc = 100;
    FileSkc = 0;
    int choice = 1, index = 1;
    while (choice == 1)
    {
        auto start = hrClock::now();
        FileSkc ++;
        MokiniuSkc *= 10;
        stringstream pavadinimas;
        pavadinimas << "kursiokai" << index << ".txt";
        ofstream out(pavadinimas.str());
        for (int i = 1; i <= MokiniuSkc; i++)
        {
            stringstream name, lastname, output;
            name << "Vardas" << i << " ";
            lastname << "Pavarde" << i << " ";
            output << name.str() << lastname.str();
            for (int j = 0; j < 15; j++)
            {
                output << dist(mt) << " ";
            }
            output << endl;
            out << output.str(); //iraso i faila
        }
        out.close();
        auto stop = hrClock::now();
        //auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::chrono::duration<double> diff = stop-start;
        //duration /= 1000;
        cout<<"Failu generavimas su "<< MokiniuSkc << " mokiniu uztruko: "<< std::setprecision(2) <<diff.count()<<" sekundziu."<<endl;
        cout<<"Jei norite generuoti faila su  "<< MokiniuSkc * 10<<" mokiniais iveskite 1." << endl;
        cin >> choice;
        index ++;
    }
    //failu rusiavimas
}

bool gavoSkola(const mokinys& m, double (*kriterijus)(vector<double>) = mediana) {
 return galutinis(m.egzam, m.hw, kriterijus) < 5.0;
}

vector<mokinys> sortByGrades(vector<mokinys>& mok){
    vector<mokinys> neislaike;
    vector<mokinys>::iterator it = mok.begin();
    while(it != mok.end()){
        if(gavoSkola(*it)){
        neislaike.push_back(*it);
        it = mok.erase(it);
    }
    else it++;
    }
    return neislaike;
}

void readAndSort(int FileSkc)
{
    //nuskaito is sugeneruotu failu ir sudeda i vectoriu
    vector<mokinys> mok;
    mokinys temp;
    for(int i = 0;i < FileSkc; i++)
    {
    stringstream pavadinimas;
    pavadinimas << "kursiokai" << i << ".txt"; //sukuria failo pavadinima
    ifstream in(pavadinimas.str());
    while (readData(in, temp))
    {
        mok.push_back(temp);
    }
    sort(mok.begin(), mok.end(), compareName);
    in.close();
    //nuskaito viena faila i vektoriu
    writeSorted(sortByGrades(mok), mok, i);//rusiuoja pagal pazymius

    }
    
}

void writeSorted(vector<mokinys> &pass,vector<mokinys> &fail, int FileNr)
{
    stringstream nameFail, namePass;
        nameFail << "neislaike" << FileNr << ".txt";
        namePass << "islaike" << FileNr << ".txt";
        ofstream outF(nameFail.str());
        ofstream outP(namePass.str());
        //sukuria du txt failus islaikiusiems ir neislaikiusiems
        vector<mokinys>::iterator itP = pass.begin(); //islaike
        vector<mokinys>::iterator itF = fail.begin(); //neislaike
        while(itP != pass.end()){
            stringstream name, lastname, output;
            name << itP->name << " ";
            lastname << itP->surename << " ";
            output << name.str() << lastname.str();
            for (int j = 0; j < 15; j++)
            {
                output << itP->hw[j] << " ";
            }
            output << endl;
            outP << output.str(); //iraso i faila
        }
        while(itF != pass.end()){
            stringstream name, lastname, output;
            name << itF->name << " ";
            lastname << itF->surename << " ";
            output << name.str() << lastname.str();
            for (int j = 0; j < 15; j++)
            {
                output << itF->hw[j] << " ";
            }
            output << endl;
            outF << output.str(); //iraso i faila
        }
        outF.close();
        outP.close();
}