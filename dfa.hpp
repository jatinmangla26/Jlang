#pragma once
#include "types.hpp"

class DFA{
    public:
    int curr_state;
    int prev_state;

    DFA();
    int transition(char);

    private:
    charClass identifyClass(char);
};