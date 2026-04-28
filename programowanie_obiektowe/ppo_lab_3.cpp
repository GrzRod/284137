#include <iostream>
#include <string>

const int liczba = 10;

class Osoba
{
private:
    int indeks;
    std::string imie;
    std::string nazwisko;
    std::string dataUr;
    int wzrost;
public:
    Osoba();
    int getIndeks();
    std::string getImie();
    std::string getNazwisko();
    std::string getDataUr();
    int getWzrost();

    void setIndeks(int indeks);
    void setImie(std::string imie);
    void setNazwisko(std::string nazwisko);
    void setDataUr(std::string dataUr);
    void setWzrost(int wzrost);
};

class ListaObecnosci
{
private:
    Osoba* tabOsob[liczba];
    bool tabObecnosci[liczba];
public:
    ListaObecnosci();
    bool dodajOsobeDoListy(Osoba* osoba);
    void ustawObecnosc(int indeks, bool obecnosc);
    void usunOsobeZListy(int indeks);
    void drukujListe();
};

class InterfejsUzytkownika
{
private:
    Osoba* bazyOsob;
    int maxOsob;
    ListaObecnosci* tabList;
    int maxList;
    int aktywneListy;

    Osoba* znajdzOsobe(int indeks);
public:
    InterfejsUzytkownika(Osoba* bazyOsob, int maxOsob, ListaObecnosci* tabList, int maxList);
    void petla();
};

Osoba::Osoba()
{
    indeks = 0;
    imie = "";
    nazwisko = "";
    dataUr = "";
    wzrost = 0;
}

int Osoba::getIndeks() { return indeks; }
std::string Osoba::getImie() { return imie; }
std::string Osoba::getNazwisko() { return nazwisko; }
std::string Osoba::getDataUr() { return dataUr; }
int Osoba::getWzrost() { return wzrost; }

void Osoba::setIndeks(int indeks)
{
    if ((indeks > 99999 && indeks < 1000000) || indeks == 0)
        this->indeks = indeks;
    else
        std::cout << "Bledne dane\n";
}

void Osoba::setImie(std::string imie)
{
    if ((imie.length() < 20 && imie.length() > 2) || imie == "")
        this->imie = imie;
    else
        std::cout << "Bledne dane\n";
}

void Osoba::setNazwisko(std::string nazwisko)
{
    if ((nazwisko.length() < 20 && nazwisko.length() > 2) || nazwisko == "")
        this->nazwisko = nazwisko;
    else
        std::cout << "Bledne dane\n";
}

void Osoba::setDataUr(std::string dataUr)
{
    if ((dataUr.length() == 10 && dataUr[4] == '-' && dataUr[7] == '-') || dataUr == "")
        this->dataUr = dataUr;
    else
        std::cout << "Bledne dane\n";
}

void Osoba::setWzrost(int wzrost)
{
    if ((wzrost > 120 && wzrost < 220) || wzrost == 0)
        this->wzrost = wzrost;
    else
        std::cout << "Bledne dane\n";
}

ListaObecnosci::ListaObecnosci()
{
    for (int i = 0; i < liczba; i++)
    {
        tabOsob[i] = nullptr;
        tabObecnosci[i] = false;
    }
}

bool ListaObecnosci::dodajOsobeDoListy(Osoba* osoba)
{
    for (int i = 0; i < liczba; i++)
    {
        if (tabOsob[i] != nullptr && tabOsob[i]->getIndeks() == osoba->getIndeks())
            return false; // osoba juz na liscie
    }
    for (int i = 0; i < liczba; i++)
    {
        if (tabOsob[i] == nullptr)
        {
            tabOsob[i] = osoba;
            tabObecnosci[i] = false;
            return true;
        }
    }
    return false;
}

void ListaObecnosci::ustawObecnosc(int indeks, bool obecnosc)
{
    bool ustawiono = false;
    for (int i = 0; i < liczba; i++)
    {
        if (tabOsob[i] != nullptr && tabOsob[i]->getIndeks() == indeks)
        {
            tabObecnosci[i] = obecnosc;
            ustawiono = true;
            break;
        }
    }
    if (ustawiono == false)
    {
        std::cout << "\nBrak takiego indeksu na liscie";
    }
}

