#include "tokens.hpp"
#include "output.hpp"
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <assert.h>
#define MIN_STR_LEN 2

void  handleString(std::string& str, char *yytext){
    std::string s = yytext;
    // std::string res;
    // std::cout << s << std::endl;
    // std::cout << "string len" << s.length() << std::endl;
    assert(s.length() >= MIN_STR_LEN);
    if(s.length() == MIN_STR_LEN) return;
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
                str += asciiChar;
            }
            else if(i + 1 <= s.length() && s[i + 1] == '0')
            {
                str += '\0';
                i++;
            }
            else if(i + 1 <= s.length() && s[i + 1] == 't')
            {
                str += '\t';
                i++;
            }
            else if(i + 1 <= s.length() && s[i + 1] == 'r')
            {
                str += '\r';
                i++;
            }
            else if(i + 1 <= s.length() && s[i + 1] == 'n')
            {
                str += '\n';
                i++;
            }
            else if(i + 1 <= s.length() && s[i + 1] == '\"')
            {
                str += '\"';
                i++;
            }
            else
            {
                str += '\\';
                i++;
            }
        }
        else
        {
            str += s[i];
        }
    }
    // std::cout << std::endl << res << std::endl << "end" << std::endl;
    // return str.c_str();
}

int main() {
    enum tokentype token;
    std::string str;
    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        if(token == STRING) {
            handleString(str, yytext);
            // std::cout << str << std::endl;
            output::printToken(yylineno, token, str.c_str());
            str.clear();
        }
        else output::printToken(yylineno, token, yytext);
    }
    return 0;
}