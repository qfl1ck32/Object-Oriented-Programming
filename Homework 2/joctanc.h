#ifndef JOCTANC_H_INCLUDED
#define JOCTANC_H_INCLUDED

#define KILL -32
#include "engine.h"

class zid : public unit {
public:
    zid(int a, int b) : unit(a, b) {}
    void *gettip() {
        return &nume;
    }

protected:
    void action() {};
    void behaviour(int) {};

private:
    static unsigned char nume;
};

class bomba : public unit {
public:
    bomba(int a, int b, int c, int d) : unit(a, b) {
        dirx = c;
        diry = d;
    }
    void *gettip() {
        return &nume;
    }

protected:
    void action();
    void behaviour(int);

private:
    static unsigned char nume;
    int dirx, diry, xn, yn;
};

class tanc : public unit {
public:
    static char cc;
    static int numar_tancuri;
    tanc(char a, char b, char c, char d, char e, char f, int g, int h) : unit(g, h) {
        numar_tancuri++;
        nume = a;
        stg = b;
        dr = c;
        sus = d;
        jos = e;
        foc = f;
    }
    void *gettip() {
        return &nume;
    }
protected:
    void action();
    void behaviour(int);

private:
    unsigned char nume;
    char stg, dr, sus, jos, foc, pc;
    int bx, by;
};

#endif // JOCTANC_H_INCLUDED
