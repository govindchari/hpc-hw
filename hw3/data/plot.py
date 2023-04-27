from matplotlib import pyplot as plt
from numpy import genfromtxt
import numpy as np

jki_d_def = genfromtxt('time_jki_double_def.csv', delimiter=',')
jki_d_o3 = genfromtxt('time_jki_double_o3.csv', delimiter=',')
jki_d_fm = genfromtxt('time_jki_double_fast_math.csv', delimiter=',')

kij_d_def = genfromtxt('time_kij_double_def.csv', delimiter=',')
kij_d_o3 = genfromtxt('time_kij_double_o3.csv', delimiter=',')
kij_d_fm = genfromtxt('time_kij_double_fast_math.csv', delimiter=',')

jki_f_def = genfromtxt('time_jki_float_def.csv', delimiter=',')
jki_f_o3 = genfromtxt('time_jki_float_o3.csv', delimiter=',')
jki_f_fm = genfromtxt('time_jki_float_fast_math.csv', delimiter=',')

kij_f_def = genfromtxt('time_kij_float_def.csv', delimiter=',')
kij_f_o3 = genfromtxt('time_kij_float_o3.csv', delimiter=',')
kij_f_fm = genfromtxt('time_kij_float_fast_math.csv', delimiter=',')

sdef = genfromtxt('strassen_def.csv', delimiter=',')
so3 = genfromtxt('strassen_o3.csv', delimiter=',')
sfm = genfromtxt('strassen_fast_math.csv', delimiter=',')

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

s = np.linspace(2, 512, num=512)

plt.figure(dpi=150)
plt.suptitle("Double Gemm")
plt.subplot(1,2,1)
plt.plot(s, jki_d_def, label="Default", color='blue')
plt.plot(s, jki_d_o3, label="-O3", color='red')
plt.plot(s, jki_d_fm, label="-O3 -ffast-math", color='green')
plt.ylim((0,8))
plt.xlabel("n")
plt.ylabel("GFLOPs")
plt.title("jki")
plt.legend()
plt.grid()

plt.subplot(1,2,2)
plt.plot(s, kij_d_def, label="Default", color='blue')
plt.plot(s, kij_d_o3, label="-O3", color='red')
plt.plot(s, kij_d_fm, label="-O3 -ffast-math", color='green')
plt.xlabel("n")
plt.ylabel("GFLOPs")
plt.title("kij")
plt.legend()
plt.grid()
plt.ylim((0,8))

plt.savefig("double_gemm.png")

plt.figure(dpi=150)
plt.suptitle("Float Gemm")
plt.subplot(1,2,1)
plt.plot(s, jki_f_def, label="Default", color='blue')
plt.plot(s, jki_f_o3, label="-O3", color='red')
plt.plot(s, jki_f_fm, label="-O3 -ffast-math", color='green')
plt.ylim((0,8))
plt.xlabel("n")
plt.ylabel("GFLOPs")
plt.title("jki")
plt.legend()
plt.grid()

plt.subplot(1,2,2)
plt.plot(s, kij_f_def, label="Default", color='blue')
plt.plot(s, kij_f_o3, label="-O3", color='red')
plt.plot(s, kij_f_fm, label="-O3 -ffast-math", color='green')
plt.xlabel("n")
plt.ylabel("GFLOPs")
plt.title("kij")
plt.legend()
plt.grid()
plt.ylim((0,8))

plt.savefig("float_gemm.png")

plt.figure(dpi=150)
s = [2**m for m in range(1,11)]
plt.plot(s, sdef, label="Default", color='blue')
plt.plot(s, so3, label="-O3", color='red')
plt.plot(s, sfm, label="-O3 -ffast-math", color='green')
plt.xlabel("n")
plt.ylabel("GFLOPs")
plt.title("Strassen")
plt.legend()
plt.grid()
plt.ylim((0,0.2))
plt.xscale("log")

plt.savefig("strassen.png")

plt.show()