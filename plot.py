from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt

def getProm(arr, n):
    arr = np.array_split(arr,len(arr)/10)
    return [sum(i)/n for i in arr]

n = 20
version = "v1"

xs = []
ys = []
z1s = []
z2s = []

file = open("times" + version + ".txt", "r") 

#[k, n, leaf_size, time_strassen, time_trad]
# time in seconds

cont = 0
for line in file: 
    x,y,_,z1,z2 = line.strip().split()
    xs.append(x)
    ys.append(y)
    z1s.append(z1)
    z2s.append(z2)

fig = plt.figure()
ax = plt.axes(projection="3d")


xs = getProm([int(i) for i in xs],n)
ys = getProm([int(i) for i in ys],n)
z1s = getProm([float(i) for i in z1s],n)
z2s = getProm([float(i) for i in z2s],n)

ax.plot3D(ys,xs,z1s, label="Strassen")
ax.plot3D(ys,xs,z2s, label="trad")

plt.legend()
plt.show()