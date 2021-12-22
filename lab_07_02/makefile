CC := gcc
CFLAGS := -std=gnu99 -Wall -Werror -I inc/ -pedantic -g3
SRC_PATH := src/
INC := inc/
OUT := out/
UNIT_PATH := unit_tests/


app.exe : $(OUT)main.o $(OUT)io.o $(OUT)graph_oper.o
	$(CC) -o app.exe $(OUT)main.o $(OUT)io.o $(OUT)graph_oper.o


$(OUT)%.o : $(SRC_PATH)%.c $(INC)*.h
	$(CC) $(CFLAGS) -c $< -o $@



.PHONY : clean
clean :
	rm $(OUT)*.o *.exe
