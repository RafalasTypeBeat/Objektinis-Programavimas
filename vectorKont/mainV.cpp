#include "funkcijosV.h"
#include "mokiniaiV.h"

int main()
{
    auto ProgramosStart = hrClock::now();
    vector<mokinys> mok;
    mokinys temp;
    int vieta = 0, choice; 
    cout<<"Ar norite duomenis ivesti ranka, skaityti is failo ar generuoti?(1/2/3)";
    while(choice != 1 && choice!= 2 && choice!= 3)cin>>choice; 
    if (choice == 1)//ivedimas ranka
    {
        input(mok, vieta);
        sort(mok.begin(), mok.end(), compareName);
        try
        {
            print(mok);
        }
        catch(std::domain_error e)
        {
            cout<<endl<<e.what();
        }
        return 0;
    }
    else if(choice == 2)//skaitymas is failo
    {
        auto start = hrClock::now();
        ifstream in("kursiokai3.txt");
        if (!in){
            cout<< "Failas neegzistuoja ! Patikrinkite faila ir bandykite is naujo."; return 1;
        }
        in.ignore(999, '\n');
        while (readData(in, temp))
        {
            mok.push_back(temp);
        }
        sort(mok.begin(), mok.end(), compareName);
        in.close();
        auto stop = hrClock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
        cout<<duration.count()<<endl;
        try
        {
            print(mok);
        }
        catch(std::domain_error e)
        {
            cout<<endl<<e.what();
        }
        return 0;
    }
    else //failu generavimas
    {
        int FileSkc;
        generate(FileSkc);
    }
    auto pabaiga = hrClock::now();
    std::chrono::duration<double> trukme = pabaiga - ProgramosStart;
    cout<<"Programa veike "<< std::setprecision(2) <<trukme.count()<<" sekundziu."<<endl;
}