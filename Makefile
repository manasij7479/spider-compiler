spc : lex.yy.c main.cpp Callbacks.hpp
	g++ lex.yy.c main.cpp -lfl -std=c++11 -o spc -g
	
lex.yy.c: spider.lex
	flex spider.lex

clean:
	rm spc lex.yy.c