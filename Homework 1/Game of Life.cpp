#include <iostream>
#include <math.h>
#include <conio.h>
#include <ctime>
#include <windows.h>

#define dimX 30
#define dimY 70

#define VarstaMaxima 20
#define EnergieInitiala 20

#define PragUnFiu 50
#define PragDoiFii 60
#define PragTreiFii 80
#define PragPatruFii 100

#define EnergieNecesaraInmultirii 10

#define EnergieImbatranire 2


class individ {

private:

    /// Declar toate variabilele, antetele metodelor cerute si constructorii necesari.

    int i, j, varsta;
    double energie;
    char tip;
    unsigned char viu;
    void hraneste(individ **Individ, int m, int n);
    void inmulteste(individ **Individ, int m, int n);
    void ataca(individ **Individ);
    void imbatraneste();
    void moare();

public:

    individ () {
        i = -1;
        j = -1;
        tip = '?';
        energie = -1;
        varsta = -1;
        viu = 0;
    }

    individ(int a, int b, char c) {
        i = a;
        j = b;
        tip = c;
        energie = EnergieInitiala;
        varsta = 0;
        viu = 1;
    }

    void actualizare(individ **Individ, int m, int n);
    int esteviu();
    char gettip();
    void NObiecte(int n);

    friend std :: istream & operator >> (std :: istream &in, individ &I);
    friend std :: ostream & operator << (std :: ostream &out, const individ &I);

    individ (const individ &x) {
        i = x.i;
        j = x.j;
        tip = x.tip;
        energie = x.energie;
        varsta = x.varsta;
        viu = x.viu;
    }

};

class tabla {

    /// Aceasta clasa a fost realizata pentru a initializa un tablou bidimensional de indivizi, a-l actualiza si a-l verifica constant daca mai contine indivizi.
    /// Afisarea tablei reprezinta afisarea valorii lui 'viu' pentru fiecare Individ[i][j]. (i.e. 1 sau 0)

private:

    int m, n, i, j;
    individ **Individ;

public:

    tabla () {}
    tabla(int a, int b) {

        m = a;
        n = b;

        Individ = new individ*[m + 2];
        for (int i = 0; i <= m + 2; i += 1)
            Individ[i] = new individ[n + 2];
    }

    ~tabla() {}

    void initializare();
    void afisare();
    void actualizare();
    int verifica_existenta_indivizi();

};

/// Metode pentru clasa 'individ'.

void individ :: hraneste(individ **Individ, int m, int n) {

    /// Aceasta metoda calculeaza aportul energetic si creste energia individului de pe pozitia (i, j) conform unei formule.

    int aport_energetic = 0;
    if (Individ[i - 1][j].esteviu() != 1 && i - 1 >= 1) aport_energetic += 1;
    if (Individ[i + 1][j].esteviu() != 1 && i + 1 <= m) aport_energetic += 1;
    if (Individ[i][j - 1].esteviu() != 1 && j - 1 >= 1) aport_energetic += 1;
    if (Individ[i][j + 1].esteviu() != 1 && j + 1 <= n) aport_energetic += 1;

    energie += aport_energetic * abs(VarstaMaxima/2 - varsta) / 10;

}

