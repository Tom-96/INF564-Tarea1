from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()
ax = plt.axes(projection="3d")

z = [500,600,1100]
x = [1,1,1]
y  = [150,250,500]
ax.plot3D(x, y, z)

plt.show()