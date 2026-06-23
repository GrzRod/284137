// ============================================================
//  Lab: Interfejsy i wzorzec Strategy
//  Paradygmaty Programowania Obiektowego
//
// ============================================================

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ============================================================
//  KLASY PODSTAWOWE
//  Mozesz skopiować tutaj swoje klasy Student i ListaObecnosci,
//  z poprzednich zajec, lub użyć zaproponowanych (uproszczone)
// ============================================================


// ============================================================
// STUDENT
// Bazowa implementacja - tylko podstawowe informacje o studencie
// ustawianie danych przez konstruktor, bez setterów
// ============================================================

class Student {
private:
    string imie;
    string nazwisko;
    string nrIndeksu;

public:
    Student(string imie, string nazwisko, string nrIndeksu)
        : imie(imie), nazwisko(nazwisko), nrIndeksu(nrIndeksu) {
    }

    string getImie() { return imie; }
    string getNazwisko() { return nazwisko; }
    string getNrIndeksu() { return nrIndeksu; }
};


// ============================================================
//  ListaObecnosci
//
//  Prosta implementacja oparta o dwie oddzielne tablice polaczone indeksem:
//    studenci[i]  — wskaznik do obiektu Student
//    obecnosc[i]  — licznik obecnosci studenta i
//
//  Indeksy obu tablic sa zsynchronizowane:
//  obecnosc[2] to liczba obecnosci studenta studenci[2].
// ============================================================
class ListaObecnosci {
private:
    Student** studenci;
    int* obecnosc;
    int       liczba_zajec;
    int       rozmiar;
    int       pojemnosc;
    string nazwa_przedmiotu;

public:
    ListaObecnosci(string nazwa, int pojemnosc)
        : liczba_zajec(0), rozmiar(0), pojemnosc(pojemnosc),
        nazwa_przedmiotu(nazwa) {
        studenci = new Student * [pojemnosc];
        obecnosc = new int[pojemnosc];
        for (int i = 0; i < pojemnosc; i++)
            obecnosc[i] = 0;
    }

    ~ListaObecnosci() {
        for (int i = 0; i < rozmiar; i++)
            delete studenci[i];
        delete[] studenci;
        delete[] obecnosc;
    }

    void dodajStudenta(Student* s) {
        if (rozmiar < pojemnosc)
            studenci[rozmiar++] = s;
    }

    // Zaznacza obecnosc dla jednych zajec.
    // obecni[i] == 1 oznacza ze student studenci[i] byl obecny.
    // obecni[i] == 0 oznacza nieobecnosc.
    void zaznaczObecnosc(int* obecni, int rozmiar_tablicy) {
        liczba_zajec++;
        for (int i = 0; i < rozmiar_tablicy && i < rozmiar; i++)
            if (obecni[i])
                obecnosc[i]++;
    }

    int getLiczbaObecnosci(int i) { return obecnosc[i]; }
    int getLiczbaZajec() { return liczba_zajec; }

    int getProcentObecnosci(int i) {
        if (liczba_zajec == 0) return 0;
        return (obecnosc[i] * 100) / liczba_zajec;
    }

    Student** getStudenci() { return studenci; }
    int* getObecnosc() { return obecnosc; }
    int         getRozmiar() { return rozmiar; }
    string getNazwa() { return nazwa_przedmiotu; }
};


// ============================================================
//  INTERFEJSY
//  Nie modyfikuj tych klas.
// ============================================================

class IFiltr {
public:
    // Zwraca nowa tablice wskaznikow do studentow spelniajacych
    // kryterium. Rozmiar wynikowej tablicy zapisywany jest
    // do *wynik_rozmiar. Wywolujacy jest odpowiedzialny za
    // zwolnienie pamieci tablicy wynikowej (nie obiektow Student).
    virtual Student** filtruj(Student** studenci,
        int* obecnosc,
        int       liczba_zajec,
        int       rozmiar,
        int* wynik_rozmiar) = 0;
};



// ============================================================
//  CZESC 1 — IMPLEMENTACJE IFiltr
//
//  Zaimplementuj jedna z ponizszych klas.
//  UWAGA - każda klasa w swoim konstruktorze powinna przyjmować
//  odpowiewni parametr (prog, litere lub cyfre)
//
//  FiltrProguObecnosci — zwraca studentow ktorych procent
//    obecnosci jest nizszy niz prog podany w konstruktorze
//.   np. FiltrProguObecniosci(50) zwroci studentow ktorzy byli obecni na mniej niz 50% zajec
//
// 
//  JA FILTR NAZWISKA
//  FiltrNazwiska — zwraca studentow ktorych nazwisko
//    zaczyna sie na litere podana w konstruktorze
//    np. FiltrNazwiska('K') zwroci studentow ktorzy mają nazwisko zaczynające się na literę 'K'
//
//  FiltrIndeksu — zwraca studentow ktorych numer indeksu
//    zaczyna sie od ciagu znakow podanego w konstruktorze
//.   np. FiltrIndeksu("12") zwroci studentow ktorzy mają numer indeksu zaczynający się od "12"
// ============================================================


//  PRZYKLAD IMPLEMENTACJI TYPU "STUB"
//  FiltrStub zwraca cala tablice, ktora otrzymal na wejsciu
//

class FiltrStub : public IFiltr {
public:
    Student** filtruj(Student** studenci, int* obecnosc,int liczba_zajec, int rozmiar,int* wynik_rozmiar) 
    {
        Student** wynik = new Student * [rozmiar];
        for (int i = 0; i < rozmiar; i++)
            wynik[i] = studenci[i];
        *wynik_rozmiar = rozmiar;
        return wynik;
    }

};


