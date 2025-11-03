import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
import numpy as np
import matplotlib.pyplot as plt
import scipy as sc
from astropy.constants import astropyconst20 as c
import astropy.units as u
from sympy import latex
import scienceplots

plt.style.use(["science", 'no-latex'])


def fit_air(input):
    return linear_fit.slope*input + linear_fit.intercept


data = np.genfromtxt("data.csv",delimiter=",",skip_header=1)

fig, ax = plt.subplots(figsize=(8,5.5))

ax.grid()

x = data[:,0]
y = data[:,1]
yerr = data[:,2]

linear_fit = sc.stats.linregress(x, y)


print('fit', linear_fit)


ax.errorbar(x=x, y=y, xerr=0, yerr=yerr, marker='.', capsize=2, fmt=' ', color='black', markersize=6)

ax.plot(x,fit_air(x), color='r', linewidth=1, label='Linear Fit', linestyle='-.')


ax.set_title('$1/\\lambda$ vs $1 / \\eta_{i}^{2}$', fontsize=20)
ax.set_xlabel('$1 / \\eta_{i}^{2}$', fontsize=16)
ax.set_ylabel('$1/\\lambda$ $(m^{-1})$', fontsize=16)


# ax.set_xlim([0, 13])
# ax.set_ylim([0, 1.75e-5])

 

# ax.plot([], [], ' ', label="Fit equation: y = 9.86816e-07x -8.026e-09 ")
# ax.plot([], [], ' ', label="$R^2$ value: 0.999")
# ax.plot([], [], ' ', label="Error in slope: 3.304e-09")


ax.legend(fontsize=15)




print(c.h)

plt.show()