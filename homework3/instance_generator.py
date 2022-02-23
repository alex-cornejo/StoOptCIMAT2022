import random as rng

rng.seed(0)

n = 100
p_connect = 1 / 100 * 2
d_range = (0, 5)
p_range = (1000, 10000)

for i in range(0, n):
    for j in range(0, n):
        if i != j:
            p = rng.uniform(0, 1)

            if p <= p_connect:
                line = "{} {} R > {} {}".format(i, j, rng.randint(d_range[0], d_range[1]),
                                                rng.randint(p_range[0], p_range[1]))
                print(line)
