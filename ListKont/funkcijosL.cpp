#include "funkcijosL.h"
#include "mokiniaiL.h"

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
        temp.egzam = temp.hw.back();
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

void input(list<mokinys>& mok, int vieta)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);
    char outhwrand, outegzrand, outaddmok;
    auto it = mok.begin();
    int nd, ndsize, temprand;
    while (outaddmok != 'n')
    {
        ndsize = 0;
        cout << "Iveskite mokinio varda: ";
        mok.push_back(mokinys());
        cin >> (*it).name;
        cout << "Iveskite mokinio pavarde: ";
        cin >> (*it).surename;
        outhwrand = '0';
        cout << "Ar norite automatiskai generuoti namu darbu rezultatus?(t/n) ";
        while (outhwrand != 't' && outhwrand != 'n') cin >> outhwrand;
        if (outhwrand == 't')
        {
            (*it).size = 5;
            for (int g = 0; g < 5; g++)
            {
                (*it).hw.push_back(dist(mt));
            }
        }
        else
        {
            cout << "Iveskite pazymius: ";
            while(cin >> nd)
            {
                (*it).hw.push_back(nd);
                ndsize++;
            }
            (*it).size = ndsize;
            std::cin.clear();
        }
        outegzrand = '0';
        cout << "Ar norite automatiskai generuoti egzmino rezultata?(t/n)";
        while (outegzrand != 't' && outegzrand != 'n') cin >> outegzrand;
        if (outegzrand == 't') (*it).egzam = dist(mt);

        else
        {
            cout << "Iveskite egzamino rezultata: ";
            cin >> (*it).egzam;
        }

        outaddmok = '0';
        cout << "Ar norite prideti dar viena mokini?(t/n)? ";
        while (outaddmok != 't' && outaddmok != 'n') cin >> outaddmok;
        if(outaddmok == 't')it++;
    }
}

void print(list<mokinys>& mok)
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

double mediana(list<double> hw)
{
    typedef list<int>::size_type vecSize;
    vecSize size = hw.size();
    if (size == 0)
        throw std::domain_error("Negalima skaiciuoti medianos, kai vektorius tuscias! ");
    hw.sort();
    std::list<double>::iterator it = hw.begin();
    for( int i = 0 ; i < size / 2 ; i ++ ) it++;
    return size % 2 == 0 ? (*it + (*it--)) / 2 : *it;
}

double vidurkis(list<double> hw)
{
    if (hw.size() == 0)
        throw std::domain_error("Negalima skaiciuoti vidurkio, kai vektorius tuscias! ");
    return std::accumulate(hw.begin(), hw.end(), 0.0) / hw.size();
}

double galutinis(double egz, double hw)
{
    return 0.6 * egz + 0.4 * hw;
}

double galutinis(double egz, const list<double>& hw, double (*kriterijus)(list<double>))
{
    if(hw.size() == 0)
        throw std::domain_error("Negalima skaiciuoti galutinio ivertinimo, nes nera namu darbu ivertinimu! ");
    return galutinis(egz, kriterijus(hw));
}

void generate(int &FileSkc)
{
    //list<mokinys> mok;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);
    //auto start = hrClock::now();
    //list<mokinys>::iterator it = mok.begin();
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

bool gavoSkola(list<double> &hw, int egz, double &mediana)  {
    double temp;//reiksme medianai saugoti
    typedef list<int>::size_type vecSize;
    vecSize size = hw.size();
    if (size == 0)
        throw std::domain_error("Negalima skaiciuoti medianos, kai vektorius tuscias! ");
    hw.sort();
    std::list<double>::iterator it = hw.begin();
    for( int i = 0 ; i < size / 2 ; i ++ ) it++;
    vecSize vid = size / 2;
    temp =  size % 2 == 0 ? (*it + (*it--)) / 2 : *it;
    mediana = (0.6 * egz + 0.4 * temp);
    return mediana < 5.0;
}

void sortByGrades(list<mokinys>& mok, list<mokinys> &fail, list<mokinys> &pass){
    list<mokinys>::iterator it = mok.end();
    it--;
    while(it != mok.begin()){
        if(gavoSkola(it->hw, it->egzam, it->mediana)){
        fail.push_back(*it);
        it--;
    }
    else{
    pass.push_back(*it);
    it--;
    }
    mok.pop_back();
    }
}

void readAndSort(int FileSkc)//nuskaito is sugeneruotu failu ir sudeda i listiu
{
    auto startRead = hrClock::now();
    list<mokinys> mok, fail, pass;
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
    sortByGrades(mok, fail, pass); //rusiavimas
    auto stopSort = hrClock::now();
    std::chrono::duration<double> diffSort = stopSort-startSort;
    cout<<"Failo "<<pavadinimas.str()<<" rusiavimas uztruko "<<std::setprecision(2) <<diffSort.count()<<" sekundziu."<<endl;

    writeSorted(fail, mok, i);//iraso i atskirus failus islaikiusius ir neislaikiusius
    }
}

void writeSorted(list<mokinys> &fail,list<mokinys> &pass, int FileNr)
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
        list<mokinys>::iterator itP = pass.begin(); //islaike
        list<mokinys>::iterator itF = fail.begin(); //neislaike
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