void individ :: inmulteste(individ **Individ, int m, int n) {

    /// Aceasta metoda calculeaza numarul de fii care pot fi alocati [i.e. numarul de pozitii libere invecinate cu (i,j)].
    /// Pentru fiecare pozitie invecinata cu (i, j), verificam daca individul exista (prin faptul ca nu depasim marginile matricei) si,
    /// daca mai putem crea fii, ii alocam corespunzator.

    int numar_fii_alocati = 0, formula_fii = energie * abs(VarstaMaxima / 2 - varsta) / 4;

    if (formula_fii > PragUnFiu) numar_fii_alocati += 1;

    if (formula_fii > PragDoiFii) numar_fii_alocati += 1;

    if (formula_fii > PragTreiFii) numar_fii_alocati += 1;

    if (formula_fii > PragPatruFii) numar_fii_alocati += 1;

    if (numar_fii_alocati > 0 && Individ[i - 1][j].esteviu() == 0 && energie >= EnergieNecesaraInmultirii && i - 1 >= 1) {
        Individ[i - 1][j] = individ(i - 1, j, gettip());
        energie -= EnergieNecesaraInmultirii;
        numar_fii_alocati -= 1;
    }

    if (numar_fii_alocati > 0 && Individ[i][j - 1].esteviu() == 0 && energie >= EnergieNecesaraInmultirii && j - 1 >= 1) {
        Individ[i][j - 1] = individ(i, j - 1, gettip());
        energie -= EnergieNecesaraInmultirii;
        numar_fii_alocati -= 1;
    }

    if (numar_fii_alocati > 0 && Individ[i + 1][j].esteviu() == 0 && energie >= EnergieNecesaraInmultirii && i + 1 <= m) {
        Individ[i + 1][j] = individ(i + 1, j, gettip());
        energie -= EnergieNecesaraInmultirii;
        numar_fii_alocati -= 1;
    }

    if (numar_fii_alocati > 0 && Individ[i][j + 1].esteviu() == 0 && energie >= EnergieNecesaraInmultirii && j + 1 <= n) {
        Individ[i][j + 1] = individ(i, j + 1, gettip());
        energie -= EnergieNecesaraInmultirii;
        numar_fii_alocati -= 1;
    }

}

void individ :: ataca(individ **Individ) {

    /// Aceasta metoda verifica toate pozitiile invecinate cu individul de pe pozitia (i, j) si determina daca exista un individ pe acele pozitii (i.e. au viu = 1),
    /// iar in cazul in care sunt indeplinite conditiile, acesta ataca in mod corespunzator.

    if (esteviu() && Individ[i + 1][j].esteviu() && Individ[i + 1][j].gettip() != gettip() && energie >= Individ[i + 1][j].energie) {
        energie -= Individ[i + 1][j].energie;
        Individ[i + 1][j].moare();
    }

    if (esteviu() && Individ[i][j + 1].esteviu() && Individ[i][j + 1].gettip() != gettip() && energie >= Individ[i][j + 1].energie) {
        energie -= Individ[i][j + 1].energie;
        Individ[i][j + 1].moare();
    }

    if (esteviu() && Individ[i - 1][j].esteviu() && Individ[i - 1][j].gettip() != gettip() && energie >= Individ[i - 1][j].energie) {
        energie -= Individ[i - 1][j].energie;
        Individ[i - 1][j].moare();
    }


    if (esteviu() && Individ[i][j - 1].esteviu() && Individ[i][j - 1].gettip() != gettip() && energie >= Individ[i][j - 1].energie) {
        energie -= Individ[i][j - 1].energie;
        Individ[i][j - 1].moare();
    }


}

void individ :: imbatraneste() {

    /// Aceasta metoda face individul sa imbatraneasca conform cerintei.

    varsta += 1;

    energie -= EnergieImbatranire;

    if (varsta >= VarstaMaxima || energie <= 0)
        moare();

}

void individ :: actualizare(individ **Individ, int m, int n) {

    /// Aceasta metoda aplica succesiv toate celelalte patru metode definite anterior, in ordinea aceasta.

    hraneste(Individ, m, n);
    inmulteste(Individ, m, n);
    ataca(Individ);
    imbatraneste();

}

char individ :: gettip() {
    return tip;
}

int individ :: esteviu() {
    if (viu == 1)
        return 1;
    else
        return 0;
}

void individ :: moare() {
    viu = 0;
}