void ListaObecnosci::usunOsobeZListy(int indeks)
{
    bool usunieto = false;
    for (int i = 0; i < liczba; i++)
    {
        if (tabOsob[i] != nullptr && tabOsob[i]->getIndeks() == indeks)
        {
            for (int j = i; j < liczba - 1; j++)
            {
                tabOsob[j] = tabOsob[j + 1];
                tabObecnosci[j] = tabObecnosci[j + 1];
            }
            tabOsob[liczba - 1] = nullptr;
            tabObecnosci[liczba - 1] = false;
            usunieto = true;
            break;
        }
    }
    if (usunieto == false)
    {
        std::cout << "\nBrak takiego indeksu";
    }
}

void ListaObecnosci::drukujListe()
{
    for (int i = 0; i < liczba; i++)
    {
        if (tabOsob[i] != nullptr && tabOsob[i]->getIndeks() != 0)
        {
            std::cout << tabOsob[i]->getIndeks() << " " << tabOsob[i]->getImie() << " "
                << tabOsob[i]->getNazwisko() << " " << tabOsob[i]->getDataUr() << " "
                << tabOsob[i]->getWzrost() << " " << tabObecnosci[i] << "\n";
        }
    }
}

InterfejsUzytkownika::InterfejsUzytkownika(Osoba* bazyOsob, int maxOsob, ListaObecnosci* tabList, int maxList)
{
    this->bazyOsob = bazyOsob;
    this->maxOsob = maxOsob;
    this->tabList = tabList;
    this->maxList = maxList;
    this->aktywneListy = 0;
}

Osoba* InterfejsUzytkownika::znajdzOsobe(int indeks)
{
    for (int i = 0; i < maxOsob; i++)
    {
        if (bazyOsob[i].getIndeks() == indeks)
            return &bazyOsob[i];
    }
    return nullptr;
}

