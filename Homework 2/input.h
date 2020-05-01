#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

class input {
public:
    void init();
    void close();
    void write(char *words);
    char getc();
};

#endif // INPUT_H_INCLUDED
