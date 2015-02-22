%option yylineno
%{
#include "Callbacks.hpp"
#define YY_DECL extern "C" int yylex()
%}
%%
function {scanKeyWord(yytext, yylineno);}

@ {scanKeyWord(yytext, yylineno);}
# {scanKeyWord(yytext, yylineno);}
= {scanKeyWord(yytext, yylineno);}

\"(\\.|[^"])*\" {scanString(yytext, yylineno);}
\<(\\.|[^>])*\> {scanSpecial(yytext, yylineno);}

[a-zA-Z+\-*/&|\\][a-zA-Z0-9+\-*/&|\\]* {scanIdentifier(yytext, yylineno);}
-?[0-9]+ {scanInt(yytext, yylineno);}
"(" {scanPunctuation(yytext, yylineno);}
")" {scanPunctuation(yytext, yylineno);}

"{" {scanPunctuation(yytext, yylineno);}
"}" {scanPunctuation(yytext, yylineno);}

[ \n\r\t]
. {reportUnexpected(yytext, yylineno);}
%%
// int main()
// {
//     yylex();
// }