void InterfejsUzytkownika::petla()
{
    int indeks;
    int nowyIndeks;
    std::string imie;
    std::string nazwisko;
    std::string dataUr;
    int wzrost;
    bool obecnosc;
    int wybor;
    int nrListy;

    do
    {
        std::cout << "\nMenu:\n1 : Dodawanie osoby do bazy\n2 : Edytowanie osoby w bazie\n3 : Usuwanie osoby z bazy\n4 : Dodawanie listy obecnosci\n5 : Dodawanie osoby do listy\n6 : Ustawianie obecnosci na liscie\n7 : Usuwanie osoby z listy\n8 : Wypisywanie wybranej listy\n0 : Wyjscie\n";
        std::cin >> wybor;

        switch (wybor)
        {
        case 1:
        {
            std::cout << "Podaj indeks : ";
            std::cin >> indeks;
            if (znajdzOsobe(indeks) != nullptr) {
                std::cout << "Osoba o takim indeksie juz istnieje w bazie.\n";
                break;
            }
            Osoba* wolneMiejsce = znajdzOsobe(0);
            if (wolneMiejsce != nullptr)
            {
                std::cout << "Podaj imie: "; std::cin >> imie;
                std::cout << "Podaj nazwisko: "; std::cin >> nazwisko;
                std::cout << "Podaj date urodzenia: "; std::cin >> dataUr;
                std::cout << "Podaj wzrost: "; std::cin >> wzrost;
                wolneMiejsce->setIndeks(indeks);
                wolneMiejsce->setImie(imie);
                wolneMiejsce->setNazwisko(nazwisko);
                wolneMiejsce->setDataUr(dataUr);
                wolneMiejsce->setWzrost(wzrost);
            }
            else
            {
                std::cout << "\nBrak miejsca w bazie glownej";
            }
            break;
        }
        case 2:
        {
            std::cout << "Podaj indeks po ktorym chcesz modyfikowac w bazie: ";
            std::cin >> indeks;
            Osoba* osobaDoEdycji = znajdzOsobe(indeks);
            if (osobaDoEdycji != nullptr)
            {
                std::cout << "Podaj nowy indeks: "; std::cin >> nowyIndeks;
                std::cout << "Podaj imie: "; std::cin >> imie;
                std::cout << "Podaj nazwisko: "; std::cin >> nazwisko;
                std::cout << "Podaj date urodzenia: "; std::cin >> dataUr;
                std::cout << "Podaj wzrost: "; std::cin >> wzrost;
                osobaDoEdycji->setIndeks(nowyIndeks);
                osobaDoEdycji->setImie(imie);
                osobaDoEdycji->setNazwisko(nazwisko);
                osobaDoEdycji->setDataUr(dataUr);
                osobaDoEdycji->setWzrost(wzrost);
            }
            else
            {
                std::cout << "\nBrak takiego indeksu w bazie";
            }
            break;
        }
        case 3:
        {
            std::cout << "Podaj indeks po ktorym chcesz usunac z bazy (i ze wszystkich list): ";
            std::cin >> indeks;
            Osoba* osobaDoUsuniecia = znajdzOsobe(indeks);
            if (osobaDoUsuniecia != nullptr)
            {
                for (int i = 0; i < aktywneListy; i++) {
                    tabList[i].usunOsobeZListy(indeks);
                }
                osobaDoUsuniecia->setIndeks(0);
                osobaDoUsuniecia->setImie("");
                osobaDoUsuniecia->setNazwisko("");
                osobaDoUsuniecia->setDataUr("");
                osobaDoUsuniecia->setWzrost(0);
            }
            else
            {
                std::cout << "\nBrak takiego indeksu";
            }
            break;
        }
        case 4:
        {
            if (aktywneListy < maxList)
            {
                aktywneListy++;
                std::cout << "Dodano nowa liste. Aktywne listy: " << aktywneListy << "\n";
            }
            else
            {
                std::cout << "Brak miejsca na kolejne listy.\n";
            }
            break;
        }
        case 5:
        {
            std::cout << "Podaj indeks osoby do dodania: "; 
            std::cin >> indeks;
            std::cout << "Na ktora liste dodac (1-" << aktywneListy << ")? "; 
            std::cin >> nrListy;
            Osoba* osobaDoDodania = znajdzOsobe(indeks);
            if (osobaDoDodania != nullptr && nrListy > 0 && nrListy <= aktywneListy)
            {
                if (!tabList[nrListy - 1].dodajOsobeDoListy(osobaDoDodania))
                {
                    std::cout << "Nie mozna dodac (brak miejsca lub osoba juz na liscie).\n";
                }
            }
            else
            {
                std::cout << "Nie ma takiej osoby w bazie lub zly numer listy.\n";
            }
            break;
        }
        case 6:
        {
            std::cout << "Podaj indeks po ktorym chcesz ustawic obecnosc na liscie: "; 
            std::cin >> indeks;
            std::cout << "Na ktorej liscie? (1-" << aktywneListy << "): "; 
            std::cin >> nrListy;
            if (nrListy > 0 && nrListy <= aktywneListy)
            {
                std::cout << "Podaj obecnosc (0 lub 1): "; 
                std::cin >> obecnosc;
                tabList[nrListy - 1].ustawObecnosc(indeks, obecnosc);
            }
            else
            {
                std::cout << "Niepoprawny numer listy.\n";
            }
            break;
        }
        case 7:
        {
            std::cout << "Podaj indeks po ktorym chcesz usunac z listy: "; 
            std::cin >> indeks;
            std::cout << "Z ktorej listy? (1-" << aktywneListy << "): "; 
            std::cin >> nrListy;
            if (nrListy > 0 && nrListy <= aktywneListy)
            {
                tabList[nrListy - 1].usunOsobeZListy(indeks);
            }
            else
            {
                std::cout << "Niepoprawny numer listy.\n";
            }
            break;
        }
        case 8:
        {
            std::cout << "Ktora liste wypisac? (1-" << aktywneListy << "): ";
            std::cin >> nrListy;
            if (nrListy > 0 && nrListy <= aktywneListy)
            {
                tabList[nrListy - 1].drukujListe();
            }
            else
            {
                std::cout << "Niepoprawny numer listy.\n";
            }
            break;
        }
        case 0:
            return;
        default:
            std::cout << "Brak takiej opcji";
            break;
        }
    } while (wybor != 0);
}

int main()
{
    Osoba tabOsob[liczba]; 
    ListaObecnosci tabList[2];
    InterfejsUzytkownika ui(tabOsob, liczba, tabList, 2);
    ui.petla(); 
    return 0;
}