from matplotlib import pyplot as plt
from numpy import genfromtxt
import numpy as np

my_data = genfromtxt('daxpy_unroll.csv', delimiter=',')

fig_small_sz = 12
fig_med_sz = 15
fig_big_sz = 17
plt.rc("text", usetex='true')
plt.rc("font", size=fig_small_sz, family="serif")
plt.rc("axes", titlesize=fig_small_sz)
plt.rc("axes", labelsize=fig_med_sz)
plt.rc("xtick", labelsize=fig_small_sz)
plt.rc("ytick", labelsize=fig_small_sz)
plt.rc("legend", fontsize=fig_small_sz)
plt.rc("figure", titlesize=fig_big_sz)
plt.rc("figure", dpi=100) 

s = [2 ** x for x in range(8)]
plt.plot(s, my_data)
# plt.plot(np.linspace(2, 1002, 22), my_data[my_data != 0])
plt.ylim((0,0.75))
plt.xscale("log")

plt.xlabel("Size")
plt.ylabel("GFLOPs")
plt.title("daxpy_unroll")
plt.grid()

plt.savefig("daxpy_unroll.png")

plt.show()