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

for method in ["Winograd"]:

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
    
    xdata = []
    ydata = []
    for i in range(len(LSs)):
        xdata.append(LSs[i])
        ydata.append(zs[i])
        if (i+1)%25 == 0 and i > 0:
            plt.plot(xdata,ydata, label="n= " + str(ys[i-1]))
            xdata = []
            ydata = []
        

   
    #plt.plot(LSs,zs, label=method)

plt.title("Winograd, k=1")
plt.xlabel("leaf size")
plt.ylabel("time (seconds)")
plt.legend()
plt.show()
fig.savefig('images/' + name)