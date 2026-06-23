#include <iostream>
#include <string>
#include <fstream>
#include <map>

const int liczba = 10;

//ISerialize zastapione przez IEksportowalny

class IEksportowalny
{
public:
    virtual std::map<std::string, std::string> eksportuj() = 0;
    virtual ~IEksportowalny() = default;
};

class IEksporter
{
public:
    virtual void wykonajEksport(IEksportowalny* obj, std::string sciezka, bool append) = 0;
    virtual ~IEksporter() = default;
};

class EksporterTXT : public IEksporter
{
public:
    void wykonajEksport(IEksportowalny* obj, std::string sciezka, bool append) override
    {
        std::ofstream plik;
        if (append)
        {
            plik.open(sciezka, std::ios_base::app);
        }
        else
        {
            plik.open(sciezka);
        }

        if (plik.is_open())
        {
            std::map<std::string, std::string> dane = obj->eksportuj();
            std::map<std::string, std::string>::iterator it;
            for (it = dane.begin(); it != dane.end(); ++it)
            {
                plik << it->first << ": " << it->second << "\n";
            }
            plik << "---------------------------\n";
            plik.close();
        }
        else
        {
            std::cout << "Blad otwarcia pliku TXT!\n";
        }
    }
};

class EksporterCSV : public IEksporter
{
public:
    void wykonajEksport(IEksportowalny* obj, std::string sciezka, bool append) override
    {
        std::ofstream plik;
        if (append)
        {
            plik.open(sciezka, std::ios_base::app);
        }
        else
        {
            plik.open(sciezka);
        }

        if (plik.is_open())
        {
            std::map<std::string, std::string> dane = obj->eksportuj();
            if (!append)
            {
                for (auto it = dane.begin(); it != dane.end(); ++it)
                {
                    plik << it->first << ";";
                }
                plik << "\n";
            }
            for (auto it = dane.begin(); it != dane.end(); ++it)
            {
                plik << it->second << ";";
            }
            plik << "\n";
            plik.close();
        }
        else
        {
            std::cout << "Blad otwarcia pliku CSV!\n";
        }
    }
};

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

class Student : public Osoba, public IEksportowalny
{
protected:
    int nr_indeksu;
public:
    Student();
    int getId() override;
    void setNrIndeksu(int indeks);
    void drukuj() override;
    std::map<std::string, std::string> eksportuj() override;
};

class StudentZaoczny : public Student
{
public:
    StudentZaoczny();
    std::map<std::string, std::string> eksportuj() override;
};

