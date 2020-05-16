#include <iostream>
#include <cmath>
#include <algorithm>
#include <conio.h>
#include <ctime>
#include "Bank.h"

#define SET 1
#define GET 2

template <class ClassName>
void afisare_conturi(ClassName &c) {
    std :: string separator;
    for (int i = 0; i < 36; ++i)
        separator += "_";

    for (auto it = c.begin(); it != c.end(); ++it) {
        std :: cout << *it;
        if (it + 1 != c.end())
            std :: cout << "\n\n" << separator << "\n\n";
    }
}

template <>
void afisare_conturi <std :: vector <cont_economii *>> (std :: vector <cont_economii *> &c) {
    std :: string separator;
    for (int i = 0; i < 36; ++i)
        separator += " ";

    for (auto it = c.begin(); it != c.end(); ++it) {
        if ((*it) -> get_rata_dobanda() == 12)
            std :: cout << dynamic_cast <cont_bancar *> (*it);
        if (it + 1 != c.end())
            std :: cout << "\n\n" << separator << "\n\n";
    }
}

GestionareConturi :: GestionareConturi(std :: string cod, std :: string nume, std :: string cod_bic) {
        cod_tara = cod;
        nume_banca = nume;
        BIC = cod_bic;
        afiseaza_meniu = true;
        numar_conturi = 0;

        functii_actiuni.push_back(&creare_cont);
        functii_actiuni.push_back(&stergere_cont);
        functii_actiuni.push_back(&afisare_cont);
        functii_actiuni.push_back(&afisare_clienti);
        functii_actiuni.push_back(&afisare_clienti_specializare);
        functii_actiuni.push_back(&iesire);

        functii_tipuri_de_conturi.push_back(&creare_cont_economii);
        functii_tipuri_de_conturi.push_back(&creare_cont_curent);

        functii_cautare_clienti.push_back(&verificare_iban);
        functii_cautare_clienti.push_back(&verificare_cnp);
        functii_cautare_clienti.push_back(&verificare_id_cont);
}

void GestionareConturi :: operator += (cont_bancar *c) {
    conturi.push_back(c);
    ++numar_conturi;
}

void GestionareConturi :: mesaj_intampinare() {
    std :: string mesaj = "Gestionarea conturilor deschise la banca " + nume_banca;
    std :: cout << mesaj << ":\n";
    for (unsigned int i = 0; i < mesaj.size() + 1; ++i)
        std :: cout << "=";
    std :: cout << "\n\n";
}

void GestionareConturi :: revenire() {
    std :: cout << "\n\nApasati orice tasta pentru a reveni la ecranul anterior.";
    getch();
    system("cls");
}

int GestionareConturi :: afisare_vector(std :: vector <std :: string> x, std :: string mesaj1, std :: string mesaj2) {
    std :: cout << mesaj1 << ":\n";
    unsigned int i;
    for (i = 0; i < x.size(); ++i)
        std :: cout << i + 1 << ". " << x.at(i) << "\n";
    std :: cout << "> ";
    std :: cin >> i;
    while (i < 1 || i > x.size()) {
        std :: cout << mesaj2 << "\n";
        std :: cout << "> ";
        std :: cin >> i;
    }
    std :: cout << "\n";
    return i;
}

void GestionareConturi :: generare_IBAN() {

    srand(time(NULL));

    for (int i = 0; i < 10; ++i)
        IBAN += std :: to_string(rand() % 10);

    std :: string aux = IBAN;


    IBAN = IBAN.substr(4) + IBAN.substr(0, 2) + "00";
    char l;
    for (unsigned int i = 0; i < IBAN.size(); ++i) {
        l = IBAN.at(i);
        if (l <= 'Z' && l >= 'A')
            IBAN.replace(i, 1, std :: to_string(l - 'A' + 10));
    }

    int check_digits = stoi(IBAN.substr(0, 9));
    IBAN = IBAN.substr(9);

    while (IBAN.size() > 0) {
        check_digits %= 97;
        if (IBAN.size() >= 7) {
            check_digits = check_digits * 10000000 + stoi(IBAN.substr(0, 7));
            IBAN = IBAN.substr(7);
        }
        else {
            check_digits = check_digits * pow(10, IBAN.size()) + stoi(IBAN);
            break;
        }
    }

    check_digits %= 97;

    check_digits = 98 - check_digits;


    if (check_digits < 10)
        aux.replace(2, 2, "0" + std :: to_string(check_digits));
    else
        aux.replace(2, 2, std :: to_string(check_digits));

    IBAN = aux;
}

