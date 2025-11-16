import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FuncFormatter

AU = 1.496e11

def to_AU(x, pos):
    return f"{x/AU:.2f}"



data_day = np.genfromtxt("Day.csv",delimiter=",",skip_header=0)
data_half_day = np.genfromtxt("halfday.csv",delimiter=",",skip_header=0)
data_quarter_day = np.genfromtxt("quarterday.csv",delimiter=",",skip_header=0)

data_energy = np.genfromtxt("Momentum.csv",delimiter=",",skip_header=0)

fig, ax = plt.subplots(figsize=(10, 10))
fig, ax_energy = plt.subplots(figsize=(10,10))

x_day = data_day[:,0]
y_day = data_day[:,1]

x_halfday = data_half_day[:,0]
y_halfday = data_half_day[:,1]

x_quarterday = data_quarter_day[:,0]
y_quarterday = data_quarter_day[:,1]

x_energy = data_energy[:,0]
y_energy = data_energy[:,1]

ax.xaxis.set_major_formatter(FuncFormatter(to_AU))
ax.yaxis.set_major_formatter(FuncFormatter(to_AU))

ax.set_title("Orbit of Earth using Euler Method", fontsize=15)
ax.set_xlabel("x Position in AU", fontsize=15)
ax.set_ylabel("y Position in AU", fontsize=15)


ax.plot(x_day, y_day, 'r')
ax.plot(x_halfday, y_halfday, 'b')
ax.plot(x_quarterday, y_quarterday, 'g')

ax_energy.plot(x_energy, y_energy, 'r')
ax_energy.set_xlabel('Time (seconds)', fontsize=15)
ax_energy.set_ylabel('Energy (J)', fontsize=15)            
ax_energy.set_title('Energy vs Time for Euler Integration')


fig.savefig("Earth_orbit_euler.pdf",bbox_inches='tight', dpi=300)

plt.show()