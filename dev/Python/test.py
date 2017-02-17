import numpy as np
from scipy.misc import imread, imsave, imresize
from scipy.spatial.distance import cdist, pdist, squareform
import matplotlib.pyplot as plt
from math import sqrt

#
# nums = [sqrt(x) for x in range(30)]
#
# print nums, len(nums)

# list
# girls = ['xichuan', 'jingjing', 'future']
# for i in girls[0:2]:
#     print i
# for index, girl in enumerate(girls):
#     print '#%d: %s' % (index + 1, girl)
# print 'future' in girls
#
# traverse list(multidimension array)
# d2_list = [[1.2, 2, 3], [4, 5]]
# print d2_list[d2_list > 2]
# for index1, x in enumerate(d2_list):
#     for index2, y in enumerate(x):
#         print '[%d][%d]:' % (index1, index2), y

# nums = range(5)
# squares = [x ** 2 for x in nums]
# print squares

# dictionary
# adore = {'panyutong': 25, 'future': 26}
#
# for name, age in adore.iteritems():
#     print '%s is %d years old.' % (name, age)

# set
# axis = [(1,2,3), (4,5,6)]
# print axis[1][1]

#
# Function Definition
#

# def myfunc(name, flag = False):
#     if flag:
#         print 'Yes!'
#     else:
#         print 'No!'
# myfunc('panyutong')
# myfunc('panyutong', True)

#
# Class Definition
#

# class MyPerson(object):
#
#     def __init__(self, name):
#         self.name = name
#
#     def intro(self):
#         print 'My name is %s' % (self.name)
#
# p = MyPerson('panyutong')
# p.intro()

#
# Numpy Usage
#


# d1 = np.array([1, 2, 3])
# d2 = np.array([[1.2, 2], [4, 5], [7, 8]])
# d3 = np.array([[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [11, 12, 13]]])
# int_index = d2[[0, 1], [0, 1]]
# print d2
# print int_index
# d2_1 = np.array([[1, 2], [1, 2]])
# c_arr = np.array([chr(48), chr(18)])
# print c_arr

#
# Create a random matrix
#
# rand = np.random.random((2, 2, 2))
# print rand

# a = np.array([[[1, 2, 3], [3, 4, 5]], [[5, 6, 7], [7, 8, 9]]])
# print a.shape
# print np.sum(a)
# print np.sum(a, axis = 1)

# x = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
# v = np.array([[1, 2, 3]])
# vtile = np.tile(v, (4, 4))
# print v.shape
# if v.shape == (1, 3):
#     print "pyt"
# print v
# print vtile

# image operations!!!
# matA = np.array([[1, 2], [3, 4]])
# matB = np.array([[4, 5], [2, 4]])
# d = cdist(matA, matB, 'euclidean')
# print d

# img = imread('images/cat.jpg')
# plt.imshow(img)
# plt.subplot(2, 3, 1)
# plt.imshow(img)
# plt.subplot(2, 3, 3)
# plt.imshow(img)
# plt.show()

# x = np.arange(0, 3 * np.pi, 0.1)
# z = np.cos(x)
# y = np.sin(x)
# plt.plot(x, y)
# plt.plot(x, z)
# plt.legend(['Sine', 'Cosine'])
# plt.show()

# class NBtest(object):
# 
#     def __init__(self):
#         pass
# 
#     def test1(self, X):
#         self.Xtr = X
# 
#     def show(self):
#         print self.Xtr
# 
#     def mindist(self, X):
#         
#         for i in range(2):
# 
#             dist = np.linalg.norm(self.Xtr, X)
#             print dist
# 
# arr1 = np.array([[1, 2, 3], [4, 5, 6]])
# arr2 = np.array([[3, 8, 4], [5, 7, 9]])
# 
# nb1 = NBtest()
# nb1.test1(arr1)
# nb1.mindist(arr2)

# x = np.random.random((3, 3, 3))
# print x

data = open('input.txt', 'r').read()
chars = list(set(data))
data_size, vocab_size = len(data), len(chars)
char_to_idx = {ch:i for i, ch in enumerate(chars)}
idx_to_char = {i:ch for i, ch in enumerate(chars)}

hidden_size = 100
seq_length = 25
learning_rate = 1e-1

Wxh = np.random.randn(hidden_size, vocab_size) * 0.01
Whh = np.random.randn(hidden_size, hidden_size) * 0.01
Why = np.random.randn(vocab_size, hidden_size) * 0.01
bh = np.zeros((hidden_size, 1))
by = np.zeros(vocab_size, 1))





n, p = 0, 0
mWxh, mWhh, mWhy = np.zeros_like(Wxh), np.zero_like(Whh), np.zeros_like(Why)
mbh, mby = np.zeros_like(bh), np.zeros_like(by)
smooth_loss = -np.log(1.0 / vocab_size) * seq_length
while True:
    if p + seq_length + 1 > len(data) or n == 0:
        hprev = np.zeros((hidden_size, 1))
        p = 0
        inputs = [char_to_idx[ch] for ch in data[p:p + seq_length]]
        targets = [char_to_idx[ch] for ch in data[p + 1: p + seq_length + 1]]

    if n % 100 == 0:
