import ctypes
from ctypes import *

adder = CDLL('./adder.so')
adder.check_number.restype = ctypes.c_int
adder.check_number.argtypes = [ctypes.c_char_p]
adder.start_operation.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]


def test_1():
    number = adder.start_operation("12", "0", "2", "0")
    if (number != " +0.2 E +1"):
        return 1
    return 0


def test_2():
    number = adder.start_operation("12", "0", "0", "0")
    if (number != "INPUT ERROR"):
        return 1
    return 0

def test_3():
    number = adder.start_operation("77833", "0", "6652", "0")
    if (number != " 0.11700691521346963319302465423 E +2"):
        return 1
    return 0

def test_4():
    number = adder.start_operation(".1", "0", "2", "0")
    if (number != "+0.5 E +2"):
        return 1
    return 0

def test_5():
    number = adder.start_operation("1200000000000000000000000000000", "0", "2", "0")
    if (number != "INPUT ERROR"):
        return 1
    return 0

def all_tests():
    err = 0
    err += test_1()
    err += test_2()
    err += test_3()
    err += test_4()
    err += test_5()
    if (err == 0):
        print("OK")
    else:
        print("NOT OK, err_num: %d", err)