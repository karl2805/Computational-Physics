import matplotlib as plt
import astropy.constants as c
import astropy.units as u
import matplotlib.pyplot as plt
import math as m
import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
import numpy as np


#hbar = 1.054571817e-34  
#k_B  = 1.380649e-23     
#omega = 1e13 

hbar = 1 
k_B  = 1   
omega = 1

def U(T):
    x = (hbar * omega) / (k_B * T)
    return hbar * omega * (0.5 + 1/(np.expm1(x))) 

def Cv(T):
    x = (hbar * omega) / (k_B * T)
    return ( ((hbar**2 * omega**2) / (k_B * T**2)) * np.exp(x) ) / ( (np.exp(x)) - 1)**2

def S(T):
    x = (hbar * omega) / (k_B * T)
    return k_B * ( (x / (np.exp(x) - 1)) - np.log(1 - np.exp(-x)) )

x = np.linspace(0.001,500,50000)

y=U(x)
yCv = Cv(x)
yS = S(x)


fig, ax = plt.subplots(1,3)


ax[0].plot(x, y, label='Internal Energy')
ax[1].plot(x, yCv, label='Cv', color='red')
ax[2].plot(x, yS, label='Entropy', color='green')



ax[0].legend(fontsize = 15)
ax[1].legend(fontsize = 15)
ax[2].legend(fontsize = 15)

ax[0].set_title('Internal Energy vs Temperature', fontsize=15)
ax[1].set_title('Cv vs Temperature', fontsize=15)
ax[2].set_title('Entropy vs Temperature', fontsize=15)


ax[0].set_xlabel('$T \\, k_{B}  / \\hbar\\omega$', fontsize=15)
ax[1].set_xlabel('$T \\, k_{B}  / \\hbar\\omega$', fontsize=15)
ax[2].set_xlabel('$T \\, k_{B}  / \\hbar\\omega$', fontsize=15)

ax[0].set_ylabel('U / $\\hbar\\omega$', fontsize=15)
ax[1].set_ylabel('Cv / $k_{B}$', fontsize=15)
ax[2].set_ylabel('S / $k_{B}$', fontsize=15)

ax[0].set_xlim(0,10)
ax[1].set_xlim(0,10)
ax[2].set_xlim(0,10)

ax[0].set_ylim(0,10)
ax[1].set_ylim(0,1.1)
ax[2].set_ylim(0,4)





plt.show()


