#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <iostream>

#define MAXNL 23
#define MAXNC 23
#define MAXNU (MAXNL + 1) / 2 * (MAXNC / 2) + 3 /// numar de numere impare in MAXNL * numar de numere pare in MAXNC + numar de unitati <> zid | + 3 pentru ca sunt doua tancuri si cel mult o bomba.
#define MAXNM 5


class unit;

class engine {
public:
    void init(int, int);
    int getnl();
    int getnc();
    int getnu();
    int validxy(int, int);
    int validpoz(int);
    unit* getunitxy(int, int);
    unit* getunitpoz(int);
    void next();
    friend class unit;
private:
    unit *unittab[MAXNL + 1][MAXNC + 1], *unitvect[MAXNU];
    int nc, nl, nu;
};

class unit {
public:
    static engine motor;
    int getx();
    int gety();
    virtual void *gettip() = 0;
    friend class engine;
protected:
    unit(int, int);
    virtual ~unit() {
        delete[] message;
    }
    void die();
    void move(int, int);
    void sendmes(int, unit&);
    virtual void action() = 0;
    virtual void behaviour(int) = 0;
private:
    int alive, x, y, poz, nm, *message = new int[MAXNM];
    void react();
};


#endif // ENGINE_H_INCLUDED
