inp = open('exam.in', 'r')
out = open('exam.out', 'w')

data = inp.readlines()
inp.close()
k, n = int(data[0].split(' ')[0]), int(data[0].split(' ')[1])
expected_value = 0.
for line in data[1:]:
    line = line.split(' ')
    p, m = int(line[0]), int(line[1])
    expected_value += p * (m / 100.)
out.write(str(round(expected_value / n, 5)))
