import numpy as np
from scipy.misc import imread, imsave, imresize
from scipy.spatial.distance import cdist, pdist, squareform
import matplotlib.pyplot as plt
from math import sqrt

x = np.array([ [0, 0, 1], [0, 1, 1], [1, 0, 1], [1, 1, 1] ])
# x0 = np.array([ [2, 3, 4], [5, 6, 7], [8, 9, 10], [11, 12, 13] ])
# x1 = np.array([ [14, 15, 16, 17], [18, 19, 20, 21], [22, 23, 24, 25] ])
x0 = np.array([ [1, 1, 1], [1, 1, 1], [1, 1, 1], [1, 1, 1] ])
x1 = np.array([ [1, 1, 1, 1], [1, 1, 1, 1], [1, 1, 1, 1] ])
# pr = np.dot(x0, x1)
pr = x0 * x1
print pr
print x0.shape
print x1.shape
