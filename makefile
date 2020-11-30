compiler: lexer.l parser.y ./ast/AST.cpp ./symtab/symtab.cpp
	g++ -c ./symtab/symtab.cpp
	g++ -c ./ast/AST.cpp	
	bison -d parser.y
	flex lexer.l
	g++ -o compiler symtab.o AST.o parser.tab.c lex.yy.c

clean: 
	rm *.c *.h *.o compiler
