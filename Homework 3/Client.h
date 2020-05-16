#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>

template <class ClassName>
std :: string modify(std :: string lookup, ClassName &c, int action);

class adresa {
    std :: vector <std :: pair <std :: string, std :: string>> detalii;
    std :: vector <std :: string> data = {"Tara", "Oras", "Adresa"};
public:

    adresa();
    ~adresa();

    template <class ClassName>
    friend std :: string modify(std :: string lookup, ClassName &c, int action);

    friend std :: istream &operator >> (std :: istream &in, adresa &a);
    friend std :: ostream &operator << (std :: ostream &out, adresa &a);

    adresa& operator = (const adresa &a);
};

class informatii_personale {
    std :: vector <std :: pair <std :: string, std :: string>> detalii;
    std :: vector <std :: string> data = {"Nume", "Prenume", "Varsta", "Numar de telefon", "Cod numeric personal", "Seria", "Numarul"};
public:

    informatii_personale();
    ~informatii_personale();

    template <class ClassName>
    friend std :: string modify(std :: string lookup, ClassName &c, int action);

    friend std :: istream &operator >> (std :: istream &in, informatii_personale &i);
    friend std :: ostream &operator << (std :: ostream &out, informatii_personale &i);

    informatii_personale& operator = (const informatii_personale &i);
};

class client {
protected:
    adresa *locatie = new adresa;
    informatii_personale *detalii = new informatii_personale;
    friend class GestionareConturi;
public:

    friend std :: istream &operator >> (std :: istream &in, client *c);
    friend std :: ostream &operator << (std :: ostream &out, const client *c);

    client& operator = (const client &c);
};

#endif // CLIENT_H_INCLUDED
