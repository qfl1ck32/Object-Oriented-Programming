#include "input.h"
#include "output.h"
#include "joctanc.h"
#include <windows.h>


input intrare;
output iesire(tanc :: motor);

int main() {

    tanc :: motor.init(MAXNL, MAXNC);

    for (int i = 1; i <= MAXNL; ++i)
        for (int j = 1; j < MAXNC; ++j)
            if (i % 2 && !(j % 2))
                new zid(i, j);

    intrare.init();


    char a, b, c, d, e, f;
    int g, h;

    std :: cout << "You have to enter some details about the two tanks.\n\n";
    for (int i = 0; i < 2; ++i) {
        std :: cout << "Player " << i + 1 << "'s tank: \n";
        std :: cout << "Name: "; std :: cin >> a;
        std :: cout << "Left: "; std :: cin >> b;
        std :: cout << "Right: "; std :: cin >> c;
        std :: cout << "Up: "; std :: cin >> d;
        std :: cout << "Down: "; std :: cin >> e;
        std :: cout << "Fire: "; std :: cin >> f;
        std :: cout << "X-Position: "; std :: cin >> g;
        std :: cout << "Y-Position: "; std :: cin >> h;
        new tanc(a, b, c, d, e, f, g, h);
        std :: cout << "\n";
    }

    iesire.init();
    iesire.afisare();
    do {
        tanc :: cc = intrare.getc();
        tanc :: motor.next();
        iesire.afisare();
	Sleep(50);
    } while (tanc :: cc != 27 && tanc :: numar_tancuri > 1);

    iesire.close();
    intrare.close();
    return 0;
}
