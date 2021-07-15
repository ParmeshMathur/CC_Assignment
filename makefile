output:
	flex -l scanner.l
	bison -d parser.y 
	g++ -o interactive driver.cpp parser.tab.c lex.yy.c -lfl
	
clean:
	rm -rf parser.output parser.tab.* lex.yy.c interactive
