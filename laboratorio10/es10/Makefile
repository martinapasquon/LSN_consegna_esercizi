CXX= mpicxx


main.exe: main.o random.o Configurazione.o
	$(CXX) Configurazione.o random.o main.o -o main.exe
main.o : main.cpp 
	$(CXX) -c main.cpp -o main.o
random.o : random.cpp random.h
	$(CXX) -c random.cpp -o random.o 
Configurazione.o : Configurazione.cpp Configurazione.h 
	$(CXX) -c Configurazione.cpp -o Configurazione.o 
clean :
	rm *.o main.exe
