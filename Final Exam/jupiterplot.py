import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FuncFormatter
import os

AU = 1.496e11
Year = 60*60*24*365.25

def to_AU(x, pos):
    return f"{x/AU:.2f}"

def to_years(thing):
    return f"{thing/Year:.2f}"



data_earth = np.genfromtxt("CSVS/Earth_With_Jupiter.csv", delimiter=",",skip_header=0)
data_earth_L = np.genfromtxt("CSVS/Earth_With_Jupiter_Earth_L.csv", delimiter=",",skip_header=0)
data_earth_E = np.genfromtxt("CSVS/Earth_With_Jupiter_Earth_E.csv", delimiter=",",skip_header=0)
data_earth_e = np.genfromtxt("CSVS/Earth_e.csv", delimiter=",",skip_header=0)

data_Jupiter = np.genfromtxt("CSVS/Jupiter_With_Earth.csv", delimiter=",",skip_header=0)
data_Jupiter_L = np.genfromtxt("CSVS/Earth_With_Jupiter_Jupiter_L.csv", delimiter=",",skip_header=0)
data_Jupiter_E = np.genfromtxt("CSVS/Earth_With_Jupiter_Jupiter_E.csv", delimiter=",",skip_header=0)


x_earth = data_earth[:,1]
y_earth = data_earth[:,2]

x_Jupiter = data_Jupiter[:,1]
y_Jupiter = data_Jupiter[:,2]

time = data_earth[:,0] / Year

earth_radius = np.sqrt(x_earth**2 + y_earth**2) / AU
earth_L = data_earth_L[:,1] 

Jupiter_radius = np.sqrt(x_Jupiter**2 + y_Jupiter**2) 
Jupiter_L = data_Jupiter_L[:,1]

fig, ax = plt.subplots(figsize=(6, 6))
fig2, ax2 = plt.subplots(figsize=(15, 6))
fig3, ax3 = plt.subplots(figsize=(15, 6))
fig4, ax4 = plt.subplots(figsize=(15, 6))
fig5, ax5 = plt.subplots(figsize=(9, 6))


ax.xaxis.set_major_formatter(FuncFormatter(to_AU))
ax.yaxis.set_major_formatter(FuncFormatter(to_AU))
ax.set_xlabel("x Position in AU", fontsize=15)
ax.set_ylabel("y Position in AU", fontsize=15)
plt.subplots_adjust(wspace=0.3)

ax.plot(x_earth, y_earth, 'r', label='Earth')
ax.plot(x_Jupiter, y_Jupiter, 'g', label='Jupiter')
ax.set_xticks(np.arange(-6*AU,7*AU, 2*AU))
ax.set_yticks(np.arange(-6*AU,7*AU, 2*AU))
ax.set_title("Orbit of Earth and Jupiter", fontsize=20)
ax.set_xlabel("X Position (AU)")
ax.set_ylabel("Y Position (AU)")


fig.savefig(os.path.dirname(__file__) + "/Write_Up/Earth_Jupiter_Orbit.png",bbox_inches='tight', dpi=300)


ax2.plot(time, earth_L, 'b')
ax2.set_xlim(0,24)
ax2.set_title("$\\Delta$ Earth Angular Momentum with Presence of Jupiter", fontsize=20)
ax2.set_xlabel("Time (Years)", fontsize=17)
ax2.set_ylabel("$\\Delta$ Angular Momentum ($kgm^2s^{-1}$)", fontsize=17)
ax2.set_xticks(np.arange(25))
fig2.savefig(os.path.dirname(__file__) + "/Write_Up/Earth_Angular_Momentum.png",bbox_inches='tight', dpi=300)


ax3.plot(time, data_earth_E[:,1], 'red', label="Kinetic Energy")
ax3.set_xlim(0,24)
ax3.set_title("$\\Delta$ Earth Energy with Presence of Jupiter", fontsize=20)
ax3.set_xlabel("Time (Years)", fontsize=17)
ax3.set_ylabel("$\\Delta$ Energy ($J$)", fontsize=17)
ax3.set_xticks(np.arange(25))

fig3.savefig(os.path.dirname(__file__) + "/Write_Up/Earth_Energy.png",bbox_inches='tight', dpi=300)

ax4.plot(time, earth_radius, 'navy')
ax4.set_title("Earth Orbit Radius with Jupiter Present", fontsize=20)
ax4.set_xlabel("Time (Years)", fontsize=17)
ax4.axvline(12, color='r', linestyle='--', label="Jupiter Period")
ax4.axvline(24, color='r', linestyle='--', label="Jupiter Period")
ax4.set_ylabel("Radius (AU)", fontsize=17)
ax4.set_xticks(np.arange(25))
fig4.savefig(os.path.dirname(__file__) + "/Write_Up/Earth_Radius.png",bbox_inches='tight', dpi=300)




ax2.clear()
ax3.clear()
ax4.clear()



fig2, ax2 = plt.subplots(figsize=(15,6))
fig3, ax3 = plt.subplots(figsize=(15,6))
fig4, ax4 = plt.subplots(figsize=(15,6))

ax2.plot(time, Jupiter_L, 'orange')
ax2.set_xlim(0,24)
ax2.set_xticks(np.arange(25))
ax2.set_title("$\\Delta$ Jupiter Angular Momentum", fontsize=20)
ax2.set_xlabel("Time (Years)", fontsize=17)
ax2.set_ylabel("$\\Delta$ Angular Momentum ($kgm^2s^{-1}$)", fontsize=17)
fig2.savefig(os.path.dirname(__file__) + "/Write_Up/Jupiter_Angular_Momentum.png",bbox_inches='tight', dpi=300)

ax3.plot(time, data_Jupiter_E[:,1])
ax3.set_xlim(0,24)
ax3.set_xticks(np.arange(25))
ax3.set_title("$\\Delta$ Jupiter Energy", fontsize=20)
ax3.set_xlabel("Time (Years)", fontsize=17)
ax3.set_ylabel("$\\Delta$ Energy ($J$)", fontsize=17)
fig3.savefig(os.path.dirname(__file__) + "/Write_Up/Jupiter_Energy.png",bbox_inches='tight', dpi=300)

ax4.plot(time, Jupiter_radius)
ax4.set_title("Jupiter Radius", fontsize=20)
ax4.set_xlabel("Time (Years)", fontsize=17)
ax4.set_ylabel("Radius (AU)", fontsize=17)
fig4.savefig(os.path.dirname(__file__) + "/Write_Up/Jupiter_Radius.png",bbox_inches='tight', dpi=300)





