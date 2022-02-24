#include "dfa.hpp"
#include "config.hpp"

DFA::DFA()
{
    prev_state = curr_state = 0;
}
charClass DFA::identifyClass(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
    {
        return charClass::ALPHA;
    }
    else if (ch >= '1' && ch <= '9')
    {
        return charClass::NUMERIC;
    }
    else if (ch == '.')
    {
        return charClass::DOT;
    }
    else if (ch == ' ' || ch == '\t' || ch == '\n')
    {
        return charClass::WHITESPACE;
    }
    else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
    {
        return charClass::ARITH;
    }
    else if (ch == '<' || ch == '>' || ch == '!' || ch == ':')
    {
        return charClass::LOGIC;
    }
    else if (ch == '=')
    {
        return charClass::EQU;
    }
    else if (ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == ';' || ch == ',')
    {
        return charClass::DELIM;
    }
    else if (ch == '"')
    {
        return charClass::QUOTE;
    }
    else if (ch == '&')
    {
        return charClass::AND;
    }
    else if (ch == '|')
    {
        return charClass::OR;
    }
    else if (ch == '$')
    {
        return charClass::ENDOFFILE;
    }
    else
    {
        // invalid character;
        return charClass::INVALID;
    }
}
int DFA::transition(char ch)
{
    charClass col=identifyClass(ch);
    
    if(col==charClass::INVALID)
    return -1;
    else
    return transitionTable[curr_state][static_cast<int>(col)];
}
