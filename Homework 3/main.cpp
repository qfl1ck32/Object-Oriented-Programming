#include <iostream>
#include <ctime>
#include "Bank.h"

int main() {
    GestionareConturi *BT = new GestionareConturi ("RO", "Banca Transilvania", "BTRL");
    BT -> meniu_principal();
}
