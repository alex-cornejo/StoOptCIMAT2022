import matplotlib.pyplot as plt
import numpy as np

# print graph
plt.plot([2, 4, 8, 16, 32], [0.17, 0.51, 2.36, 8.99, 23.39], 'ro-', color='black')
plt.plot([2, 4, 8, 16, 32], [0.01, 0.02, 0.17, 1.19, 5.93], 'ro-', color='green')

plt.grid(True)
plt.xlabel('ρ')
plt.xticks([])
plt.ylabel('seconds')
plt.legend(('double trx a', 'double trx b'),
           loc='upper center', shadow=False)
plt.show()
