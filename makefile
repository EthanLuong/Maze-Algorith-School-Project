build:
	rm -f program.exe
	gcc main.cpp
	
run:
	./program.exe mazeData1.txt -d

valgrind:
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all -v ./program.exe mazeData1.txt
