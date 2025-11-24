# import matplotlib.pyplot as plt
# import numpy as np
# from matplotlib.ticker import FuncFormatter

# AU = 1.496e11

# def to_AU(x, pos):
#     return f"{x/AU:.2f}"



# data_day = np.genfromtxt("CSVS/Day_RK2.csv",delimiter=",",skip_header=0)
# data_half_day = np.genfromtxt("CSVS/halfday_RK2.csv",delimiter=",",skip_header=0)
# data_quarter_day = np.genfromtxt("CSVS/quarterday_RK2.csv",delimiter=",",skip_header=0)


# x_day = data_day[:,1]
# y_day = data_day[:,2]

# x_halfday = data_half_day[:,1]
# y_halfday = data_half_day[:,2]

# x_quarterday = data_quarter_day[:,1]
# y_quarterday = data_quarter_day[:,2]


# n_cols = 3
# subplot_size = 7  # width and height of each subplot in inches
# fig = plt.figure(figsize=(n_cols*subplot_size, subplot_size))
# axes = [fig.add_subplot(1, n_cols, i+1) for i in range(n_cols)]

# for x in axes:
#     x.set_xlim(-2*AU, 2*AU)
#     x.set_ylim(-2*AU, 2*AU)
#     x.xaxis.set_major_formatter(FuncFormatter(to_AU))
#     x.yaxis.set_major_formatter(FuncFormatter(to_AU))
#     x.set_xlabel("x Position in AU", fontsize=15)
#     x.set_ylabel("y Position in AU", fontsize=15)

# plt.subplots_adjust(wspace=0.3)

# axes[0].plot(x_day, y_day, 'r')
# axes[1].plot(x_halfday, y_halfday, 'b')
# axes[2].plot(x_quarterday, y_quarterday, 'g')


# plt.tight_layout(rect=[0, 0, 1, 0.95])
# fig.savefig("Plots/RK2_Orbit.png",bbox_inches='tight', dpi=300)



# data_energy = np.genfromtxt("CSVS/Day_E_RK2.csv",delimiter=",",skip_header=0)
# data_momentum = np.genfromtxt("CSVS/Day_L_RK2.csv",delimiter=",",skip_header=0)


# x_e = data_energy[:,0]
# y_e = data_energy[:,1]

# x_L = data_momentum[:,0]
# y_L = data_momentum[:,1]


# n_cols = 2
# subplot_size = 6  # width and height of each subplot in inches
# fig = plt.figure(figsize=(n_cols*subplot_size, subplot_size))
# axes = [fig.add_subplot(1, n_cols, i+1) for i in range(n_cols)]




# plt.subplots_adjust(wspace=0.3)

# axes[0].set_xlabel("Time", fontsize=15)
# axes[0].set_ylabel("Energy", fontsize=15)

# axes[1].set_xlabel("Time", fontsize=15)
# axes[1].set_ylabel("Momentum", fontsize=15)

# axes[0].set_title("Energy", fontsize=15)
# axes[1].set_title("Angular Momentum", fontsize=15)


# axes[0].plot(x_e, y_e, 'r')
# axes[1].plot(x_L, y_L, 'b')




# fig.savefig("Plots/RK2_E_L.png",bbox_inches='tight', dpi=300)

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FuncFormatter
import os

AU = 1.496e11
Year = 60*60*24*365.25
def to_AU(x, pos):
    return f"{x/AU:.2f}"



data_day = np.genfromtxt("CSVS/Day_RK2.csv",delimiter=",",skip_header=0)
data_half_day = np.genfromtxt("CSVS/halfday_RK2.csv",delimiter=",",skip_header=0)
data_quarter_day = np.genfromtxt("CSVS/quarterday_RK2.csv",delimiter=",",skip_header=0)

data_day_euler = np.genfromtxt("CSVS/Day_Euler.csv",delimiter=",",skip_header=0)
data_half_day_euler = np.genfromtxt("CSVS/halfday_Euler.csv",delimiter=",",skip_header=0)
data_quarter_day_euler = np.genfromtxt("CSVS/quarterday_Euler.csv",delimiter=",",skip_header=0)

data_day_RK4 = np.genfromtxt("CSVS/Day_RK4.csv",delimiter=",",skip_header=0)
data_half_day_RK4 = np.genfromtxt("CSVS/halfday_RK4.csv",delimiter=",",skip_header=0)
data_quarter_day_RK4 = np.genfromtxt("CSVS/quarterday_RK4.csv",delimiter=",",skip_header=0)


x_day = data_day[:,1]
y_day = data_day[:,2]

x_halfday = data_half_day[:,1]
y_halfday = data_half_day[:,2]

x_quarterday = data_quarter_day[:,1]
y_quarterday = data_quarter_day[:,2]


# n_cols = 3
# subplot_size = 6  # width and height of each subplot in inches
# fig = plt.figure(figsize=(n_cols*subplot_size, subplot_size))
# axes = [fig.add_subplot(1, n_cols, i+1) for i in range(n_cols)]

# --- NEW LAYOUT: 2 rows × 2 columns ---
fig, axes = plt.subplots(2, 2, figsize=(12, 12))


