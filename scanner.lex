%{
    #include "output.hpp"
    #include <iostream>
%}

%option yylineno
%option noyywrap
%x S


whitespace  ([\r\t\n ])
binary_op   ([+\-*/])
relop       (==|!=|<|>|<=|>=)
num         ([1-9][0-9]*|0)
num_b       (0b|{num}b)
ascii_x20_to_x21    ([ !])
ascii_x23_to_x5B    ([#-\[])
ascii_x5D_to_x7E    ([\]-~])
printable_characters    ({ascii_x20_to_x21}|{ascii_x23_to_x5B}|{ascii_x5D_to_x7E})
legal_hex_pattern   (x[2-6][0-9a-fA-F]|x7[0-9a-eA-E])
legal_escape_pattern    ([\\ntr\"0])
legal_string        ({printable_characters}|\\{legal_hex_pattern}|\\{legal_escape_pattern})*




%%
void                                return VOID;
int                                 return INT;
byte                                return BYTE;
bool                                return BOOL;
and                                 return AND;
or                                  return OR;
not                                 return NOT;
true                                return TRUE;
false                               return FALSE;
return                              return RETURN;
if                                  return IF;
else                                return ELSE;
while                               return WHILE;
break                               return BREAK;
continue                            return CONTINUE;
";"                                 return SC;
","                                 return COMMA;
"("                                 return LPAREN;
")"                                 return RPAREN;
"{"                                 return LBRACE;
"}"                                 return RBRACE;
"="                                 return ASSIGN;
{relop}                             return RELOP;
{binary_op}                         return BINOP;
[a-zA-Z][a-zA-Z0-9]*                return ID;
{num}                               return NUM;
{num_b}                             return NUM_B;
\/\/([^\r\n]*)                      return COMMENT;
\"                                  BEGIN(S);
<S>{legal_string}\n                 output::errorUnclosedString();
<S>{legal_string}                   return STRING;
<S>\"                               BEGIN(INITIAL);
{whitespace} ;
. output::errorUnknownChar(*yytext); exit(0);
%%
