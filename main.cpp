#include "tokens.hpp"
#include "output.hpp"
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <assert.h>
#define MIN_STR_LEN 2

const char *  handleString(char *yytext){
    // 1. Remove ""
    // 2. transform hex pattern to matching ascii character (e.g the substring "\x23" should be printed as #)

    std::string s = yytext;
    std::string res;
    std::cout << s << std::endl;
    std::cout << "string len" << s.length() << std::endl;
    assert(s.length() >= MIN_STR_LEN);
    if(s.length() == MIN_STR_LEN) return "";
    for (size_t i = 1; i < s.length() - 1; ++i) { //This loop ignores the first and last characters, ' " '
        //start of an escape seq.
        if (s[i] == '\\') {
            //hex seq.
            if(i + 1 <= s.length() && s[i + 1] == 'x')
            {
                int hexStart = i + 2;
                int hexLen = 2;
                std::string hexStr = s.substr(hexStart, hexLen);
                char asciiChar = static_cast<char>(std::stoi(hexStr, nullptr, 16));
                i += 3; //only +3 because the loop will add another 1
                // handle the character
                res += asciiChar;
            }
            else if(i + 1 <= s.length() && s[i + 1] == '0')
            {
                res += '\0';
            }
            else if(i + 1 <= s.length() && s[i + 1] == 't')
            {
                res += '\t';
            }
            else if(i + 1 <= s.length() && s[i + 1] == 'r')
            {
                res += '\r';
            }
            else if(i + 1 <= s.length() && s[i + 1] == 'n')
            {
                res += '\n';
            }
            else if(i + 1 <= s.length() && s[i + 1] == '\"')
            {
                res += '\"';
            }
            else
            {
                res += '\\';
            }
        }
        else
        {
            res += s[i];
        }
    }
    return res.c_str();
}

int main() {
    enum tokentype token;
    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        // your code here
        if(token == STRING) {
            const char * text = handleString(yytext);
            output::printToken(yylineno, token, text);
        }
        else output::printToken(yylineno, token, yytext);
    }
    return 0;
}