from matplotlib import pyplot as plt
import numpy as np


def zad2():
    a = []
    for i in np.linspace(1,1000,1000):
        a.append(np.spacing(i))
    plt.plot(a)
    plt.show()


zad2()