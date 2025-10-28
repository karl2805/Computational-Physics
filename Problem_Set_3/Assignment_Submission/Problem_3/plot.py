import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

def f(x):
    return 0.514102 + x*0.0202415

data = np.genfromtxt("data1.dat",delimiter="  ",skip_header=0)

fig, ax = plt.subplots()

x = data[:,0]
y = data[:,1]

ax.scatter(x, y, label="Data Points")

ax.plot(x, f(x), color='red', label="Linear Fit y = 0.0202415x + 0.514102")

plt.xlabel("Positions (cm)", fontsize=15)
plt.ylabel("Voltage (V)", fontsize=15)

plt.legend(fontsize=15)
plt.savefig("Graph.png")
plt.show()



