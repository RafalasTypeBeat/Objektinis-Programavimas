#include "funkcijosV.h"
#include "mokiniaiV.h"

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
    //vector<mokinys> mok;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);
    //auto start = hrClock::now();
    //vector<mokinys>::iterator it = mok.begin();
    int MokiniuSkc = 100;
    FileSkc = 0;
    int choice = 1, index = 1;
    while (choice == 1)
    {
        auto startGen = hrClock::now();
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
            for (int j = 0; j < 5; j++)
            {
                output << dist(mt) << " ";
            }
            output << endl;
            out << output.str(); //iraso i faila
        }
        out.close();
        auto stopGen = hrClock::now();
        std::chrono::duration<double> diffGen = stopGen-startGen;
        cout<<"Failu generavimas su "<< MokiniuSkc << " mokiniu uztruko: "<< std::setprecision(2) <<diffGen.count()<<" sekundziu."<<endl;
        cout<<"Jei norite generuoti faila su  "<< MokiniuSkc * 10<<" mokiniais iveskite 1. Jei ne, iveskite bet koki simoboli: " << endl;
        cin >> choice;
        if(choice != 1)break;
        index ++;
    }
    //failu rusiavimas
    readAndSort(FileSkc);
}

bool gavoSkola(vector<double> &hw, int egz, double &mediana)  {
    double temp;//reiksme medianai saugoti
    typedef vector<int>::size_type vecSize;
    vecSize size = hw.size();
    if (size == 0)
        throw std::domain_error("Negalima skaiciuoti medianos, kai vektorius tuscias! ");
    sort(hw.begin(), hw.end());
    vecSize vid = size / 2;
    temp = size % 2 == 0 ? (hw[vid] + hw[vid - 1]) / 2 : hw[vid];
    mediana = (0.6 * egz + 0.4 * temp);
    return mediana < 5.0;
}


vector<mokinys> sortByGrades(vector<mokinys>& mok){
    vector<mokinys> neislaike;
    vector<mokinys>::iterator it = mok.begin();
    while(it != mok.end()){
        if(gavoSkola(it->hw, it->egzam, it->mediana)){
        neislaike.push_back(*it);
        *it = mok.back();
        mok.pop_back();
    }
    else it++;
    }
    return neislaike;
}


void readAndSort(int FileSkc)//nuskaito is sugeneruotu failu ir sudeda i vectoriu
{
    auto startRead = hrClock::now();
    vector<mokinys> mok, fail;
    mokinys temp;
    
    for(int i = 1;i <= FileSkc; i++)
    {
    mok.clear();
    fail.clear();
    stringstream pavadinimas;
    pavadinimas << "kursiokai" << i << ".txt"; //sukuria failo pavadinima
    ifstream in(pavadinimas.str());
    int t = 0;
    while (readData(in, temp))//nuskaito faila i vektoriu
    {
        mok.push_back(temp);
        t++;
    }
    //sort(mok.begin(), mok.end(), compareName);
    in.close();

    auto stopRead = hrClock::now();
    std::chrono::duration<double> diffRead = stopRead-startRead;
    cout<<"Failo "<<pavadinimas.str()<<" nuskaitymas uztruko "<<std::setprecision(2) <<diffRead.count()<<" sekundziu."<<endl;

    auto startSort = hrClock::now();
    fail = sortByGrades(mok); //rusiavimas
    auto stopSort = hrClock::now();
    std::chrono::duration<double> diffSort = stopSort-startSort;
    cout<<"Failo "<<pavadinimas.str()<<" rusiavimas uztruko "<<std::setprecision(2) <<diffSort.count()<<" sekundziu."<<endl;

    writeSorted(fail, mok, i);//iraso i atskirus failus islaikiusius ir neislaikiusius
    }
}

void writeSorted(vector<mokinys> &fail,vector<mokinys> &pass, int FileNr)
{
    auto startWrite = hrClock::now();
    stringstream nameFail, namePass;
        nameFail << "neislaike" << FileNr << ".txt";
        namePass << "islaike" << FileNr << ".txt";
        ofstream outF(nameFail.str());
        ofstream outP(namePass.str());
        outF << "Vardas " << " Pavarde " << setw(2) << " Galutinis (Med.)" <<endl;
        outF<<"------------------------------"<<endl;
        outP << "Vardas " << setw(2) << " Pavarde " << setw(2) << " Galutinis (Med.)" <<endl;    
        outP<<"------------------------------"<<endl;
        //sukuria du txt failus islaikiusiems ir neislaikiusiems
        vector<mokinys>::iterator itP = pass.begin(); //islaike
        vector<mokinys>::iterator itF = fail.begin(); //neislaike
        while(itP != pass.end()){
            stringstream name, lastname, output;
            name << itP->name << " ";
            lastname << itP->surename << " ";
            output << name.str() << lastname.str();
            output << itP->mediana;
            output << endl;
            outP << output.str(); //iraso i faila
            itP++;
        }
        while(itF != fail.end()){
            stringstream name, lastname, output;
            name << itF->name << " ";
            lastname << itF->surename << " ";
            output << name.str() << lastname.str();
            output << itF->mediana;
            output << endl;
            outF << output.str(); //iraso i faila
            itF++;//pereina prie kito
        }
        outF.close();
        outP.close();
         auto stopWrite = hrClock::now();
        std::chrono::duration<double> difWrite = stopWrite-startWrite;
        cout<<"Surusiuotu failu isvedimas uztruko "<<std::setprecision(2) <<difWrite.count()<<" sekundziu."<<endl;
        cout<<"------------------------------"<<endl;
}