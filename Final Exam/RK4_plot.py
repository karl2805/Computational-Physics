
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FuncFormatter
import os

AU = 1.496e11
Year = 60*60*24*365.25
def to_AU(x, pos):
    return f"{x/AU:.2f}"


data_day = np.genfromtxt("CSVS/Day_RK4.csv",delimiter=",",skip_header=0)
data_half_day = np.genfromtxt("CSVS/halfday_RK4.csv",delimiter=",",skip_header=0)
data_quarter_day = np.genfromtxt("CSVS/quarterday_RK4.csv",delimiter=",",skip_header=0)


x_day = data_day[:,1]
y_day = data_day[:,2]

x_halfday = data_half_day[:,1]
y_halfday = data_half_day[:,2]

x_quarterday = data_quarter_day[:,1]
y_quarterday = data_quarter_day[:,2]





fig, axes = plt.subplots(2, 2, figsize=(12, 12))


axes_flat = axes.flatten()


for i in range(3, 4):
    axes_flat[i].axis("off")


for ax in axes_flat[:3]:
    ax.set_xlim(-2*AU, 2*AU)
    ax.set_ylim(-2*AU, 2*AU)
    ax.set_xticks(np.arange(-2*AU,3*AU, AU))
    ax.set_yticks(np.arange(-2*AU,3*AU, AU))
    ax.xaxis.set_major_formatter(FuncFormatter(to_AU))
    ax.yaxis.set_major_formatter(FuncFormatter(to_AU))
    ax.set_xlabel("x Position in AU", fontsize=20)
    ax.set_ylabel("y Position in AU", fontsize=20)
    ax.tick_params(axis='x', labelsize= 13)
    ax.tick_params(axis='y', labelsize= 13)
    ax.plot(0, 0, marker="o", markerfacecolor="yellow", markersize=15)


axes_flat[0].set_title("Stepsize = 1 Day", fontsize=20)
axes_flat[1].set_title("Stepsize = 1/2 Day", fontsize=20)
axes_flat[2].set_title("Stepsize = 1/4 Day", fontsize=20)


axes_flat[0].plot(x_day, y_day, 'r')
axes_flat[1].plot(x_halfday, y_halfday, 'b')
axes_flat[2].plot(x_quarterday, y_quarterday, 'g')


fig.suptitle("RK4 Integration of Earth's Orbit using Different Step Sizes",
             fontsize=25, y=0.98)

plt.tight_layout(rect=[0, 0, 1, 0.95])

pos = axes_flat[2].get_position()
new_pos = [pos.x0 + 0.25, pos.y0, pos.width, pos.height]
axes_flat[2].set_position(new_pos)

fig.savefig(
    os.path.dirname(__file__) + "/Write_Up/RK4_Orbit.png",
    bbox_inches='tight', dpi=300
)





