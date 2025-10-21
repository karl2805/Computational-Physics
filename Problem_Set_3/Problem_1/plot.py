import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

data = np.genfromtxt("data.csv",delimiter=",",skip_header=1)

x = data[:,0]
y = data[:,1]
y1 = data[:,2]
y2 = data[:,3]

fig, ax = plt.subplots()

ax.plot(x,y, label='Bisect')
ax.plot(x,y1, label='Secant')
ax.plot(x,y2, label='Newton-Rapson')

ax.set_xlabel('Iterations', fontsize=20)
ax.set_ylabel('$\log_{10}\left(|\\frac{\\in_{n}}{\\in_{0}}|\\right)$', fontsize=20)
ax.set_yscale('log', base=10)
ax.legend(fontsize=20)
plt.show()