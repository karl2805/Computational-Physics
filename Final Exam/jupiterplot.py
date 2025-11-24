import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FuncFormatter

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

data_jupiter = np.genfromtxt("CSVS/Jupiter_With_Earth.csv", delimiter=",",skip_header=0)
data_jupiter_L = np.genfromtxt("CSVS/Earth_With_Jupiter_Jupiter_L.csv", delimiter=",",skip_header=0)
data_jupiter_E = np.genfromtxt("CSVS/Earth_With_Jupiter_Jupiter_E.csv", delimiter=",",skip_header=0)


x_earth = data_earth[:,1]
y_earth = data_earth[:,2]

x_jupiter = data_jupiter[:,1]
y_jupiter = data_jupiter[:,2]

time = data_earth[:,0] / Year


earth_radius = np.sqrt(x_earth**2 + y_earth**2)
earth_L = data_earth_L[:,1]

fig, ax = plt.subplots(figsize=(10, 10))
fig2, ax2 = plt.subplots(figsize=(10, 10))
fig3, ax3 = plt.subplots(figsize=(10, 10))
fig4, ax4 = plt.subplots(figsize=(10, 10))
fig5, ax5 = plt.subplots(figsize=(10, 10))



ax.set_xlim(-7*AU, 7*AU)
ax.set_ylim(-7*AU, 7*AU)
ax.xaxis.set_major_formatter(FuncFormatter(to_AU))
ax.yaxis.set_major_formatter(FuncFormatter(to_AU))
ax.set_xlabel("x Position in AU", fontsize=15)
ax.set_ylabel("y Position in AU", fontsize=15)
plt.subplots_adjust(wspace=0.3)

ax.plot(x_earth, y_earth, 'r')
ax.plot(x_jupiter, y_jupiter, 'g')


ax2.plot(time, earth_L)
ax2.set_title("Earth Angular Momentum", fontsize=15)
plt.savefig("Plots/Earth_Angular_Momentum.png")

ax3.plot(time, data_earth_E[:,1])
ax3.set_title("Earth Energy", fontsize=15)
plt.savefig("Plots/Earth_Energy.png")

ax4.plot(time, earth_radius)
ax4.set_title("Earth Radius", fontsize=15)
plt.savefig("Plots/Earth_Radius.png")

ax5.plot(time, data_earth_e[:,1])
ax5.set_title("Earth Eccentricity", fontsize=15)
plt.savefig("Plots/Earth_e.png")




plt.show()
