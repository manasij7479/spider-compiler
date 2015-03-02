%option yylineno
%{
#include "Callbacks.hpp"
#define YY_DECL extern "C" int yylex()
%}
%%
function {scanSymbol(yytext, yylineno);}
type {scanSymbol(yytext, yylineno);}
auto {scanSymbol(yytext, yylineno);}
if {scanSymbol(yytext, yylineno);}
else {scanSymbol(yytext, yylineno);}
while {scanSymbol(yytext, yylineno);}
return {scanSymbol(yytext, yylineno);}

@ {scanSymbol(yytext, yylineno);}
# {scanSymbol(yytext, yylineno);}
= {scanSymbol(yytext, yylineno);}
\. {scanSymbol(yytext, yylineno);}
\' {scanSymbol(yytext, yylineno);}
; {scanSymbol(yytext, yylineno);}
"(" {scanSymbol(yytext, yylineno);}
")" {scanSymbol(yytext, yylineno);}
"{" {scanSymbol(yytext, yylineno);}
"}" {scanSymbol(yytext, yylineno);}

\"(\\.|[^"])*\" {scanString(yytext, yylineno);}
\<(\\.|[^>])*\> {scanSpecial(yytext, yylineno);}

[a-zA-Z+\-*/&|\\][a-zA-Z0-9+\-*/&|\\]* {scanIdentifier(yytext, yylineno);}
-?[0-9]+ {scanInt(yytext, yylineno);}

[ \n\r\t]
. {reportUnexpected(yytext, yylineno);}
%%
// int main()
// {
//     yylex();
// }