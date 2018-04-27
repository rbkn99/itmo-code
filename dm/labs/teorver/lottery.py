inp = open('lottery.in', 'r')
out = open('lottery.out', 'w')

data = inp.readlines()
inp.close()
n, m = int(data[0].split(' ')[0]), int(data[0].split(' ')[1])
p = 1.
prev = 0
expected_value = 0.
for line in data[1:]:
    line = line.split(' ')
    expected_value += p * (1 - 1. / int(line[0])) * prev
    p *= 1. / int(line[0])
    prev = int(line[1])
expected_value += p * prev
out.write(str(n - expected_value))

