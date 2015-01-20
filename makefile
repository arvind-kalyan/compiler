
stage1exe: Lexer.c parser.c abstract_tree.c SymbolTable.c type_checker.c driver.c
	gcc -c Lexer.c
	gcc -c parser.c
	gcc -c abstract_tree.c
	gcc -c SymbolTable.c
	gcc -c type_checker.c
	gcc -c semantic_analyzer.c
	gcc -c  code_generator.c
	gcc Lexer.o parser.o abstract_tree.o SymbolTable.o type_checker.o semantic_analyzer.o code_generator.c driver.c -o stage1exe

clean:
	rm -vf *.o *.exe stage1exe *~ 

