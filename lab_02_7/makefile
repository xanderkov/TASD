CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -g3
SRC_PATH := src/
UNIT_PATH := unit_tests/
SRC := $(SRC_PATH)io_file.c $(SRC_PATH)sort_array.c $(SRC_PATH)main.c $(UNIT_PATH)unit_test.c
UNIT :=  $(UNIT_PATH)unit_test.c
MAIN := $(SRC_PATH)main.c
OBJ :=  io.o sort.o line_operations.o

app.exe : $(OBJ) main.o
	$(CC) -o app.exe  $(OBJ) main.o

%.o : %.c *.h
	$(CC) $(CFLAGS) -c $<


.PHONY : clean
clean :
	rm *.o *.exe