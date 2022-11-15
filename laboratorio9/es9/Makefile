CC = g++
CFLAGS = -Wall -O3 --std=c++11

main.exe : main.o configurazione.o random.o
	$(CC) random.o configurazione.o main.o -o main.exe
main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
configurazione.o : configurazione.cpp configurazione.h 
	$(CC) -c configurazione.cpp -o configurazione.o $(CFLAGS)
clean :
	rm *.o main.exe


