CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -g3
OBJ := in_out.o number_division.o

main.exe : $(OBJ) main.o
	$(CC) -o main.exe $(OBJ) main.o

in_out.o : in_out.c in_out.h long_number.h
	$(CC) $(CFLAGS) -c in_out.c

number_division.o : number_division.c number_division.h long_number.h
	$(CC) $(CFLAGS) -c number_division.c

main.o : main.c in_out.h number_division.h long_number.h
	$(CC) $(CFLAGS) -c main.c

clean :
	rm *.o *.exe
