import numpy as np
import matplotlib.pyplot as plt
from os import listdir, walk

def getProm(arr, n):
    arr = np.array_split(arr,len(arr)/n)
    return [sum(i)/n for i in arr]

name = ""
for (dirpath, dirnames, filenames) in walk("images/"):
    if len(filenames) == 0:
        name = "plot1.png"
    else:
        n = int(filenames[-1][4]) + 1
        name = "plot" + str(n) + ".png"
    break

#main 
n = 20
version = "v1"

fig = plt.figure()

for method in ["Trad", "Strassen","Winograd"]:

    xs = []
    ys = []
    zs = []
    LSs = []

    file = open("time" + method + version + ".txt", "r") 

    cont = 0
    for line in file: 
        x,y,ls,z = line.strip().split()
        xs.append(x)
        ys.append(y)
        zs.append(z)
        LSs.append(ls)

    file.close()

    xs = getProm([int(i) for i in xs],n)
    ys = getProm([int(i) for i in ys],n)
    zs = getProm([float(i) for i in zs],n)
    LSs = getProm([float(i) for i in LSs],n)
        
    plt.plot(xs,zs, label=method)

plt.title("Tiempo vs k, n=500")
plt.xlabel("k")
plt.ylabel("tiempo (segundos)")
plt.legend()
plt.show()
fig.savefig('images/' + name)