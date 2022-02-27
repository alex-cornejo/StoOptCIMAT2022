import random as rng

rng.seed(0)

n = 1000
alpha = 64

p_connect = 1 / n * alpha
d_range = (0, 4)
p_range = (1000, 10000)

instance_name = "DSP/DSP-{}-{}.ctr".format(n, alpha)
file = open(instance_name, 'w')
edges = []
for i in range(0, n):
    for j in range(0, n):
        if i != j:
            p = rng.uniform(0, 1)

            if p <= p_connect and (j, i) not in edges:
                edges.append((i, j))
                line = "{} {} R > {} {}\n".format(i, j, rng.randint(d_range[0], d_range[1]),
                                                rng.randint(p_range[0], p_range[1]))
                print(line)
                file.write(line)

file.close()