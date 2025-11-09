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

fig, ax = plt.subplots(figsize=(8,5.5))


data = np.genfromtxt("pierror.csv",delimiter=",",skip_header=1)

ax.set_xlabel("Number of points", fontsize=18)
ax.set_ylabel("Absolute Percentage Error", fontsize=18)
ax.set_title("Error of Monte Carlo Estimation of PI with increasing points", fontsize=20)


ax.grid()


x = data[:,0]

y = data[:,1]

ax.plot(x,y)

plt.show()