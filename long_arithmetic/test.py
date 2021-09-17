import ctypes
from ctypes import *

adder = CDLL('./adder.so')
adder.check_number.restype = ctypes.c_int
adder.check_number.argtypes = [ctypes.c_char_p]
adder.start_operation.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]


def test_1():
    number = adder.start_operation("12", "0", "2", "0")

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