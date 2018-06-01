inp = open('rmq2.in', 'r').readlines()
out1 = open('rmq2.out', 'r').readlines()
out2 = open('answers_rmq2.out', 'r').readlines()

inp_it = 2
it = 1
for line1, line2 in zip(out1, out2):
    if set(line1.strip().split(' ')) != set(line2.strip().split(' ')):
        print("zaloopa happened at {0} line".format(it))
        print("request: {0} at line {1}".format(inp[inp_it].strip(), inp_it + 1))
        print("actual: {0}".format(line1).strip())
        print("expected: {0}".format(line2).strip())
        print('------------------------------------')
    it += 1
    inp_it += 1
