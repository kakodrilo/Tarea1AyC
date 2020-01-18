
ejecutar: MIB
	./MIB < input.txt

MIB: MIB.o
	g++ MIB.o -o MIB

MIB.o: MIB.cpp
	g++ -c MIB.cpp -Wall

clear:
	rm -r MIB \
	MIB.o
