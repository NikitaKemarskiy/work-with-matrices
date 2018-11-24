all: compile

compile: main.cpp
	g++ -o ./bin/Debug/Matrices.exe main.cpp

clear: 
	rm ./bin/Debug/Matrices.exe
