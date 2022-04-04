#include "funkcijos.h"
#include "mokiniai.h"

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
        sort(mok.begin(), mok.end(), compareName);
    }
    else
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
    }
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