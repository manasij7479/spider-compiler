spc : lex.yy.c a.cpp Callbacks.hpp
	g++ lex.yy.c a.cpp -lfl -std=c++11 -o spc
	
lex.yy.c: a.lex
	flex a.lex