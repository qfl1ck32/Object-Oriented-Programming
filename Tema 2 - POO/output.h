#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED

#include "engine.h"
#include "joctanc.h"

class output {
public:
    output(engine &pm): motor(pm) {}
    void init();
    void afisare();
    void close();
private:
    engine &motor;
};



#endif // OUTPUT_H_INCLUDED
