X, Y = [], []
with open("hull.txt", "r") as f:
    for line in f:
        x, y = line.split()
        X.append(int(x))
        Y.append(int(y))

import matplotlib.pyplot as plt
plt.plot(X, Y, 'ro')
plt.show()
