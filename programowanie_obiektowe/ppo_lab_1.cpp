#include <iostream>
#include <string>

const int liczba = 10;

void dodajOsobe(int* tabIndeksy, std::string* tabImiona,std::string* tabNazwiska, int indeks, std::string imie, std::string nazwisko)
{
    bool dodano = false;
    for (int i = 0; i < liczba; i++)
    {
        if(tabIndeksy[i] == 0)
        {
            tabIndeksy[i] = indeks;
            tabImiona[i] = imie;
            tabNazwiska[i] = nazwisko;
            dodano = true;
            break;
        }
    }
    if (dodano == false)
    {
        std::cout<<"\nBrak miejsca na liscie";
    }
}

void ustawObecnosc(int* tabIndeksy, bool* tabObecnosci, int indeks, bool obecnosc)
{
    bool ustawiono = false;
    for (int i = 0; i < liczba; i++)
    {
        if(tabIndeksy[i] == indeks)
        {
            tabObecnosci[i] = obecnosc;
            break;
        }
    }
    if (ustawiono == false)
    {
        std::cout<<"\nBrak miejsca na liscie";
    }
}

void drukujListe(int* tabIndeksy, std::string* tabImiona,std::string* tabNazwiska, bool* tabObecnosci)
{
    for (int i = 0; i < liczba; i++)
    {
        if(tabIndeksy[i] != 0)
        {
            std::cout<<"\n"<<tabIndeksy[i]<<tabImiona[i]<<tabNazwiska[i]<<tabObecnosci[i];
        }
        else
        {
            break;
        }
        
    }
}

void edytujElement(int* tabIndeksy, std::string* tabImiona,std::string* tabNazwiska, bool* tabObecnosci, int indeks, int nowyIndeks, std::string imie, std::string nazwisko, bool obecnosc)
{
    for (int i = 0; i < liczba; i++)
    {
        if (tabIndeksy[i] == indeks)
        {
            tabIndeksy[i] = nowyIndeks;
            tabImiona[i] = imie;
            tabNazwiska[i] = nazwisko;
            tabObecnosci[i] = obecnosc;
            break;
        }
    }
    std::cout<<"\nBrak takiego indeksu";
}

void usunElement(int* tabIndeksy, std::string* tabImiona,std::string* tabNazwiska, bool* tabObecnosci, int indeks)
{
    for (int i = 0; i < liczba; i++)
    {
        if (tabIndeksy[i] == indeks)
        {
            for(int j = i; j < liczba - 1; j++)
            {
                if (tabIndeksy[j] != 0)
                {
                    tabIndeksy[j] = tabIndeksy[j + 1];
                    tabImiona[j] = tabImiona[j + 1];
                    tabNazwiska[j] = tabNazwiska[j + 1];
                    tabObecnosci[j] = tabObecnosci[j + 1];
                }
                else
                {
                    break;
                }
            }
            tabIndeksy[liczba - 1] = 0;
            break;
        }
    }
}

int main()
{
    int tabIndeksy[liczba] = {0};
    std::string tabImiona[liczba];
    std::string tabNazwiska[liczba];
    bool tabObecnosci[liczba] = {false};
    int indeks;
    int nowyIndeks;
    std::string imie;
    std::string nazwisko;
    bool obecnosc;
    int wybor;
    do
    {
        std::cout<<"\nMenu:\n1:Dodawanie osoby\n2:Ustawianie obecnosci\n3:Wypisywanie listy\n4:Edytowanie elementu\n5:Usuwanie elementu\n0:Wyjscie";
        std::cin>>wybor;
        switch (wybor)
        {
            case 1:
            {
                std::cout<<"\nPodaj indeks: ";
                std::cin>>indeks;
                std::cout<<"\nPodaj imie: ";
                std::cin>>imie;
                std::cout<<"\nPodaj nazwisko: ";
                std::cin>>nazwisko;
                dodajOsobe(tabIndeksy, tabImiona, tabNazwiska, indeks, imie, nazwisko);
                break;
            }
            case 2:
            {
                std::cout<<"\nPodaj indeks po ktorym chcesz ustawic obecnosc: ";
                std::cin>>indeks;
                std::cout<<"\nPodaj obecnosc (0 lub 1): ";
                std::cin>>obecnosc;
                ustawObecnosc(tabIndeksy, tabObecnosci, indeks, obecnosc);
                break;
            }
            case 3:
            {
                drukujListe(tabIndeksy, tabImiona, tabNazwiska, tabObecnosci);
                break;
            }
            case 4:
            {
                std::cout<<"\nPodaj indeks po ktorym chcesz modyfikowac: ";
                std::cin>>indeks;
                std::cout<<"\nPodaj indeks ";
                std::cin>>nowyIndeks;
                std::cout<<"\nPodaj imie: ";
                std::cin>>imie;
                std::cout<<"\nPodaj nazwisko: ";
                std::cin>>nazwisko;
                std::cout<<"\nPodaj obecnosc (0 lub 1): ";
                std::cin>>obecnosc;
                edytujElement(tabIndeksy, tabImiona, tabNazwiska, tabObecnosci, indeks, nowyIndeks, imie, nazwisko, obecnosc);
                break;
            }
            case 5:
            {
                std::cout<<"\nPodaj indeks po ktorym chcesz usunac: ";
                std::cin>>indeks;
                usunElement(tabIndeksy, tabImiona, tabNazwiska, tabObecnosci, indeks);
                break;
            }
            case 0:
                return 0;
            default:
                std::cout<<"\nBrak takiej opcji";
                break;
        }
    }
    while (wybor != 0);
}