#include "engine.h"

engine unit :: motor;

void engine :: init(int a, int b) {
    nl = a;
    nc = b;
    nu = 0;
    for (register int i = 1; i <= MAXNL; ++i)
        for (register int j = 1; j <= MAXNC; ++j)
            unittab[i][j] = NULL;
}

int engine :: getnl() {
    return nl;
}

int engine :: getnc() {
    return nc;
}

int engine :: getnu() {
    return nu;
}

int engine :: validxy(int a, int b) {
    return (a > 0 && a <= nl && b > 0 && b <= nc ) ? 1 : 0;
}

int engine :: validpoz(int a) {
   return (a >= 0 && a < nu) ? 1 : 0;
}

unit* engine :: getunitxy(int a, int b) {
    return unittab[a][b];
}

unit* engine :: getunitpoz(int a) {
    return unitvect[a];
}

void engine :: next() {

    for (register int i = 0; i < nu; ++i)
        unitvect[i] -> action();

    for (register int i = 0; i < nu; ++i)
        unitvect[i] -> react();

    for (register int i = 0; i < nu; ++i)
        if (!(unitvect[i] -> alive)) {
                unittab[unitvect[i] -> getx()][unitvect[i] -> gety()] = NULL;
                delete unitvect[i];
                for (register int j = i + 1; j < nu; ++j)
                    unitvect[j - 1] = unitvect[j];
                nu--;
                i--;
            }
}

unit :: unit(int a, int b) {
        x = a;
        y = b;
        alive = 1;
        nm = 0;

        for (register int i = 0; i < MAXNM; ++i)
            message[i] = 0;

        if (motor.unittab[a][b] == NULL && motor.nu != MAXNU) {
            motor.unitvect[motor.nu++] = this;
            motor.unittab[a][b] = this;
        }
}

void unit :: react() {
    for (register int i = 0; i <= nm; ++i)
        if (message[i] && alive)
            behaviour(message[i]);
    nm = 0;
}

void unit :: die() {
    alive = 0;
}

void unit :: move(int dx, int dy) {
    motor.unittab[x][y] = NULL;
    motor.unittab[x += dx][y += dy] = this;
}

void unit :: sendmes(int pm, unit& pu) {
    if (pu.nm != MAXNM)
        pu.message[nm++] = pm;
}

int unit :: getx() {
    return x;
}

int unit :: gety() {
    return y;
}
