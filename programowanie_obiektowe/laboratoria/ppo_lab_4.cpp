#include <iostream>
#include <string>

const int liczba = 10;

class IPredstawialny
{
public:
    virtual std::string przedstawSie() = 0;
    virtual ~IPredstawialny() = default;
};

void drukuj_obj(IPredstawialny* obj)
{
    std::cout << obj->przedstawSie();
}


class Osoba
{
protected:
    std::string imie;
    std::string nazwisko;
    std::string dataUr;
    int wzrost;
public:
    Osoba();
    virtual ~Osoba() = default;
    virtual int getId() = 0;
    virtual void drukuj();

    std::string getImie();
    std::string getNazwisko();
    std::string getDataUr();
    int getWzrost();

    void setImie(std::string imie);
    void setNazwisko(std::string nazwisko);
    void setDataUr(std::string dataUr);
    void setWzrost(int wzrost);
};

class Student : public Osoba, public IPredstawialny
{
private:
    int nr_indeksu;
public:
    Student();
    int getId() override;
    void setNrIndeksu(int indeks);
    void drukuj() override;

    std::string przedstawSie() override;
};

class Pracownik : public Osoba, public IPredstawialny
{
private:
    int id_pracownika;
public:
    Pracownik();
    int getId() override;
    void setIdPracownika(int id);
    void drukuj() override;

    std::string przedstawSie() override;
};

class ListaObecnosci
{
private:
    Osoba* tabOsob[liczba];
    bool tabObecnosci[liczba];
public:
    ListaObecnosci();
    bool dodajOsobeDoListy(Osoba* osoba);
    void ustawObecnosc(int id, bool obecnosc);
    void usunOsobeZListy(int id);
    void drukujListe();
};

class InterfejsUzytkownika
{
private:
    Osoba** bazyOsob;
    int maxOsob;
    ListaObecnosci* tabList;
    int maxList;
    int aktywneListy;

    Osoba* znajdzOsobe(int id);
public:
    InterfejsUzytkownika(Osoba** bazyOsob, int maxOsob, ListaObecnosci* tabList, int maxList);
    void petla();
};

Osoba::Osoba()
{
    imie = "";
    nazwisko = "";
    dataUr = "";
    wzrost = 0;
}

