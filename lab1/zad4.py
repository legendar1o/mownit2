import numpy as np


def nonstablefun(a, b):
    return np.float64(((a * a) - (b * b)))


def stablefun(a, b):
    return np.float64((a - b) * (a + b))


if __name__ == "__main__":
    x = 0.01
    y = 0.1

    for i in range(1000):
        print("Not stable - ")
        print(nonstablefun(x, y))
        print("Stable - ")
        print(stablefun(x, y))
        print("Difference - ")
        print(abs(nonstablefun(x, y) - stablefun(x, y)))
        x += 1.0
        y += 1.0

