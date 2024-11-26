#include "tokens.hpp"
#include "output.hpp"
#include <iostream>
#include <string>

void handleString(char *yytext){
    // 1. Remove ""
    // 2. transform hex pattern to matching ascii character (e.g the substring "\x23" should be printed as #)

    std::string s = input

}

int main() {
    enum tokentype token;
    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        // your code here
        if(token == STRING) {
            handleString(yytext);
        }
        else output::printToken(yylineno, token, yytext);
    }
    return 0;
}