#include<bits/stdc++.h>
using namespace std;
#pragma once
#include "dfa.hpp"
struct Token{
    string token;
    string lexeme;
    int line;
};
class Lexer{
    string::iterator sp;
    string::iterator fp;
    string text;
    DFA dfa;
    // void handleExceptions(exceptionClass)
    int handleString();
    int handleComment();
    
    public:
    Lexer(string code);
    vector<Token>getTokens();

    Lexer()=default;

    
};