# Flatten for easier indexing
axes_flat = axes.flatten()

# Use only the first 3 axes, hide the last one
for i in range(3, 4):
    axes_flat[i].axis("off")

# Shared settings for the real axes
for ax in axes_flat[:3]:
    ax.set_xlim(-2*AU, 2*AU)
    ax.set_ylim(-2*AU, 2*AU)
    ax.xaxis.set_major_formatter(FuncFormatter(to_AU))
    ax.yaxis.set_major_formatter(FuncFormatter(to_AU))
    ax.set_xlabel("x Position in AU", fontsize=20)
    ax.set_ylabel("y Position in AU", fontsize=20)
    ax.plot(0, 0, marker="o", markerfacecolor="yellow", markersize=15)

# Titles
axes_flat[0].set_title("Stepsize = 1 Day", fontsize=20)
axes_flat[1].set_title("Stepsize = 1/2 Day", fontsize=20)
axes_flat[2].set_title("Stepsize = 1/4 Day", fontsize=20)

# Data plots
axes_flat[0].plot(x_day, y_day, 'r')
axes_flat[1].plot(x_halfday, y_halfday, 'b')
axes_flat[2].plot(x_quarterday, y_quarterday, 'g')

# Supertitle
fig.suptitle("RK2 Integration of Earth's Orbit using Different Step Sizes",
             fontsize=25, y=0.98)

plt.tight_layout(rect=[0, 0, 1, 0.95])

pos = axes_flat[2].get_position()
new_pos = [pos.x0 + 0.25, pos.y0, pos.width, pos.height]
axes_flat[2].set_position(new_pos)

fig.savefig(
    os.path.dirname(__file__) + "/Write_Up/RK2_Orbit.png",
    bbox_inches='tight', dpi=300
)

data_energy_euler = np.genfromtxt("CSVS/Day_E_Euler.csv",delimiter=",",skip_header=0)
data_momentum_euler = np.genfromtxt("CSVS/Day_L_Euler.csv",delimiter=",",skip_header=0)

data_energy = np.genfromtxt("CSVS/Day_E_RK2.csv",delimiter=",",skip_header=0)
data_momentum = np.genfromtxt("CSVS/Day_L_RK2.csv",delimiter=",",skip_header=0)

data_energy_RK4 = np.genfromtxt("CSVS/Day_E_RK4.csv",delimiter=",",skip_header=0)
data_momentum_RK4 = np.genfromtxt("CSVS/Day_L_RK4.csv",delimiter=",",skip_header=0)


x_e = data_energy[:,0] 
time = x_e / Year

y_e = data_energy[:,1]

x_L = data_momentum[:,0]
y_L = data_momentum[:,1]


n_cols = 2
subplot_size = 6  # width and height of each subplot in inches
fig = plt.figure(figsize=(n_cols*subplot_size, subplot_size))
axes = [fig.add_subplot(1, n_cols, i+1) for i in range(n_cols)]




plt.subplots_adjust(wspace=0.3)

axes[0].set_xlabel("Time (Years)", fontsize=15)
axes[0].set_ylabel("Energy  (J)", fontsize=15)

axes[1].set_xlabel("Time (Years)", fontsize=15)
axes[1].set_ylabel("Momentum ($kgm^2s^{-1}$)", fontsize=15)

axes[0].set_title("Energy", fontsize=15)
axes[1].set_title("Angular Momentum ", fontsize=15)


axes[0].plot(time, y_e, 'g', label="RK2")
axes[0].plot(time, data_energy_RK4[:,1], 'b', label="RK4")
axes[0].plot(time, data_energy_euler[:,1], 'r', label="Euler")
axes[0].legend()

axes[1].plot(time, y_L, 'g', label="RK2")
axes[1].plot(time, data_momentum_RK4[:,1], 'b', label="RK4")
axes[1].plot(time, data_momentum_euler[:,1], 'r', label="Euler")
axes[1].legend()



fig.savefig(os.path.dirname(__file__) + "/Write_Up/RK2_E_L.png",bbox_inches='tight', dpi=300)


fig = plt.figure(figsize=(9, 6))
axes = fig.add_subplot()

euler_radius = np.sqrt(data_day_euler[:,1]**2 + data_day_euler[:,2]**2)
RK2_radius = np.sqrt(data_day[:,1]**2 + data_day[:,2]**2)
RK4_radius = np.sqrt(data_day_RK4[:,1]**2 + data_day_RK4[:,2]**2)

axes.plot(time, RK2_radius, 'g', label='RK2')
axes.plot(time, RK4_radius, 'b', label='RK4')
axes.plot(time, euler_radius, 'r', label='Euler')

axes.yaxis.set_major_formatter(FuncFormatter(to_AU))
axes.set_ylabel("Radius (AU)", fontsize=17)
axes.set_xlabel("Time (Years)", fontsize=17)
axes.set_title("Radius of Orbit with Time for the Methods", fontsize=20)
axes.legend()

fig.savefig(os.path.dirname(__file__) + "/Write_Up/Radius.png",bbox_inches='tight', dpi=300)






