#include <iostream>
#include <ctime>
#include "Bank.h"

int main() {
    banca *BT = new banca("RO", "Banca Transilvania", "BTRL");
    BT -> meniu_principal();
}
