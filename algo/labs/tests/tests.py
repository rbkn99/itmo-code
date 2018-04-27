from collections import defaultdict
from random import randint


inp1 = open('multimap.in', 'w')
inp2 = open('answers_multimap.out', 'w')


m = defaultdict(list)

n = 10000
alphabet = ['a', 'b', 'c']
max_len = 5

for __ in range(n):
    req_type = randint(1, 4)
    key = ''
    len_s = randint(1, max_len)
    for _ in range(len_s):
        key += alphabet[randint(0, len(alphabet) - 1)]
    val = ''
    len_s1 = randint(1, max_len)
    for _ in range(len_s1):
        val += alphabet[randint(0, len(alphabet) - 1)]

    if req_type == 1:
        inp1.write('put ')
        inp1.write(key + ' ' + val + '\n')
        if key not in m.keys() or val not in m[key]:
            m[key].append(val)
    elif req_type == 2:
        inp1.write('delete ' + key + ' ' + val + '\n')
        if key in m.keys() and val in m[key]:
            m[key].remove(val)
    elif req_type == 3:
        inp1.write('deleteall ' + key + '\n')
        if key in m.keys():
            m[key] = []
    elif req_type == 4:
        inp1.write('get ' + key + '\n')
        if key in m.keys() and len(m[key]) > 0:
            inp2.write(str(len(m[key])) + ' ')
            for s in m[key]:
                inp2.write(s + ' ')
            inp2.write('\n')
        else:
            inp2.write("0\n")