void GestionareConturi :: creare_cont_economii(int a) {
    int i = afisare_vector(tipuri_dobanzi, "Alege tipul dobanzii", "Tipul de dobanda este inexistent. Reincercati.");
    time_t now = time(0);
    generare_IBAN();
    try {
        *this += new cont_economii(tipuri_de_valuta.at(a), IBAN, now, perioade_dobanzi[i - 1], rate_dobanzi[i - 1], numar_conturi + 1);
    }
    catch (const std :: bad_alloc &) {
        std :: cout << "A fost atins numarul maxim de conturi.";
        revenire();
    }
}

void GestionareConturi :: creare_cont_curent(int a) {
    time_t now = time(0);
    generare_IBAN();
    *this += new cont_curent(tipuri_de_valuta.at(a), IBAN, now, numar_conturi + 1);
}

void GestionareConturi :: alegere_tip_cont() {
    int j = afisare_vector(tipuri_de_valuta, "Alege tipul valutei", "Tipul de valuta este inexistent. Reincercati.");
    IBAN += prescurtari_valute[j - 1];
    int i = afisare_vector(tipuri_de_conturi, "Alege tipul contului", "Tipul de cont este inexistent. Reincercati.");
    IBAN += prescurtari_conturi[i - 1];
   (this ->* functii_tipuri_de_conturi[i - 1])(j - 1);
}

void GestionareConturi :: creare_cont() {
    IBAN = cod_tara + "00" + BIC;
    alegere_tip_cont();
    std :: cin.ignore();
    std :: cin >> conturi.back() -> detinator;
    std :: cout << "\nContul a fost creat cu succes.";
    ++numar_conturi;
    revenire();
}

void GestionareConturi :: verificare_iban(std :: string IBAN) {
    for (unsigned int i = 0; i < conturi.size(); ++i)
        if (conturi.at(i) -> IBAN == IBAN) {
            index_cont = i;
            return;
        }
    index_cont = -1;
    return;
}

void GestionareConturi :: verificare_cnp(std :: string CNP) {
    std :: string search = "Cod numeric personal";
    for (unsigned int i = 0; i < conturi.size(); ++i) {
        if (modify <informatii_personale> (search, *conturi.at(i) -> detinator -> detalii, GET) == CNP) {
                index_cont = i;
                return;
        }
    }
    index_cont = -1;
    return;
}

void GestionareConturi :: verificare_id_cont(std :: string id) {
    long long int id_cont;

    try {
        id_cont = stoll(id);
    }

    catch(const std :: invalid_argument &) {
        std :: cout << "\nID-ul este format doar din numere.\n";
        revenire();
        return;
    }

    for (unsigned int i = 0; i < conturi.size(); ++i)
        if (conturi.at(i) -> id_cont == id_cont) {
            index_cont = i;
            return;
        }

    index_cont = -1;
}

void GestionareConturi :: cautare_cont() {
    std :: string input;
    int i = afisare_vector(criterii_cautare_clienti, "Alege criteriul dupa care se va realiza cautarea contului", "Criteriul este inexistent. Reincercati.");
    std :: cout << "Introdu valoarea cautata:\n> ";
    std :: cin >> input;
    (this ->* functii_cautare_clienti[i - 1])(input);
    return;
}

void GestionareConturi :: afisare_clienti() {
    std :: vector <cont_bancar*> :: iterator it = conturi.begin();
    if (it == conturi.end())
        std :: cout << "Nu exista clienti.";
    else
        std :: cout << (this);
    revenire();
}


void GestionareConturi :: afisare_clienti_specializare() {
    std :: vector <cont_bancar*> :: iterator it = conturi.begin();
    if (it == conturi.end())
        std :: cout << "Nu exista conturi de economii cu rata dobanzii la 1 an.";
    else {
        int i = 0;
        std :: vector <cont_economii *> conturi_economii(conturi.size());
        for (auto it = conturi.begin(); it != conturi.end(); ++it) {
            if (dynamic_cast <cont_economii *> (*it))
                conturi_economii.at(i++) = dynamic_cast <cont_economii *> (*it);
        }
        afisare_conturi (conturi_economii);
        conturi_economii.clear();
    }

    revenire();
}

void GestionareConturi :: afisare_cont() {
    cautare_cont();
    std :: cout << "\n";
    if (index_cont == -1)
        std :: cout << "Contul nu a fost gasit.";
    else
        std :: cout << conturi.at(index_cont);
    revenire();
    return;
}

