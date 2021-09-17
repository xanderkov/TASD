import ctypes
from tkinter import *
from ctypes import *
OK = 0
adder = CDLL('./adder.so')
adder.check_number.restype = ctypes.c_int
adder.check_number.argtypes = [ctypes.c_char_p]
adder.start_operation.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]


def division():
    res = " "*100
    number_1 = first_number.get().encode('utf-8')
    order_1 = first_order.get().encode('utf-8')
    number_2 = second_number.get().encode('utf-8')
    order_2 = second_order.get().encode('utf-8')
    adder.start_operation(number_1, order_1, number_2, order_2)
    f = open("output.txt", "r") 
    res = f.readline()
    result.config(text = res)
    f.close()


def clear_all():
    check_res['text'] = " "
    check_res_order['text'] = " "
    check_res_2['text'] = " "
    check_res_order_2['text'] = " "
    first_number.delete(0, 'end')
    first_order.delete(0, 'end')
    second_number.delete(0, 'end')
    second_order.delete(0, 'end')



def check_message_number():
    number = first_number.get().encode('utf-8')
    if (adder.check_number(number) != OK):
        check_res['text'] = "Неверный ввод"
    else:
        check_res['text'] = "Верный"


def check_message_order():
    number = first_order.get().encode('utf-8')
    if (adder.check_order(number) != OK):
        check_res_order['text'] = "Неверный ввод"
    else:
        check_res_order['text'] = "Верный"


def check_message_number_2():
    number = second_number.get().encode('utf-8')
    if (adder.check_number(number) != OK):
        check_res_2['text'] = "Неверный ввод"
    else:
        check_res_2['text'] = "Верный"


def check_message_order_2():
    number = second_order.get().encode('utf-8')
    if (adder.check_order(number) != OK):
        check_res_order_2['text'] = "Неверный ввод"
    else:
        check_res_order_2['text'] = "Верный"


master = Tk()
myText=StringVar()

Label(master, text="Ввод двух действительных чисел вида: +-m.n E +-K").grid(sticky=N)
Label(master, text="Поля ввода чисел имеют 32 знака (для знака, . и цифр), порядок 6 (знака и цифр)").grid(row=1, sticky=N)
Label(master, text="Первое число. Ввод части: знак и m.n, m + n <= 30 зн.").grid(row=2, sticky=W)
Label(master, text="Первое число. Ввод части знак и K, K <= 5 зн.").grid(row=3, sticky=W)


check_res = Label(master, text="                                       ")
check_res.grid(row=2, column=3)
check_res_order = Label(master, text="")

check_res_order.grid(row=3, column=3)
first_number = Entry(master, width=32)
first_order = Entry(master, width=7)

first_number.grid(row=2, column=1)
first_order.grid(row=3, column=1)


сheck_first_number = Button(master, text="Проверить", command=check_message_number)
сheck_first_number.grid(row=2, column=2, padx=5)

сheck_first_order = Button(master, text="Проверить", command=check_message_order)
сheck_first_order.grid(row=3, column=2, padx=5)


Label(master, text="Второе число. Ввод части: знак и m.n, m + n <= 30 зн.").grid(row=5, column=0, sticky=W)
Label(master, text="Второе число. Ввод части знак и K, K <= 5 зн.").grid(row=6, column=0, sticky=W)


check_res_2 = Label(master, text="                                       ")
check_res_2.grid(row=5, column=3)
check_res_order_2 = Label(master, text="")

check_res_order_2.grid(row=6, column=3)
second_number = Entry(master, width=32)
second_order = Entry(master, width=7)

second_number.grid(row=5, column=1)
second_order.grid(row=6, column=1)


сheck_second_number = Button(master, text="Проверить", command=check_message_number_2)
сheck_second_number.grid(row=5, column=2, padx=5)

сheck_second_order = Button(master, text="Проверить", command=check_message_order_2)
сheck_second_order.grid(row=6, column=2, padx=5)


Label(master, text="÷").grid(row=4, column=0, columnspan=2)
get_result = Button(master, text="========================", command=division)
get_result.grid(row=7, column=0, columnspan=2)
Button(master, text="Очистить", command=clear_all).grid(row=7, column=3, columnspan=2)
result=Label(master, text="Result")
result.grid(row=10, column=0,columnspan=2, rowspan=2,sticky=W+E+N+S, padx=15, pady=15)

mainloop()
