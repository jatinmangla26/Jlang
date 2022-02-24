#include <bits/stdc++.h>
using namespace std;
#include "lexer.hpp"
#include "config.hpp"
#include "types.hpp"
int line = 1;

Lexer::Lexer(string code)
{
    text = code;
    text.push_back('$');
    sp = text.begin();
    fp = text.begin();
    // dfa=DFA::DFA();
}
int Lexer::handleString()
{
    while (true)
    {
    fp++;
    if(*fp=='\"')
    {
        return 1;
        
    }
    if(*fp=='$' || *fp=='\n')
    {
        break;
        
    }
    }
    return 0;
}
int Lexer::handleComment()
{
    while (true)
    {
        fp++;
        // cout<<*fp<<" ";
        if (*fp == '\n')
            line++;
        if (*fp == '*' && *(fp + 1) == '/')
        {
            // cout<<"Handling Comments";
            fp++;
            break;
        }
        else if (*fp == '$')
        {
            return 0;
        }
    }
    return 1;
}
bool isKeyword(string lexeme)
{
    for (int i = 0; i < keywords.size(); i++)
        if (lexeme == keywords[i])
            return true;
    return false;
}
vector<Token> Lexer::getTokens()
{
    ofstream outdata;
    outdata.open("tokens.txt");
    vector<Token> tokens;

    while (true)
    {
        char ch = *fp;
        dfa.prev_state = dfa.curr_state;
        dfa.curr_state = dfa.transition(ch);

        if (dfa.curr_state == 0 && dfa.prev_state == 0)  //It's a WhiteSpace so move both pointers forward
        {
            if (ch == '\n')
                line++;
            fp++;
            sp++;
            continue;
        }
        if (ch == '/' && *(fp + 1) == '*')
        {
            if (handleComment() == 1)
            {}
            else
            {
                cout << "Unhaandled Comment";
                outdata<<"Unhandled Comment";
                outdata.close();
                exit(1);
            }
            fp++;
            sp = fp;
            dfa.curr_state = 0;
            continue;
        }

        if (dfa.curr_state == 0)
        {
            Token token;
            string lexeme = string(sp, fp);
            switch (dfa.prev_state)
            {

            case 1:
            {

                if (isKeyword(lexeme))
                    token.token = "keyword";
                else
                    token.token = "identifier";
                break;
            }
            case 2:
            {
                token.token = "number";
                break;
            }
            case 4:
            {
                token.token = "float";
                break;
            }
            case 5:
            {
                token.token = "delimeter";
                break;
            }
            case 6:
            case 7:
            case 8:
            case 11:
            case 12:
            case 13:
            {
                token.token = "operator";
                break;
            }
            case 99:
            {
                token.token = "string";
                break;
            }
            default:
            {
                token.token = "default";
                break;
            }
            }
            
            token.line = line;
            token.lexeme = lexeme;
            tokens.push_back(token);
            
            sp = fp;
            fp--;
        }
        if (ch == '\"')
        {
            fp++;
            if (handleString()==1)
            {
                dfa.curr_state = 99;
            }
            else
            {
                cout<<"Wrong String";
                outdata<<"Wrong String";
                outdata.close();
                exit(1);
            }
        }

        if (ch == '$')
            break;
        fp++;
    }
    return tokens;
}
