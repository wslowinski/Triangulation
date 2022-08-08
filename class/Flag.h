#ifndef FLAG_H
#define FLAG_H

class Flag {
public:
    unsigned int f;

    Flag();
    ~Flag() = default;
    void infinite(unsigned int i);
    void last_finite();
    void kill();
    unsigned int is_infinite();
    unsigned int is_last_finite();
    unsigned int is_dead();
    unsigned int is_degenerate();
};

Flag::Flag() {
    f = 0u;
}

void Flag::infinite(unsigned int i) {
    f |= i;
}

void Flag::last_finite() {
    f |= 8;
}

void Flag::kill() {
    f |= 16;
}

unsigned int Flag::is_infinite() {
    return f & 7;
}

unsigned int Flag::is_last_finite() {
    return f & 8;
}

unsigned int Flag::is_dead() {
    return f & 16;
}

unsigned int Flag::is_degenerate() {
    return f & 32;
}
#endif