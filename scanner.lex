%{
    #include "output.hpp"
%}

%option yylineno
%option noyywrap

whitespace  ([\r\t\n ])
binary_op   ([+\-*/])
relop       (==|!=|<|>|<=|>=)
num         ([1-9][0-9]*|0)
num_b       (0b|{num}b)

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
\"([^\"\n\r\\]|\\[rnt\"\\])+\"      return STRING;
\/\/([^\r\n]*)                      return COMMENT;
{whitespace} ;
. output::errorUnknownChar(*yytext); exit(0);
%%
