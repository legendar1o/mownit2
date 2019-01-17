import numpy as np

def zad1():
    x = np.float32(1/3)
    y = np.float64(1/3)
    print(x == y)
    z = np.float32(1/3)
    z = np.float64(z)
    print(x == z)
    print(y == z)


