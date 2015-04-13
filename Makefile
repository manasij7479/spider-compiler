spc : lex.yy.c main.cpp Callbacks.hpp AST.cpp
	g++ lex.yy.c main.cpp AST.cpp GlobalState.cpp Sema.cpp -lfl -std=c++1y -o spc -g
	
lex.yy.c: spider.lex
	flex spider.lex

clean:
	rm spc lex.yy.c
	
redo:
	make clean
	make -j9
