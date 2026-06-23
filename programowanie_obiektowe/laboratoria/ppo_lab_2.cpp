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

int Osoba::getIndeks()
{
    return indeks;
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

void Osoba::setIndeks(int indeks)
{
    if ((indeks > 99999 && indeks < 1000000) || indeks == 0)
    {
        this->indeks = indeks;
    }
    else
    {
        std::cout << "Bledne dane\n";
    }
}

void Osoba::setImie(std::string imie)
{
    if ((imie.length() < 20 && imie.length() > 2) || imie == "")
    {
        this->imie = imie;
    }
    else
    {
        std::cout << "Bledne dane\n";
    }
}

void Osoba::setNazwisko(std::string nazwisko)
{
    if ((nazwisko.length() < 20 && nazwisko.length() > 2) || nazwisko == "")
    {
        this->nazwisko = nazwisko;
    }
    else
    {
        std::cout << "Bledne dane\n";
    }
}

void Osoba::setDataUr(std::string dataUr)
{
    if ((dataUr.length() == 10 && dataUr[4] == '-' && dataUr[7] == '-') || dataUr == "")
    {
        this->dataUr = dataUr;
    }
    else
    {
        std::cout << "Bledne dane\n";
    }
}

void Osoba::setWzrost(int wzrost)
{
    if ((wzrost > 120 && wzrost < 220) || wzrost == 0)
    {
        this->wzrost = wzrost;
    }
    else
    {
        std::cout << "Bledne dane\n";
    }
}

void dodajOsobe(Osoba osoby[], int indeks, std::string imie, std::string nazwisko, std::string dataUr, int wzrost)
{
    bool dodano = false;
    for (int i = 0; i < liczba; i++)
    {
        if (osoby[i].getIndeks() == 0)
        {
            osoby[i].setIndeks(indeks);
            osoby[i].setImie(imie);
            osoby[i].setNazwisko(nazwisko);
			osoby[i].setDataUr(dataUr);
			osoby[i].setWzrost(wzrost);
            dodano = true;
            break;
        }
    }
    if (dodano == false)
    {
        std::cout << "\nBrak miejsca na liscie";
    }
}
void ustawObecnosc(Osoba osoby[], bool* tabObecnosci, int indeks, bool obecnosc)
{
    bool ustawiono = false;
    for (int i = 0; i < liczba; i++)
    {
        if (osoby[i].getIndeks() == indeks)
        {
            tabObecnosci[i] = obecnosc;
            ustawiono = true;
            break;
        }
    }
    if (ustawiono == false)
    {
        std::cout << "\nBrak takiego indeksu";
    }
}

void drukujListe(Osoba osoby[], bool* tabObecnosci)
{
    for (int i = 0; i < liczba; i++)
    {
        if (osoby[i].getIndeks() != 0)
        {
            std::cout << osoby[i].getIndeks() << " " << osoby[i].getImie()<< " " << osoby[i].getNazwisko() << " " << osoby[i].getDataUr() << " " << osoby[i].getWzrost() << " " << tabObecnosci[i] << "\n";
        }
        else
        {
            break;
        }
    }
}

void edytujElement(Osoba osoby[],bool* tabObecnosci , int indeks, int nowyIndeks, std::string imie, std::string nazwisko, std::string dataUr, int wzrost, bool obecnosc)
{
    bool edytowano = false;
    for (int i = 0; i < liczba; i++)
    {
        if (osoby[i].getIndeks() == indeks)
        {
            osoby[i].setIndeks(nowyIndeks);
            osoby[i].setImie(imie);
            osoby[i].setNazwisko(nazwisko);
            osoby[i].setDataUr(dataUr);
            osoby[i].setWzrost(wzrost);
            tabObecnosci[i] = obecnosc;
			edytowano = true;
            break;
        }
    }
    if (edytowano == false)
    {
        std::cout << "\nBrak takiego indeksu";
    }
}

void usunElement(Osoba osoby[], bool* tabObecnosci, int indeks)
{
    bool usunieto = false;
    for (int i = 0; i < liczba; i++)
    {
        if (osoby[i].getIndeks() == indeks)
        {
            for (int j = i; j < liczba - 1; j++)
            {
                if (osoby[j + 1].getIndeks() != 0)
                {
                    usunieto = true;
                    osoby[j].setIndeks(osoby[j + 1].getIndeks());
                    osoby[j].setImie(osoby[j + 1].getImie());
                    osoby[j].setNazwisko(osoby[j + 1].getNazwisko());
                    osoby[j].setDataUr(osoby[j + 1].getDataUr());
                    osoby[j].setWzrost(osoby[j + 1].getWzrost());
                    tabObecnosci[j] = tabObecnosci[j + 1];
                }
                else
                {
                    break;
                }
            }
            osoby[liczba - 1].setIndeks(0);
            osoby[liczba - 1].setImie("");
            osoby[liczba - 1].setNazwisko("");
            osoby[liczba - 1].setDataUr("");
            osoby[liczba - 1].setWzrost(0);
            break;
        }
    }
    if (usunieto == false)
    {
        std::cout << "\nBrak takiego indeksu";
    }
}

int main()
{
    Osoba osoby[liczba];
    for (int i = 0; i < liczba; i++)
    {
        osoby[i].setIndeks(0);
        osoby[i].setImie("");
        osoby[i].setNazwisko("");
        osoby[i].setDataUr("");
        osoby[i].setWzrost(0);
    }
    bool tabObecnosci[liczba] = {false};
    int indeks;
    int nowyIndeks;
    std::string imie;
    std::string nazwisko;
    std::string dataUr;
    int wzrost;
    bool obecnosc;
    int wybor;
    do
    {
        std::cout << "\nMenu:\n1 : Dodawanie osoby\n2 : Ustawianie obecnosci\n3 : Wypisywanie listy\n4 : Edytowanie elementu\n5 : Usuwanie elementu\n0 : Wyjscie\n";
        std::cin >> wybor;
        switch (wybor)
        {
        case 1:
        {
            std::cout << "Podaj indeks : ";
            std::cin >> indeks;
            std::cout << "Podaj imie: ";
            std::cin >> imie;
            std::cout << "Podaj nazwisko: ";
            std::cin >> nazwisko;
            std::cout << "Podaj date urodzenia: ";
            std::cin >> dataUr;
            std::cout << "Podaj wzrost: ";
            std::cin >> wzrost;
            dodajOsobe(osoby, indeks, imie, nazwisko, dataUr, wzrost);
            break;
        }
        case 2:
        {
            std::cout << "Podaj indeks po ktorym chcesz ustawic obecnosc: ";
            std::cin >> indeks;
            std::cout << "Podaj obecnosc (0 lub 1): ";
            std::cin >> obecnosc;
            ustawObecnosc(osoby, tabObecnosci, indeks, obecnosc);
            break;
        }
        case 3:
        {
            drukujListe(osoby, tabObecnosci);
            break;
        }
        case 4:
        {
            std::cout << "Podaj indeks po ktorym chcesz modyfikowac: ";
            std::cin >> indeks;
            std::cout << "Podaj indeks: ";
            std::cin >> nowyIndeks;
            std::cout << "Podaj imie: ";
            std::cin >> imie;
            std::cout << "Podaj nazwisko: ";
            std::cin >> nazwisko;
            std::cout << "Podaj date urodzenia: ";
            std::cin >> dataUr;
            std::cout << "Podaj wzrost: ";
            std::cin >> wzrost;
            std::cout << "Podaj obecnosc (0 lub 1): ";
            std::cin >> obecnosc;
            edytujElement(osoby, tabObecnosci, indeks, nowyIndeks, imie, nazwisko, dataUr, wzrost, obecnosc);
            break;
        }
        case 5:
        {
            std::cout << "Podaj indeks po ktorym chcesz usunac: ";
            std::cin >> indeks;
            usunElement(osoby, tabObecnosci, indeks);
            break;
        }
        case 0:
            return 0;
        default:
            std::cout << "Brak takiej opcji";
            break;
        }
    } while (wybor != 0);
}