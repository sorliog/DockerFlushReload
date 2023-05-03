CC = g++
FLAGS = -Wall -O0 

all: victim attacker attacker2

shared:
	$(CC) $(FLAGS) -c -fPIC   shared.cpp -o shared.o
	$(CC) $(FLAGS) -shared shared.h shared.o -o libshared.so

victim: shared
	$(CC) $(FLAGS) -L. -o victim victim.cpp -lshared


attacker: shared
	$(CC) $(FLAGS) -L. -o attacker attacker.cpp -lshared
	
attacker2: shared
	$(CC) $(FLAGS) -L. -o attacker2 attacker2.cpp -lshared

clean:
	rm -f libshared.so
	rm -f shared.o
	rm -f attacker
	rm -f attacker2
	rm -f victim