class Pracownik : public Osoba, public IEksportowalny
{
private:
    int id_pracownika;
public:
    Pracownik();
    int getId() override;
    void setIdPracownika(int id);
    void drukuj() override;
    std::map<std::string, std::string> eksportuj() override;
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
    Osoba* getOsoba(int index)
    {
        if (index >= 0 && index < liczba) return tabOsob[index];
        return nullptr;
    }
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
    void odczytajCalyPlik(std::string nazwaPliku);
    void odczytajLinijke(std::string nazwaPliku, int numerLinii);
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

std::map<std::string, std::string> Student::eksportuj()
{
    std::map<std::string, std::string> dane;
    dane["typ"] = "STUDENT";
    dane["imie"] = imie;
    dane["nazwisko"] = nazwisko;
    dane["dataUr"] = dataUr;
    dane["wzrost"] = std::to_string(wzrost);
    dane["nr_indeksu"] = std::to_string(nr_indeksu);
    return dane;
}

void Student::drukuj()
{
    std::cout << "[Student] Indeks: " << nr_indeksu << ", " << imie << " " << nazwisko << " " << dataUr << " " << wzrost;
}

StudentZaoczny::StudentZaoczny() : Student() {}

std::map<std::string, std::string> StudentZaoczny::eksportuj()
{
    std::map<std::string, std::string> dane = Student::eksportuj();
    dane["typ"] = "STUDENT ZAOCZNY";
    return dane;
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

std::map<std::string, std::string> Pracownik::eksportuj()
{
    std::map<std::string, std::string> dane;
    dane["typ"] = "PRACOWNIK";
    dane["imie"] = imie;
    dane["nazwisko"] = nazwisko;
    dane["dataUr"] = dataUr;
    dane["wzrost"] = std::to_string(wzrost);
    dane["id_pracownika"] = std::to_string(id_pracownika);
    return dane;
}

void Pracownik::drukuj()
{
    std::cout << "[Pracownik] ID: " << id_pracownika << ", " << imie << " " << nazwisko << " " << dataUr << " " << wzrost;
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

void InterfejsUzytkownika::odczytajCalyPlik(std::string nazwaPliku)
{
    std::ifstream plik(nazwaPliku);
    std::string linia;
    if (plik.is_open())
    {
        std::cout << "\n--- Zawartosc pliku '" << nazwaPliku << "' ---\n";
        while (getline(plik, linia))
        {
            std::cout << linia << "\n";
        }
        std::cout << "--------------------------------------\n";
        plik.close();
    }
    else
    {
        std::cout << "Blad otwarcia pliku do odczytu!\n";
    }
}

void InterfejsUzytkownika::odczytajLinijke(std::string nazwaPliku, int numerLinii)
{
    std::ifstream plik(nazwaPliku);
    std::string linia;
    int aktualna = 1;
    if (plik.is_open())
    {
        while (getline(plik, linia))
        {
            if (aktualna == numerLinii)
            {
                std::cout << "\nLinia " << numerLinii << ": " << linia << "\n";
                plik.close();
                return;
            }
            aktualna++;
        }
        std::cout << "Brak linii " << numerLinii << " w pliku.\n";
        plik.close();
    }
    else
    {
        std::cout << "Blad otwarcia pliku do odczytu!\n";
    }
}

void InterfejsUzytkownika::petla()
{
    int id;
    std::string imie, nazwisko, dataUr, nazwaPliku;
    int wzrost, wybor, typ, nrListy, nrLinii;
    bool obecnosc;

    do
    {
        std::cout << "\nMenu:\n"
            << "1 : Dodawanie osoby do bazy\n"
            << "2 : Edytowanie osoby w bazie\n"
            << "3 : Usuwanie osoby z bazy\n"
            << "4 : Dodawanie listy obecnosci\n"
            << "5 : Dodawanie osoby do listy\n"
            << "6 : Ustawianie obecnosci na liscie\n"
            << "7 : Usuwanie osoby z listy\n"
            << "8 : Wypisywanie wybranej listy\n"
            << "9 : Zapisz do pliku (Osobe lub Liste)\n"
            << "10: Odczyt z pliku (calosc)\n"
            << "11: Odczyt z pliku (pojedyncza linia)\n"
            << "0 : Wyjscie\nWybor: ";
        std::cin >> wybor;

        switch (wybor)
        {
        case 1:
        {
            std::cout << "Kogo chcesz dodac? (1 - Student, 2 - Pracownik, 3 - Student Zaoczny): ";
            std::cin >> typ;

            if (typ != 1 && typ != 2 && typ != 3)
            {
                std::cout << "Nieznany typ!\n";
                break;
            }

            std::cout << "Podaj unikalny numer (Indeks / ID): ";
            std::cin >> id;
            if (znajdzOsobe(id) != nullptr)
            {
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
                else if (typ == 2)
                {
                    Pracownik* p = new Pracownik();
                    p->setIdPracownika(id);
                    p->setImie(imie);
                    p->setNazwisko(nazwisko);
                    p->setDataUr(dataUr);
                    p->setWzrost(wzrost);
                    bazyOsob[wolnyIndex] = p;
                }
                else if (typ == 3)
                {
                    StudentZaoczny* sz = new StudentZaoczny();
                    sz->setNrIndeksu(id);
                    sz->setImie(imie);
                    sz->setNazwisko(nazwisko);
                    sz->setDataUr(dataUr);
                    sz->setWzrost(wzrost);
                    bazyOsob[wolnyIndex] = sz;
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
            if (!znaleziono)
            {
                std::cout << "\nBrak takiego ID\n";
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
        case 9:
        {
            int opcjaZapisu, format;
            std::cout << "1 - Zapisz wybrana osobe\n2 - Zapisz cala liste\nWybor: ";
            std::cin >> opcjaZapisu;
            std::cout << "Wybierz format (1 - TXT, 2 - CSV): ";
            std::cin >> format;
            std::cout << "Podaj nazwe pliku: ";
            std::cin >> nazwaPliku;

            IEksporter* eksporter = nullptr;
            if (format == 1)
            {
                eksporter = new EksporterTXT();
            }
            else if (format == 2)
            {
                eksporter = new EksporterCSV();
            }
            else
            {
                std::cout << "Zly format!\n";
                break;
            }

            if (opcjaZapisu == 1)
            {
                std::cout << "Podaj ID osoby: ";
                std::cin >> id;
                Osoba* os = znajdzOsobe(id);
                if (os)
                {
                    IEksportowalny* element = dynamic_cast<IEksportowalny*>(os);
                    if (element)
                    {
                        eksporter->wykonajEksport(element, nazwaPliku, false);
                        std::cout << "Zapisano osobe.\n";
                    }
                }
                else
                {
                    std::cout << "Nie znaleziono osoby o takim ID.\n";
                }
            }
            else if (opcjaZapisu == 2)
            {
                std::cout << "Podaj numer listy (1-" << aktywneListy << "): ";
                std::cin >> nrListy;
                if (nrListy > 0 && nrListy <= aktywneListy)
                {
                    std::ofstream plikCzyszczacy(nazwaPliku);
                    plikCzyszczacy.close();

                    int zapisano = 0;
                    for (int i = 0; i < liczba; i++)
                    {
                        Osoba* os = tabList[nrListy - 1].getOsoba(i);
                        if (os)
                        {
                            IEksportowalny* element = dynamic_cast<IEksportowalny*>(os);
                            if (element)
                            {
                                bool append = (zapisano > 0);
                                eksporter->wykonajEksport(element, nazwaPliku, append);
                                zapisano++;
                            }
                        }
                    }
                    std::cout << "Zapisano liste (" << zapisano << " elementow) do pliku.\n";
                }
                else
                {
                    std::cout << "Niepoprawny numer listy.\n";
                }
            }
            delete eksporter;
            break;
        }
        case 10:
        {
            std::cout << "Podaj nazwe pliku do odczytu: ";
            std::cin >> nazwaPliku;
            odczytajCalyPlik(nazwaPliku);
            break;
        }
        case 11:
        {
            std::cout << "Podaj nazwe pliku do odczytu: ";
            std::cin >> nazwaPliku;
            std::cout << "Podaj numer linii do odczytania: ";
            std::cin >> nrLinii;
            if (nrLinii > 0)
            {
                odczytajLinijke(nazwaPliku, nrLinii);
            }
            else
            {
                std::cout << "Numer linii musi byc wiekszy od 0\n";
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