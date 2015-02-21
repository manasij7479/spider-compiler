%{
#include "Callbacks.hpp"
#define YY_DECL extern "C" int yylex()
%}
%%
auto {scanKeyWord(yytext);}
@ {scanKeyWord(yytext);}
# {scanKeyWord(yytext);}
= {scanKeyWord(yytext);}

\".*\" {scanString(yytext);}
\<.*\> {scanSpecial(yytext);}

[a-zA-Z+\-*/&|\\][a-zA-Z0-9+\-*/&|\\]* {scanIdentifier(yytext);}
-?[0-9]+ {scanInt(yytext);}
"(" {scanOpenParen();}
")" {scanCloseParen();}

"{" {scanOpenBrace();}
"}" {scanCloseBrace();}

[ \n\r\t]
. {reportUnexpected(yytext);}
%%
// int main()
// {
//     yylex();
// }