import string
import random

def gen_str():
    number = random.randint(10, 15)
    line = ''.join(random.choice(string.ascii_uppercase) for i in range(number))
    return line + ' '

f = open("test_2.txt", "w")
# f.write('Фамилия Имя Номер адрес(ул. дом. кв) дата рождения должность организация \n')
for i in range(1000):
    line = ''
    line += gen_str()
    line += gen_str()
    line += gen_str()
    line += str(random.randint(80000000000, 89999999999)) + ' '
    if i % 2 == 0:
        line += '0 '
        number = random.randint(1, 31)
        line += str(number) + ' '
        number = random.randint(1, 12)
        line += str(number) + ' '
        number = random.randint(1900, 2021)
        line += str(number) + '\n'
    else:
        line += '1 '
        line += gen_str()
        line += gen_str() + '\n'
    f.write(line)
f.close()
