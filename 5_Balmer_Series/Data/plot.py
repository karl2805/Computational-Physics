import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
import numpy as np
import matplotlib.pyplot as plt
import scipy as sc
from astropy.constants import astropyconst20 as c
import astropy.units as u
from sympy import latex
import scienceplots
import numpy as np
import statsmodels.api as sm


plt.style.use(["science", 'no-latex'])


def fit(input):
    return results.params[1]*input + results.params[0]


data = np.genfromtxt("data.csv",delimiter=",",skip_header=1)

fig, ax = plt.subplots(figsize=(8,5.5))

ax.grid()

x = data[:,0]
y = data[:,1]
yerr = data[:,2]

x_test = data[:,0]
y_test = data[:,1]

# Calculate weights based on the inverse of the variance of the errors
errors = data[:,2]
weights = 1 / errors

# Fit weighted least squares regression model
x_test = sm.add_constant(x_test)
model = sm.WLS(y_test, x_test, weights=weights)
results = model.fit()

# Print regression results
print(results.summary())

ax.errorbar(x=x, y=y, xerr=0, yerr=yerr, marker='.', capsize=2, fmt=' ', color='black', markersize=6)

ax.plot(x,fit(x), color='r', linewidth=1, label='Linear Fit', linestyle='-.')

ax.set_title('$1/\\lambda$ vs $1 / n_{i}^{2}$', fontsize=20)
ax.set_xlabel('$1 / n_{i}^{2}$', fontsize=16)
ax.set_ylabel('$1/\\lambda$ $(m^{-1})$', fontsize=16)


ax.plot([], [], ' ', label="Linear Fit Slope = -1.107e+07 $\pm$ 4.73e+05")
ax.plot([], [], ' ', label="Intercept: 2.694e+06 $\pm$ 4.19e+04")
ax.plot([], [], ' ', label="$R^2$ value: 0.999")

ax.legend(fontsize=15, loc=3)

ax.set_ylim([1.4e6, 2.4e6])
plt.xticks(fontsize=12)
plt.yticks(fontsize=12)



plt.show()