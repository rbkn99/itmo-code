from random import randint


inp1 = open('windows.in', 'w')
inp2 = open('windows_answers.out', 'w')

m = 10
n = 10

rects = []
inp1.write(str(n) + '\n')
for i in range(n):
    x1, y1 = randint(0, m), randint(0, m)
    x2, y2 = randint(0, m), randint(0, m)
    if x1 > x2:
        x1, x2 = x2, x1
    if y1 > y2:
        y1, y2 = y2, y1
    rects.append((x1, y1, x2, y2))
    inp1.write('{0} {1} {2} {3}\n'.format(x1, y1, x2, y2))

answer = [0, 0, 0]

for x in range(m):
    print(x)
    for y in range(m):
        c = 0
        for rect in rects:
            if rect[0] <= x <= rect[2] and rect[1] <= y <= rect[3]:
                c += 1
        if c > answer[0]:
            answer[0] = c
            answer[1] = x
            answer[2] = y

inp2.write('{0}\n{1} {2}'.format(answer[0], answer[1], answer[2]))

"""
n = 2000
m = 2000
a = -10000
b = 10000

data = [randint(a, b) for _ in range(n)]
inp1.write(str(n) + '\n')
inp1.write(' '.join([str(x) for x in data]) + '\n')
for _ in range(m):
    q = randint(0, 2)
    l = randint(0, n - 1)
    r = randint(0, n - 1)
    if l > r:
        l, r = r, l
    if q == 0:
        inp1.write('min {0} {1}\n'.format(l+1, r+1))
        inp2.write(str(min(data[l:r+1])) + '\n')
    elif q == 1:
        x = randint(a, b)
        inp1.write('set {0} {1} {2}\n'.format(l + 1, r + 1, x))
        for i in range(l, r + 1):
            data[i] = x
    else:
        x = randint(a, b)
        inp1.write('add {0} {1} {2}\n'.format(l + 1, r + 1, x))
        for i in range(l, r + 1):
            data[i] += x
"""