spc : lex.yy.c main.cpp Callbacks.hpp
	g++ lex.yy.c main.cpp -lfl -std=c++11 -o spc
	
lex.yy.c: spider.lex
	flex spider.lex