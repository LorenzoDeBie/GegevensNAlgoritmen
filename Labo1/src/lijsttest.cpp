//testprogramma voor de move- en copy van een een lijst.

#include "lijst.h"

#include <cstdlib>
#include <iostream>
#include <string>

int gemaakt = 0; //aantallen gemaakte en verwijderde knopen.
int verwijderd = 0;

// Wat volgt is een toepassing;
// deze wordt normaal door de gebruiker geschreven.
//class Lijstknoop:public string{
//    int a;
//public:
//    Lijstknoop(){};
//};

Lijst<int> maak()
{
    Lijst<int> l;
    l.voegToe(int(7));
    l.voegToe(int(45));
    l.voegToe(int(15));
    l.voegToe(int(45));
    l.voegToe(int(25));
    l.voegToe(int(35));
    l.voegToe(int(45));
    l.voegToe(int(55));
    gemaakt += 8;
    return l;
};

int main()
{
    std::cerr << "maak met transfer\n";
    Lijst<int> l;
    l = maak();
    Lijstknoop<int>::controle(gemaakt, verwijderd);

    std::cout << l << endl;

    std::cerr << "verwijderen\n";
    l.verwijder(45);
    verwijderd++;
    l.verwijder(123);
    Lijstknoop<int>::controle(gemaakt, verwijderd);

    std::cerr << "Losse oproep maak\n";
    maak();
    verwijderd += 8;
    Lijstknoop<int>::controle(gemaakt, verwijderd);

    std::cerr << "maak() in constructor\n";
    Lijst<int> l2(maak());
    Lijstknoop<int>::controle(gemaakt, verwijderd);

    std::cerr << "duplicaat 1\n";
    l2 = l;
    if (!l2.isClone(l))
        throw("copy levert andere lijst op.");
    verwijderd += 8;
    gemaakt += 7;
    Lijstknoop<int>::controle(gemaakt, verwijderd);

    std::cerr << "duplicaat 2\n";
    l2 = l;
    gemaakt += 7;
    verwijderd += 7;
    Lijstknoop<int>::controle(gemaakt, verwijderd);

    std::cerr << "duplicaat 3\n";
    l2 = l2;
    Lijstknoop<int>::controle(gemaakt, verwijderd);
    l2.schrijf(std::cerr);
    std::cerr << "\n";

    std::cerr << "duplicaat 4\n";
    Lijst<int> l3;
    l3.voegToe(int(99));
    gemaakt++;
    Lijstknoop<int>::controle(gemaakt, verwijderd);
    l3 = l2 = l;
    verwijderd += 8;
    gemaakt += 14;
    Lijstknoop<int>::controle(gemaakt, verwijderd);

    std::cerr << "insertion sort\n";
    l2.insertionsort();
    Lijstknoop<int>::controle(gemaakt, verwijderd);

    std::cerr << "verwijderen\n";
    l.verwijder(45);
    l.verwijder(45);
    l.verwijder(45);
    l.verwijder(45);
    verwijderd += 2;
    Lijstknoop<int>::controle(gemaakt, verwijderd);

    std::cerr << "swappen\n";
    swap(l2, l);
    Lijstknoop<int>::controle(gemaakt, verwijderd);
    l2.schrijf(std::cerr);

    std::cerr << "\nl=move(l2)\n";
    l = move(l2);
    verwijderd += 7;
    Lijstknoop<int>::controle(gemaakt, verwijderd);

    std::cerr << "l=l2\n";
    l = l2;
    verwijderd += 5;
    Lijstknoop<int>::controle(gemaakt, verwijderd);

    verwijderd += 7;
    Lijstknoop<int>::controle(gemaakt, verwijderd);

    std::cout << "OK BOOMER\n";

    //iterator 
    for (auto s : l)
    {
        std::cerr << s << "\n";
    }
    l.schrijf(std::cerr);
    std::cerr << "\n";

    return 0;
}
