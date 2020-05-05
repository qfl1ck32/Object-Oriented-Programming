#include "Client.h"
#include <algorithm>

#define SET 1
#define GET 2
#define PRINT 3

template <class ClassName>
std :: string modify(std :: string lookup, ClassName &c, int action) {
    std :: string temp;
    int index;
    std :: transform(lookup.begin(), lookup.end(), lookup.begin(), :: toupper);
    for (auto it = c.data.begin(); it != c.data.end(); ++it) {
        temp = *it;
        std :: transform(temp.begin(), temp.end(), temp.begin(), :: toupper);
        if (lookup == temp) {
            index = std :: distance(c.data.begin(), it);
            if (action == SET) {
                std :: cout << c.detalii[index].first << ": ";
                getline(std :: cin, c.detalii[index].second);
            }
            else if (action == GET)
                return c.detalii[index].second;
                else
                    std :: cout << c.detalii[index].first << ": " << c.detalii[index].second << "\n";
        }
    }
    return "";
}

adresa ::  adresa() {
    for (auto it = data.begin(); it != data.end(); ++it)
        detalii.push_back(std :: make_pair(*it, "-"));
}

informatii_personale :: informatii_personale() {
    for (auto it = data.begin(); it != data.end(); ++it)
        detalii.push_back(std :: make_pair(*it, "-"));
}

std :: istream &operator >> (std :: istream &in, adresa &a) {
    for (auto it = a.data.begin(); it != a.data.end(); ++it)
        modify <adresa> (*it, a, SET);
    return in;
}

std :: ostream &operator << (std :: ostream &out, adresa &a) {
    for (auto it = a.data.begin(); it != a.data.end(); ++it)
        modify <adresa> (*it, a, PRINT);
    return out;
}

std :: istream &operator >> (std :: istream &in, informatii_personale &i) {
    for (auto it = i.data.begin(); it != i.data.end(); ++it)
        modify <informatii_personale> (*it, i, SET);
    return in;
}

std :: ostream &operator << (std :: ostream &out, informatii_personale &i) {
    for (auto it = i.data.begin(); it != i.data.end(); ++it)
       modify <informatii_personale> (*it, i, PRINT);
    return out;
}

std :: istream &operator >> (std :: istream &in, client *c) {
    in >> *(c -> detalii);
    in >> *(c -> locatie);
    return in;
}

std :: ostream &operator << (std :: ostream &out, const client *c) {
    out << *(c -> detalii);
    out << *(c -> locatie);
    return out;
}