void individ :: NObiecte(int n) {

    /// Aceasta metoda realizeaza citirea, memorarea si afisarea a n indivizi.

    for (int i = 0; i < n; i += 1) {
        std :: cout<<"Scrie datele pentru individul "<<i + 1<<":\n\n";
        std :: cin>>this[i];
        std :: cout<<"\n";
    }

    for (int i = 0; i < n; i += 1) {
        std :: cout<<"Informatiile despre individul "<<i + 1<<" sunt:\n";
        std :: cout<<this[i];
        std :: cout<<"\n\n";
    }

}

std :: istream & operator >> (std :: istream &in, individ &i) {

/// Supraincarcarea operatorului >> pentru citirea (datelor) unui individ.

    std :: cout<<"Pozitia i: ";
    in>>i.i;
    std :: cout<<"Pozitia j: ";
    in>>i.j;
    std :: cout<<"Tipul: ";
    in>>i.tip;
    std :: cout<<"Energia: ";
    in>>i.energie;
    std :: cout<<"Viu sau mort (1 sau 0): ";
    in>>i.viu;

    return in;
}

std :: ostream & operator << (std :: ostream &out, const individ &i) {

/// Supraincarcarea operatorului << pentru a afisa (datele despre) un individ.

    out<<"Individul se afla pe pozitia ("<<i.i<<", "<<i.j<<"), are energia egala cu "<<i.energie<<", este de tip "<<i.tip<<" si este ";

    if (i.viu == 1)
        std :: cout<<"viu.";
    else
        std :: cout<<"mort.";

    return out;
}


/// Metode pentru clasa 'tabla':

void tabla :: initializare() {

    /// Aceasta metoda genereaza cate un element aleatoriu si initializeaza indivizi pe anumite pozitii (unde numarul generat este divizibil cu 13, 17, 23 sau 31, pentru a crea mai multe 0-uri).
    /// Pentru a avea indivizi de ambele tipuri, cei pentru care elementul este si numar par vor avea '+', iar ceilalti '0'.

        int element;
        srand(time(NULL));
        for (int i = 1; i <= m; i += 1)
        for (int j = 1; j <= n; j += 1) {
            element = rand();
            if (element % 13 == 0 || element % 17 == 0 || element % 23 == 0 || element % 31 == 0)
                if (element % 2 == 0)
                    Individ[i][j] = individ(i, j, '+');
                else
                    Individ[i][j] = individ(i, j, '0');
        }
    }

void tabla :: afisare() {

    /// Dupa cum am mentionat anterior, afisarea tablei consta in afisarea valorii lui 'viu' pentru fiecare individ (care poate fi doar 1 / 0).

        for (int i = 1; i <= m; i += 1) {
            for (int j = 1; j <= n; j += 1)
                std :: cout<<Individ[i][j].esteviu()<<" ";
            std :: cout<<"\n";
        }
}

void tabla :: actualizare() {

    /// Pentru a actualiza intreaga tabela, o vom parcurge iar pentru fiecare individ care este viu, il vom actualiza.

    for (int i = 1; i <= m; i += 1)
    for (int j = 1; j <= n; j += 1) {
            if (Individ[i][j].esteviu())
                Individ[i][j].actualizare(Individ, m, n);
    }
}

int tabla :: verifica_existenta_indivizi() {

    /// Aceasta metoda verifica daca mai exista indivizi.

    for (int i = 1; i <= m; i += 1)
        for (int j = 1; j <= n; j += 1)
            if (Individ[i][j].esteviu())
                return 1;
    return 0;

}

int main() {

    /// Programul principal, realizat conform cerintei.

    tabla x(dimX, dimY);
    x.initializare();

    while (!kbhit()) {
        x.afisare();
        x.actualizare();
        if (x.verifica_existenta_indivizi() == 0) {
            std :: cout<<"\n";
            x.afisare();
            std :: cout<<"Nu mai exista indivizi.";
            break;
        }
        std :: cout<<"\n";
    }

    return 0;


/// Exemplu de citire, memorare si afisare a n obiecte:

    ///int n;

    ///std :: cin>>n;

    ///individ I[n];

    ///I->NObiecte(n);

}