void GestionareConturi :: stergere_cont() {
    cautare_cont();
    if (index_cont == -1)
        std :: cout << "Contul nu a fost gasit.";
    else {
        delete conturi.at(index_cont);
        for (unsigned int i = index_cont + 1; i < conturi.size(); ++i)
            conturi.at(i - 1) = conturi.at(i);
        conturi.erase(conturi.end() - 1);
        conturi.shrink_to_fit();
        std :: cout << "\nContul a fost sters cu succes.";
        --numar_conturi;
    }
    revenire();
    return;
}

void GestionareConturi :: iesire() {
    std :: cout << "La revedere!";
    afiseaza_meniu = false;
    return;
}

void GestionareConturi :: analizeaza_raspuns() {
    int i = afisare_vector(actiuni, "Alege actiunea dorita", "Tipul de actiune este inexistenta. Reincercati.");

    system("cls");
    (this ->* functii_actiuni[i - 1])();
}

void GestionareConturi :: meniu_principal() {
    while(afiseaza_meniu) {
        mesaj_intampinare();
        analizeaza_raspuns();
    }
}

void cont_bancar :: afisare() {
            std :: cout << detinator;
            std :: cout << "\n\nIBAN: " << IBAN
                    << "\nSold: " << sold << " " << tip_valuta
                    << "\n\nData deschidere: " << data_deschidere -> tm_mday << "/" << data_deschidere -> tm_mon + 1 << "/" << data_deschidere -> tm_year + 1900 << " | "
                    << data_deschidere -> tm_hour << ":" << data_deschidere -> tm_min << ":" << data_deschidere -> tm_sec;
}

cont_bancar :: ~cont_bancar() {
        delete detinator;
}

cont_economii :: cont_economii(std :: string a, std :: string b, time_t c, double d, double e, long long int f) : cont_bancar(a, b, c, f) {
        rata_dobanda = d;
        dobanda = e;
}

cont_curent :: cont_curent(std :: string a, std :: string b, time_t c, long long int d) : cont_bancar(a, b, c, d) {
        numar_tranzactii_gratuite = 10;
}

cont_bancar :: cont_bancar(std :: string a, std :: string b, time_t c, long long int d) {
        sold = 0;
        tip_valuta = a;
        IBAN = b;
        data_deschidere = localtime(&c);
        id_cont = d;
}

std :: ostream &operator << (std :: ostream &out, cont_bancar *c) {
    c -> cont_bancar :: afisare();
    c -> afisare();
    return out;
}

void cont_economii :: afisare() {
    std :: cout << "\n\nRata dobanda: " << rata_dobanda
                << "\nDobanda: " << dobanda;
    std :: vector <std :: pair <int, std :: string>> :: iterator it = istoric.begin();
    while (it != istoric.end())
        std :: cout << "\nSold: " << (*it).first << " | Tranzactie: " << (*it).second;
}

void cont_curent :: afisare() {
    std :: cout << "\n\nNumar tranzactii gratuite ramase: " << numar_tranzactii_gratuite;
}

double cont_economii :: get_rata_dobanda() {
    return rata_dobanda;
}

std :: ostream &operator << (std :: ostream &out, GestionareConturi *b) {
    afisare_conturi(b -> conturi);
    return out;
}


GestionareConturi& GestionareConturi :: operator = (const GestionareConturi &GC) {
    nume_banca = GC.nume_banca;
    index_cont = GC.index_cont;
    numar_conturi = GC.numar_conturi;
    afiseaza_meniu = GC.afiseaza_meniu;
    cod_tara = GC.cod_tara;
    BIC = GC.BIC;
    IBAN = GC.IBAN;
    conturi = GC.conturi;
    functii_actiuni = GC.functii_actiuni;
    functii_tipuri_de_conturi = GC.functii_tipuri_de_conturi;
    functii_cautare_clienti = GC.functii_cautare_clienti;
    return *this;
}

cont_bancar& cont_bancar :: operator = (const cont_bancar &c) {
    detinator = c.detinator;
    IBAN = c.IBAN;
    tip_valuta = c.tip_valuta;
    actiuni = c.actiuni;
    id_cont = c.id_cont;
    data_deschidere = c.data_deschidere;
    sold = c.sold;
    return *this;
}

cont_economii& cont_economii :: operator = (const cont_economii &c) {
    istoric = c.istoric;
    dobanda = c.dobanda;
    rata_dobanda = c.rata_dobanda;
    return *this;
}

cont_curent& cont_curent :: operator = (const cont_curent &c) {
    numar_tranzactii_gratuite = c.numar_tranzactii_gratuite;
    return *this;
}
