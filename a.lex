%{
#include "Callbacks.hpp"
#define YY_DECL extern "C" int yylex()
%}

%%
\".*\" {scanString(yytext);}
[a-zA-Z][a-zA-Z0-9]* {scanIdentifier(yytext);}
-?[0-9]+ {scanInt(yytext);}
"(" {scanOpenParen();}
")" {scanCloseParen();}
@ {scanKeyWord("@");}


[ \n\r\t]
. {reportUnexpected(yytext);}
%%
// int main()
// {
//     yylex();
// }