// TUTAJ ZAIMPLEMENTUJ FILTRY


//filtr progu

class FiltrProguObecnosci : public IFiltr
{
private:
    int prog;
public:
    FiltrProguObecnosci(int prog) : prog(prog) {}

    Student** filtruj(Student** studenci, int* obecnosc,int liczba_zajec, int rozmiar, int* wynik_rozmiar) 
    {
        //ile spelnia
        int liczba_wynikow = 0;
        for (int i = 0; i < rozmiar; i++) 
        {
            int procent = (liczba_zajec == 0) ? 0 : (obecnosc[i] * 100) / liczba_zajec;
            if (procent < prog) 
            {
                liczba_wynikow++;
            }
        }

        //lista seplniajacych
        Student** wynik = new Student * [liczba_wynikow];
        int indeks_wynikowy = 0;

        //uzupelnianie listy
        for (int i = 0; i < rozmiar; i++) 
        {
            int procent = (liczba_zajec == 0) ? 0 : (obecnosc[i] * 100) / liczba_zajec;
            if (procent < prog) 
            {
                wynik[indeks_wynikowy++] = studenci[i];
            }
        }

        *wynik_rozmiar = liczba_wynikow;
        return wynik;
    }
};

//filtr nazwiska

class FiltrNazwisk : public IFiltr
{
private:
    char litera;
public:
    FiltrNazwisk(char litera) : litera(litera) {}

    Student** filtruj(Student** studenci, int* obecnosc,int liczba_zajec, int rozmiar, int* wynik_rozmiar) 
    {
        //ile spelnia
        int liczba_wynikow = 0;
        for (int i = 0; i < rozmiar; i++) 
        {
            string nazwisko = studenci[i]->getNazwisko();
            if (!nazwisko.empty() && nazwisko[0] == litera) 
            {
                liczba_wynikow++;
            }
        }

        //lista spelniajacych
        Student** wynik = new Student * [liczba_wynikow];
        int indeks_wynikowy = 0;

        //uzupelninie listy
        for (int i = 0; i < rozmiar; i++)
        {
            string nazwisko = studenci[i]->getNazwisko();
            if (!nazwisko.empty() && nazwisko[0] == litera) 
            {
                wynik[indeks_wynikowy++] = studenci[i];
            }
        }

        *wynik_rozmiar = liczba_wynikow;
        return wynik;
    }
};

//otrzymane z dc
// filtr indeksu
class FiltrIndeksu : public IFiltr
{
private:
    string poczatek;
public:
    FiltrIndeksu(string s) { poczatek = s; };
    Student** filtruj(Student** studenci, int* obecnosc,
        int liczba_zajec, int rozmiar,
        int* wynik_rozmiar)
    {
        Student** wynik = new Student * [rozmiar];
        for (int i = 0; i < rozmiar; i++)
        {
            if (studenci[i]->getNrIndeksu().rfind(poczatek, 0) == 0)
            {
                wynik[i] = studenci[i];
                (*wynik_rozmiar)++;
            }
        }
        return wynik;
    }
};

// ============================================================
//  MAIN i przyklad filtra
// ============================================================


void testFiltrowania(IFiltr* filtr, ListaObecnosci* lista) {
    int wynik_rozmiar_stub = 0;
    Student** wynikStub = filtr->filtruj(lista->getStudenci(),
        lista->getObecnosc(),
        lista->getLiczbaZajec(),
        lista->getRozmiar(),
        &wynik_rozmiar_stub);

    for (int i = 0; i < wynik_rozmiar_stub; i++) {
        cout << wynikStub[i]->getImie() << endl;
    }

    delete[] wynikStub;
}

//main

int main() {
    ListaObecnosci lista("Paradygmaty Programowania Obiektowego", 10);

    lista.dodajStudenta(new Student("Anna", "Kowalska", "123456"));
    lista.dodajStudenta(new Student("Bartosz", "Nowak", "654321"));
    lista.dodajStudenta(new Student("Celina", "Kwiatkowska", "111111"));
    lista.dodajStudenta(new Student("Damian", "Krawczyk", "222222"));

    // symulacja trzech zajec
    // zajecia 1: Anna, Celina i Damian obecni
    int zajecia1[] = { 1, 0, 1, 1 };
    lista.zaznaczObecnosc(zajecia1, lista.getRozmiar());

    // zajecia 2: tylko Damian obecny
    int zajecia2[] = { 0, 0, 0, 1 };
    lista.zaznaczObecnosc(zajecia2, lista.getRozmiar());

    // zajecia 3: Anna i Celina obecne
    int zajecia3[] = { 1, 0, 1, 0 };
    lista.zaznaczObecnosc(zajecia3, lista.getRozmiar());

    // PRZYKLADY UZYCIA FILTRA, RAPORTU i NOTYFIKATORA na podstawie interfejsów
    //FiltrStub filtrStub;
    //testFiltrowania(&filtrStub, &lista);

    //filtr progu
    //FiltrProguObecnosci filtrProgu(75);
    //testFiltrowania(&filtrProgu, &lista);

    //filtr litery
    //FiltrNazwisk filtrNazwisk('K');
    //testFiltrowania(&filtrNazwisk, &lista);

    //filtr indeksu
    FiltrIndeksu filtrIndeksu("123");
    testFiltrowania(&filtrIndeksu, &lista);
    return 0;
}