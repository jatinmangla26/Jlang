#include <bits/stdc++.h>
using namespace std;
#include "lexer.hpp"
int main()
{
    ifstream data("test.txt");
    string code;
    if (data)
    {
        ostringstream ss;
        ss << data.rdbuf();
        code = ss.str();
    }
    // cout << code;
    ofstream outdata;
    outdata.open("tokens.txt");
    if (!outdata)
    {
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    Lexer lexer(code);
    vector<Token> tokens = lexer.getTokens();
    for (auto token : tokens)
    {
        // cout << token.lexeme << " " << token.token << " " << token.line << endl;
        outdata << "<  " << token.lexeme << " ,  " << token.token << " ,  " << token.line << "  >" << endl;
    }
    outdata.close();
}