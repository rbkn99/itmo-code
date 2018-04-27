from collections import OrderedDict
from random import randint



def get_next(od, key):
    i = list(od.keys()).index(key)
    if i == len(od.keys()):
        raise IndexError
    return list(od.items())[i + 1]


def get_prev(od, key):
    i = list(od.keys()).index(key)
    if i == 0:
        raise IndexError
    return list(od.items())[i - 1]


m = OrderedDict()

m['daa'] = 'cdd'
m['cd'] = 'caa'
del m['cd']
m['a'] = 'd'
m['dba'] = 'a'
print(get_next(m, 'a'))
