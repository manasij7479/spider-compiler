CXX:=g++
CXXFLAGS:=-c -std=c++14 -g
SRCS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp, %.o, $(SRCS))         
TARGET:=spc
default: $(TARGET)

%.o : %.cpp lex.yy.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(TARGET) : $(OBJS) lex.yy.o 
	$(CXX) $(LDFLAGS) $^ -o $(TARGET) 
# spc : lex.yy.c main.cpp Callbacks.hpp AST.cpp
# 	g++ lex.yy.c main.cpp AST.cpp GlobalState.cpp Sema.cpp -lfl -std=c++1y -o spc -g
	
lex.yy.o : spider.lex
	flex spider.lex
	g++ -c lex.yy.c -lfl -o lex.yy.o -std=c++14

clean:
	rm spc lex.yy.c *.o
	
redo:
	make clean
	make -j9