std::string Osoba::getImie() 
{ 
    return imie; 
}
std::string Osoba::getNazwisko() 
{ 
    return nazwisko; 
}
std::string Osoba::getDataUr() 
{ 
    return dataUr; 
}
int Osoba::getWzrost() 
{ 
    return wzrost; 
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

void Osoba::drukuj()
{
    std::cout << imie << " " << nazwisko << " " << dataUr << " " << wzrost;
}

Student::Student() : Osoba()
{
    nr_indeksu = 0;
}

int Student::getId()
{
    return nr_indeksu;
}

void Student::setNrIndeksu(int indeks)
{
    if ((indeks > 99999 && indeks < 1000000) || indeks == 0)
        this->nr_indeksu = indeks;
    else
        std::cout << "Bledne dane (indeks)\n";
}

std::string Student::przedstawSie()
{
    return "[Student] Indeks: " + std::to_string(nr_indeksu) + ", " + imie + " " + nazwisko + " " + dataUr + " " + std::to_string(wzrost);
}

void Student::drukuj()
{
    drukuj_obj(this);
}

Pracownik::Pracownik() : Osoba()
{
    id_pracownika = 0;
}

int Pracownik::getId()
{
    return id_pracownika;
}

void Pracownik::setIdPracownika(int id)
{
    if ((id > 99999 && id < 1000000) || id == 0)
        this->id_pracownika = id;
    else
        std::cout << "Bledne dane (id)\n";
}

std::string Pracownik::przedstawSie()
{
    return "[Pracownik] ID: " + std::to_string(id_pracownika) + ", " + imie + " " + nazwisko + " " + dataUr + " " + std::to_string(wzrost);
}

void Pracownik::drukuj()
{
    drukuj_obj(this);
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
        if (tabOsob[i] != nullptr && tabOsob[i]->getId() == osoba->getId())
            return false;
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

void ListaObecnosci::ustawObecnosc(int id, bool obecnosc)
{
    bool ustawiono = false;
    for (int i = 0; i < liczba; i++)
    {
        if (tabOsob[i] != nullptr && tabOsob[i]->getId() == id)
        {
            tabObecnosci[i] = obecnosc;
            ustawiono = true;
            break;
        }
    }
    if (!ustawiono)
    {
        std::cout << "\nBrak takiego ID na liscie\n";
    }
}

void ListaObecnosci::usunOsobeZListy(int id)
{
    bool usunieto = false;
    for (int i = 0; i < liczba; i++)
    {
        if (tabOsob[i] != nullptr && tabOsob[i]->getId() == id)
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
    if (!usunieto)
    {
        std::cout << "\nBrak takiego ID\n";
    }
}

void ListaObecnosci::drukujListe()
{
    for (int i = 0; i < liczba; i++)
    {
        if (tabOsob[i] != nullptr)
        {
            tabOsob[i]->drukuj();
            std::cout << " | Obecnosc: " << (tabObecnosci[i] ? "Tak" : "Nie") << "\n";
        }
    }
}

InterfejsUzytkownika::InterfejsUzytkownika(Osoba** bazyOsob, int maxOsob, ListaObecnosci* tabList, int maxList)
{
    this->bazyOsob = bazyOsob;
    this->maxOsob = maxOsob;
    this->tabList = tabList;
    this->maxList = maxList;
    this->aktywneListy = 0;
}

Osoba* InterfejsUzytkownika::znajdzOsobe(int id)
{
    for (int i = 0; i < maxOsob; i++)
    {
        if (bazyOsob[i] != nullptr && bazyOsob[i]->getId() == id)
            return bazyOsob[i];
    }
    return nullptr;
}

void InterfejsUzytkownika::petla()
{
    int id;
    std::string imie, nazwisko, dataUr;
    int wzrost, wybor, typ, nrListy;
    bool obecnosc;

    do
    {
        std::cout << "\nMenu:\n1 : Dodawanie osoby do bazy\n2 : Edytowanie osoby w bazie\n3 : Usuwanie osoby z bazy\n4 : Dodawanie listy obecnosci\n5 : Dodawanie osoby do listy\n6 : Ustawianie obecnosci na liscie\n7 : Usuwanie osoby z listy\n8 : Wypisywanie wybranej listy\n0 : Wyjscie\n";
        std::cin >> wybor;

        switch (wybor)
        {
        case 1:
        {
            std::cout << "Kogo chcesz dodac? (1 - Student, 2 - Pracownik): ";
            std::cin >> typ;

            if (typ != 1 && typ != 2) {
                std::cout << "Nieznany typ!\n";
                break;
            }

            std::cout << "Podaj unikalny numer (Indeks / ID): ";
            std::cin >> id;
            if (znajdzOsobe(id) != nullptr) {
                std::cout << "Osoba o takim ID juz istnieje w bazie.\n";
                break;
            }

            int wolnyIndex = -1;
            for (int i = 0; i < maxOsob; i++)
            {
                if (bazyOsob[i] == nullptr)
                {
                    wolnyIndex = i;
                    break;
                }
            }

            if (wolnyIndex != -1)
            {
                std::cout << "Podaj imie: "; std::cin >> imie;
                std::cout << "Podaj nazwisko: "; std::cin >> nazwisko;
                std::cout << "Podaj date urodzenia: "; std::cin >> dataUr;
                std::cout << "Podaj wzrost: "; std::cin >> wzrost;

                if (typ == 1)
                {
                    Student* s = new Student();
                    s->setNrIndeksu(id);
                    s->setImie(imie);
                    s->setNazwisko(nazwisko);
                    s->setDataUr(dataUr);
                    s->setWzrost(wzrost);
                    bazyOsob[wolnyIndex] = s;
                }
                else
                {
                    Pracownik* p = new Pracownik();
                    p->setIdPracownika(id);
                    p->setImie(imie);
                    p->setNazwisko(nazwisko);
                    p->setDataUr(dataUr);
                    p->setWzrost(wzrost);
                    bazyOsob[wolnyIndex] = p;
                }
            }
            else
            {
                std::cout << "\nBrak miejsca w bazie glownej\n";
            }
            break;
        }
        case 2:
        {
            std::cout << "Podaj ID osoby do edycji: ";
            std::cin >> id;
            Osoba* osobaDoEdycji = znajdzOsobe(id);
            if (osobaDoEdycji != nullptr)
            {
                std::cout << "Podaj nowe imie: "; std::cin >> imie;
                std::cout << "Podaj nowe nazwisko: "; std::cin >> nazwisko;
                std::cout << "Podaj nowa date urodzenia: "; std::cin >> dataUr;
                std::cout << "Podaj nowy wzrost: "; std::cin >> wzrost;
                osobaDoEdycji->setImie(imie);
                osobaDoEdycji->setNazwisko(nazwisko);
                osobaDoEdycji->setDataUr(dataUr);
                osobaDoEdycji->setWzrost(wzrost);
                std::cout << "Dane zaktualizowane (ID pozostalo bez zmian).\n";
            }
            else
            {
                std::cout << "\nBrak takiego ID w bazie\n";
            }
            break;
        }
        case 3:
        {
            std::cout << "Podaj ID do usuniecia z bazy (i ze wszystkich list): ";
            std::cin >> id;

            for (int i = 0; i < aktywneListy; i++)
            {
                tabList[i].usunOsobeZListy(id);
            }

            bool znaleziono = false;
            for (int i = 0; i < maxOsob; i++)
            {
                if (bazyOsob[i] != nullptr && bazyOsob[i]->getId() == id)
                {
                    delete bazyOsob[i];
                    bazyOsob[i] = nullptr;
                    znaleziono = true;
                    std::cout << "Usunieto z bazy.\n";
                    break;
                }
            }
            if (!znaleziono) std::cout << "\nBrak takiego ID\n";
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
            std::cout << "Podaj ID (indeks/nr pracownika) do dodania: ";
            std::cin >> id;
            std::cout << "Na ktora liste dodac (1-" << aktywneListy << ")? ";
            std::cin >> nrListy;
            Osoba* osobaDoDodania = znajdzOsobe(id);
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
            std::cout << "Podaj ID (indeks/nr pracownika), by ustawic obecnosc na liscie: ";
            std::cin >> id;
            std::cout << "Na ktorej liscie? (1-" << aktywneListy << "): ";
            std::cin >> nrListy;
            if (nrListy > 0 && nrListy <= aktywneListy)
            {
                std::cout << "Podaj obecnosc (0 lub 1): ";
                std::cin >> obecnosc;
                tabList[nrListy - 1].ustawObecnosc(id, obecnosc);
            }
            else
            {
                std::cout << "Niepoprawny numer listy.\n";
            }
            break;
        }
        case 7:
        {
            std::cout << "Podaj ID, ktore chcesz usunac z listy: ";
            std::cin >> id;
            std::cout << "Z ktorej listy? (1-" << aktywneListy << "): ";
            std::cin >> nrListy;
            if (nrListy > 0 && nrListy <= aktywneListy)
            {
                tabList[nrListy - 1].usunOsobeZListy(id);
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
            std::cout << "Brak takiej opcji\n";
            break;
        }
    } while (wybor != 0);
}

int main()
{
    Osoba* tabOsob[liczba];
    for (int i = 0; i < liczba; i++)
    {
        tabOsob[i] = nullptr;
    }

    ListaObecnosci tabList[2];
    InterfejsUzytkownika ui(tabOsob, liczba, tabList, 2);
    ui.petla();

    for (int i = 0; i < liczba; i++)
    {
        if (tabOsob[i] != nullptr)
        {
            delete tabOsob[i];
        }
    }

    return 0;
}