import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FuncFormatter

AU = 1.496e11

def to_AU(x, pos):
    return f"{x/AU:.2f}"



data_day = np.genfromtxt("CSVS/Day_RK2.csv",delimiter=",",skip_header=0)
data_half_day = np.genfromtxt("CSVS/halfday_RK2.csv",delimiter=",",skip_header=0)
data_quarter_day = np.genfromtxt("CSVS/quarterday_RK2.csv",delimiter=",",skip_header=0)


x_day = data_day[:,1]
y_day = data_day[:,2]

x_halfday = data_half_day[:,1]
y_halfday = data_half_day[:,2]

x_quarterday = data_quarter_day[:,1]
y_quarterday = data_quarter_day[:,2]


n_cols = 3
subplot_size = 7  # width and height of each subplot in inches
fig = plt.figure(figsize=(n_cols*subplot_size, subplot_size))
axes = [fig.add_subplot(1, n_cols, i+1) for i in range(n_cols)]

for x in axes:
    x.set_xlim(-2*AU, 2*AU)
    x.set_ylim(-2*AU, 2*AU)
    x.xaxis.set_major_formatter(FuncFormatter(to_AU))
    x.yaxis.set_major_formatter(FuncFormatter(to_AU))
    x.set_xlabel("x Position in AU", fontsize=15)
    x.set_ylabel("y Position in AU", fontsize=15)

plt.subplots_adjust(wspace=0.3)

axes[0].plot(x_day, y_day, 'r')
axes[1].plot(x_halfday, y_halfday, 'b')
axes[2].plot(x_quarterday, y_quarterday, 'g')



fig.savefig("Plots/RK2_Orbit.png",bbox_inches='tight', dpi=300)



data_energy = np.genfromtxt("CSVS/Day_E_RK2.csv",delimiter=",",skip_header=0)
data_momentum = np.genfromtxt("CSVS/Day_L_RK2.csv",delimiter=",",skip_header=0)


x_e = data_energy[:,0]
y_e = data_energy[:,1]

x_L = data_momentum[:,0]
y_L = data_momentum[:,1]


n_cols = 2
subplot_size = 6  # width and height of each subplot in inches
fig = plt.figure(figsize=(n_cols*subplot_size, subplot_size))
axes = [fig.add_subplot(1, n_cols, i+1) for i in range(n_cols)]




plt.subplots_adjust(wspace=0.3)

axes[0].set_xlabel("Time", fontsize=15)
axes[0].set_ylabel("Energy", fontsize=15)

axes[1].set_xlabel("Time", fontsize=15)
axes[1].set_ylabel("Momentum", fontsize=15)

axes[0].set_title("Energy", fontsize=15)
axes[1].set_title("Angular Momentum", fontsize=15)


axes[0].plot(x_e, y_e, 'r')
axes[1].plot(x_L, y_L, 'b')




fig.savefig("Plots/RK2_E_L.png",bbox_inches='tight', dpi=300)





