#include "tokens.hpp"
#include "output.hpp"
#include <iostream>

int main() {
    enum tokentype token;
    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        // your code here
        if(token == COMMENT) output::printToken(yylineno, token, yytext);
        else output::printToken(yylineno, token, yytext);
    }
    return 0;
}