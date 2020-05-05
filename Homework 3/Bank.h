#ifndef BANK_H_INCLUDED
#define BANK_H_INCLUDED

#include "Client.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>

class cont_bancar;

class banca {
public:
    int index_cont;
    long long int numar_conturi;
    bool afiseaza_meniu;
    std :: string nume_banca, cod_tara, BIC, IBAN;
    std :: vector <cont_bancar*> conturi;
    std :: vector <std :: string> actiuni = {"Creare cont nou", "Stergere cont", "Afisare cont", "Afisare clienti", "Iesire"},
                                tipuri_de_valuta = {"Lei", "Euro", "Lire sterline"},
                                prescurtari_valute = {"RON", "EUR", "GBP"},
                                tipuri_de_conturi = {"Cont de economii", "Cont curent"},
                                prescurtari_conturi = {"ECN", "CRT"},
                                tipuri_dobanzi = {"3 luni", "6 luni", "1 an"},
                                criterii_cautare_clienti = {"IBAN", "CNP", "ID"};

    std :: vector <int> perioade_dobanzi = {3, 6, 12};
    std :: vector <double> rate_dobanzi = {0.2, 0.4, 0.8};
    std :: vector <void (banca :: *)()> functii_actiuni;
    std :: vector <void (banca :: *)(int)> functii_tipuri_de_conturi;
    std :: vector <void (banca :: *)(std :: string)> functii_cautare_clienti;


    int afisare_vector(std :: vector <std :: string> x, std :: string mesaj1, std :: string mesaj2);
    void alegere_tip_cont();
    void generare_IBAN();
    void stergere_cont();
    void creare_cont();
    void afisare_cont();
    void afisare_clienti();
    void cautare_cont();
    void revenire();
    void iesire();

    void creare_cont_economii(int);
    void creare_cont_curent(int);

    void verificare_iban(std :: string);
    void verificare_cnp(std :: string);
    void verificare_id_cont(std :: string);

    void mesaj_intampinare();
    void analizeaza_raspuns();
    void afisare_actiuni();

public:

    banca(std :: string cod, std :: string nume, std :: string cod_bic);

    ~banca() {}

    void meniu_principal();

    void operator += (cont_bancar *c);

};

class cont_bancar{
public:
    client *detinator = new client;
    std :: string IBAN, tip_valuta;
    long long int id_cont;
    const tm* data_deschidere;
    double sold;
public:
    cont_bancar(std :: string a, std :: string b, time_t c, long long int d);

    virtual ~cont_bancar();

    virtual void afisare();

    friend std :: ostream &operator << (std :: ostream &out, cont_bancar *c);
};

class cont_economii : public cont_bancar {
    std :: vector <std :: pair<int, std :: string>> istoric;
    double dobanda, rata_dobanda;
public:

    cont_economii(std :: string a, std :: string b, time_t c, double d, double e, long long int f);

    void afisare();

};

class cont_curent : public cont_bancar {
    int numar_tranzactii_gratuite;
public:

    cont_curent(std :: string a, std :: string b, time_t c, long long int d);

    void afisare();
};


#endif // BANK_H_INCLUDED
