inp = open('shooter.in', 'r')
out = open('shooter.out', 'w')

n, m, k = list(map(int, inp.readline().split(' ')))
p = list(map(float, inp.readline().split(' ')))
d = [(1. - p[i]) ** m for i in range(n)]
result = round(d[k - 1] / sum(d), 13)
out.write(str(result))
