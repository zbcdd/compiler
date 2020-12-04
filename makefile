compiler: lexer.l parser.y ./ast/AST.cpp ./symtab/symtab.cpp ./intercode/intercode.cpp
	g++ -c ./symtab/symtab.cpp
	g++ -c ./ast/AST.cpp	
	g++ -c ./intercode/intercode.cpp	
	bison -d parser.y
	flex lexer.l
	g++ -o compiler symtab.o AST.o intercode.o parser.tab.c lex.yy.c

clean: 
	rm *.c *.h *.o compiler
