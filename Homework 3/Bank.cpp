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

banca :: banca(std :: string cod, std :: string nume, std :: string cod_bic) {
        cod_tara = cod;
        nume_banca = nume;
        BIC = cod_bic;
        numar_conturi = 0;
        afiseaza_meniu = true;

        functii_actiuni.push_back(&creare_cont);
        functii_actiuni.push_back(&stergere_cont);
        functii_actiuni.push_back(&afisare_cont);
        functii_actiuni.push_back(&afisare_clienti);
        functii_actiuni.push_back(&iesire);

        functii_tipuri_de_conturi.push_back(&creare_cont_economii);
        functii_tipuri_de_conturi.push_back(&creare_cont_curent);

        functii_cautare_clienti.push_back(&verificare_iban);
        functii_cautare_clienti.push_back(&verificare_cnp);
        functii_cautare_clienti.push_back(&verificare_id_cont);
}

void banca :: operator += (cont_bancar *c) {
    conturi.push_back(c);
}

void banca :: mesaj_intampinare() {
    std :: string mesaj = "Gestionarea conturilor deschise la banca " + nume_banca;
    std :: cout << mesaj << ":\n";
    for (unsigned int i = 0; i < mesaj.size() + 1; ++i)
        std :: cout << "=";
    std :: cout << "\n\n";
}

void banca :: revenire() {
    std :: cout << "\n\nApasati orice tasta pentru a reveni la ecranul anterior.";
    getch();
    system("cls");
}

int banca :: afisare_vector(std :: vector <std :: string> x, std :: string mesaj1, std :: string mesaj2) {
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

void banca :: generare_IBAN() {

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

void banca :: creare_cont_economii(int a) {
    int i = afisare_vector(tipuri_dobanzi, "Alege tipul dobanzii", "Tipul de dobanda este inexistent. Reincercati.");
    time_t now = time(0);
    generare_IBAN();
    *this += new cont_economii(tipuri_de_valuta.at(a), IBAN, now, perioade_dobanzi[i - 1], rate_dobanzi[i - 1], ++numar_conturi);
}

void banca :: creare_cont_curent(int a) {
    time_t now = time(0);
    generare_IBAN();
    *this += new cont_curent(tipuri_de_valuta.at(a), IBAN, now, ++numar_conturi);
}

void banca :: alegere_tip_cont() {
    int j = afisare_vector(tipuri_de_valuta, "Alege tipul valutei", "Tipul de valuta este inexistent. Reincercati.");
    IBAN += prescurtari_valute[j - 1];
    int i = afisare_vector(tipuri_de_conturi, "Alege tipul contului", "Tipul de cont este inexistent. Reincercati.");
    IBAN += prescurtari_conturi[i - 1];
   (this ->* functii_tipuri_de_conturi[i - 1])(j - 1);
}

void banca :: creare_cont() {
    IBAN = cod_tara + "00" + BIC;
    alegere_tip_cont();
    std :: cin.ignore();
    std :: cin >> conturi.back() -> detinator;
    std :: cout << "\nContul a fost creat cu succes.";
    ++numar_conturi;
    revenire();
}

void banca :: verificare_iban(std :: string IBAN) {
    for (unsigned int i = 0; i < conturi.size(); ++i)
        if (conturi.at(i) -> IBAN == IBAN) {
            index_cont = i;
            return;
        }
    index_cont = -1;
    return;
}

void banca :: verificare_cnp(std :: string CNP) {
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

void banca :: verificare_id_cont(std :: string id) {
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

void banca :: cautare_cont() {
    std :: string input;
    int i = afisare_vector(criterii_cautare_clienti, "Alege criteriul dupa care se va realiza cautarea contului", "Criteriul este inexistent. Reincercati.");
    std :: cout << "Introdu valoarea cautata:\n> ";
    std :: cin >> input;
    (this ->* functii_cautare_clienti[i - 1])(input);
    return;
}

void banca :: afisare_clienti() {
    std :: vector <cont_bancar*> :: iterator it = conturi.begin();
    if (it == conturi.end())
        std :: cout << "Nu exista clienti.";
    else
        afisare_conturi (conturi);
    revenire();
}

void banca :: afisare_cont() {
    cautare_cont();
    std :: cout << "\n";
    if (index_cont == -1)
        std :: cout << "Contul nu a fost gasit.";
    else
        std :: cout << conturi.at(index_cont);
    revenire();
    return;
}

void banca :: stergere_cont() {
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

void banca :: iesire() {
    std :: cout << "La revedere!";
    afiseaza_meniu = false;
    return;
}

void banca :: analizeaza_raspuns() {
    int i = afisare_vector(actiuni, "Alege actiunea dorita", "Tipul de actiune este inexistenta. Reincercati.");

    system("cls");
    (this ->* functii_actiuni[i - 1])();
}

void banca :: meniu_principal() {
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
