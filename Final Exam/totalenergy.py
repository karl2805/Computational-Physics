import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FuncFormatter
import os

data_energy = np.genfromtxt("CSVS/totalenergy.csv", delimiter=",",skip_header=0)
time = data_energy[:,0]
energy = data_energy[:,1]


fig, ax = plt.subplots(figsize=(6, 6))


ax.plot(time, energy)

plt.show()
