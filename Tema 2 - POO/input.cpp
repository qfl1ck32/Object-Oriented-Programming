#include <iostream>
#include <windows.h>
#include <conio.h>
#include "input.h"
#include "joctanc.h"

void input :: init() {
    char greeting[] = "Hello!\n\nWelcome to Tank :: TextMode!\n\nWhen you're ready, press any key to begin.";
    write(greeting);
    while (!kbhit()) {}
    system("CLS");
    getch();
}

void input :: close() {
    if (tanc :: numar_tancuri == 1) {
        for (int i = 0; i < tanc :: motor.getnu(); ++i) {
            unsigned char *c = (unsigned char *) tanc :: motor.getunitpoz(i) -> gettip();
            if (*c != (unsigned char)(177) && *c != '.') {
                std :: cout << "Tank " << *c << " won! :)\n\n";
                Sleep(1000);
            }
        }
    }
    char greeting[] = "Thanks for playing! Have a nice one!";
    write(greeting);
}

char input :: getc() {
    if(kbhit()) {
        char a = getch();
        if (a == -32)
            return getch();
        else
            return a;
    }
    else
        return 0;
}

void input :: write(char *words) {
    while (*words) {
        std :: cout << *words++;
        Sleep(25);
    }
}
