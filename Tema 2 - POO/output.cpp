#include <windows.h>

#include "output.h"

static int pictvect[MAXNU][2], npict;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void goToCoords(short y, short x) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(console, coord);
}

void output :: init() {
    npict = 0;

    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(console, &cursor);
    cursor.bVisible = 0;
    SetConsoleCursorInfo(console, &cursor);

    /// SetConsoleDisplayMode(console, CONSOLE_FULLSCREEN_MODE, 0);

    system("CLS");
    system("color 6");

    for (int i = 1; i <= MAXNC + 2; ++i)
        std :: cout << (unsigned char) (177);

    std :: cout << "\n";

    for (int i = 1; i < MAXNL + 1; ++i) {
        std :: cout << (unsigned char) (177);
        for (int j = 1; j <= MAXNC; ++j)
            std :: cout << " ";
        std :: cout << (unsigned char) (177) << "\n";
    }

    for (int i = 1; i <= MAXNC + 2; ++i)
        std :: cout << (unsigned char) (177);


    for (int i = 0; i < motor.getnu(); ++i) {
        if (*((unsigned char *) motor.getunitpoz(i) -> gettip()) == (unsigned char) (177)) {
            goToCoords(motor.getunitpoz(i) -> getx(), motor.getunitpoz(i) -> gety());
            std :: cout << (unsigned char) (177);
        }
    }
}

void output :: afisare() {
        for (int i = 0; i < npict; ++i)
            if (motor.getunitxy(pictvect[i][0], pictvect[i][1]) == NULL)
            {
                goToCoords(pictvect[i][0], pictvect[i][1]);
                std :: cout << " ";
            }

    npict = 0;

    for (int i = 0; i < motor.getnu(); ++i) {
        unsigned char *w = (unsigned char *) motor.getunitpoz(i) -> gettip();
        if (*w != (unsigned char) (177) ) {
            int cX = motor.getunitpoz(i) -> getx(), cY = motor.getunitpoz(i) -> gety();
            goToCoords(cX, cY);
            std :: cout << *w;
            pictvect[npict][0] = cX;
            pictvect[npict][1] = cY;
            ++npict;
        }
    }
}

void output :: close() {
    system("color 7");
    system("CLS");
}
