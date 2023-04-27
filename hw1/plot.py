from matplotlib import pyplot as plt
import numpy as np

p = np.array([0,0.0625,0.125,0.1875,0.25,0.3125,0.375,0.4375,0.5,0.625,0.75,0.875,1,1.25,1.5,1.75,2,2.5,3,3.5,4,5,6,7,8,10,12,14])
n = -p

plt.figure()
plt.scatter(p, np.zeros(np.size(p)), color="blue")
plt.scatter(n, np.zeros(np.size(n)), color="blue")
plt.title("6 Bit Floating Point Numbers")
plt.show()