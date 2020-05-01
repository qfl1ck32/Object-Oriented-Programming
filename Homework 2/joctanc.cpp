#include "joctanc.h"

unsigned char zid :: nume = 177;
unsigned char bomba :: nume = '.';

char tanc :: cc;
int tanc :: numar_tancuri;

void bomba :: action() {
    xn = getx() + dirx;
    yn = gety() + diry;
    if (!motor.validxy(xn, yn))
        die();
    else
        if (motor.getunitxy(xn, yn) == NULL)
            move(dirx, diry);
        else {
            sendmes(KILL, *motor.getunitxy(xn, yn));
            die();
        }
}

void bomba :: behaviour(int a) {
    if (a == KILL)
        die();
}

void tanc :: action() {
    int xc = getx(), yc = gety();
    if (cc == stg || cc == dr || cc == sus || cc == jos || cc == foc) {
            if (cc == stg || cc == dr || cc == sus || cc == jos) {
                if (cc == stg && motor.validxy(xc, yc - 1) && motor.getunitxy(xc, yc - 1) == NULL)
                        move(0, -1);
                else if (cc == sus && motor.validxy(xc - 1, yc) && motor.getunitxy(xc - 1, yc) == NULL)
                        move(-1, 0);
                    else if (cc == dr && motor.validxy(xc, yc + 1) && motor.getunitxy(xc, yc + 1) == NULL)
                            move(0, 1);
                        else if (cc == jos && motor.validxy(xc + 1, yc) && motor.getunitxy(xc + 1, yc) == NULL)
                                move(1, 0);
                pc = cc;
            }
            else
            {
                if (pc == stg) {
                    bx = xc;
                    by = yc - 1;
                }
                else if (pc == sus) {
                        bx = xc - 1;
                        by = yc;
                    }
                    else if (pc == dr) {
                                bx = xc;
                                by = yc + 1;
                            }
                        else if (pc == jos) {
                                    bx = xc + 1;
                                    by = yc;
                                }
                if (motor.validxy(bx, by)) {
                    if (motor.getunitxy(bx, by) == NULL) {
                        if (pc == stg)
                            new bomba(bx, by, 0, -1);
                        else
                            if (pc == sus)
                                new bomba(bx, by, -1, 0);
                            else
                                if (pc == dr)
                                    new bomba(bx, by, 0, 1);
                                else
                                    if (pc == jos)
                                        new bomba(bx, by, 1, 0);
                    }
                    else
                        sendmes(KILL, *motor.getunitxy(bx, by));
                }
            }
        }
}

void tanc :: behaviour(int a) {
    if (a == KILL) {
        numar_tancuri--;
        die();
    }
}
