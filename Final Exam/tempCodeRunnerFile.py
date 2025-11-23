import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FuncFormatter

AU = 1.496e11

def to_AU(x, pos):
    return f"{x/AU:.2f}"



data_day = np.genfromtxt("CSVS/Day_Euler.csv",delimiter=",",skip_header=0)
data_half_day = np.genfromtxt("CSVS/halfday_Euler.csv",delimiter=",",skip_header=0)
data_quarter_day = np.genfromtxt("CSVS/quarterday_Euler.csv",delimiter=",",skip_header=0)


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
fig.suptitle("Euler Integration of Earth's Orbit using Different Step Sizes",
             fontsize=25, y=0.98)

plt.tight_layout(rect=[0, 0, 1, 0.95])

fig.savefig(
    "C:/Users/karlr/OneDrive/Documents/Comp/Computational-Physics/Final Exam/Write_Up/Euler_Orbit.png",
    bbox_inches='tight', dpi=300
)