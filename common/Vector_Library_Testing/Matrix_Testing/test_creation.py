import numpy as np
import os
import random
from scipy.linalg import lu


def generate_random_matrices(rows, cols):
    return np.random.randn(rows, cols)

'''
Generate random matrices of same size and do sum, and difference
'''
file = open("testing_in.txt", 'w')
total_testing = 3
num_test = 10
low = 1
high = 10
file.write(str(total_testing))
file.write('\n')
file.write(str(num_test))
file.write('\n')
if(total_testing == 1):
    for i in range(0,num_test):
        s1 = random.randint(low, high)
        s2 = random.randint(low, high)
        file.write(str(s1))
        file.write(" ")
        file.write(str(s2))
        file.write('\n')
        m1 = generate_random_matrices(s1,s2)
        m2 = generate_random_matrices(s1,s2)
        m3 = m1+m2
        m4 = m1-m2
        np.savetxt(file, m1, fmt='%0.8f', delimiter=' ')
        file.write('\n')
        np.savetxt(file, m2, fmt='%0.8f', delimiter=' ')
        file.write('\n')
        np.savetxt(file, m3, fmt='%0.8f', delimiter=' ')
        file.write('\n')
        np.savetxt(file, m4, fmt='%0.8f', delimiter=' ')
        file.write('\n')
elif(total_testing == 2):
    for i in range(0,num_test):
        s1 = random.randint(low, high)
        s2 = random.randint(low, high)
        s3 = random.randint(low, high)
        file.write(str(s1))
        file.write(" ")
        file.write(str(s2))
        file.write(" ")
        file.write(str(s3))
        file.write('\n')
        m1 = generate_random_matrices(s1,s2)
        m2 = generate_random_matrices(s2,s3)
        m3 = np.matmul(m1,m2)
        np.savetxt(file, m1, fmt='%0.8f', delimiter=' ')
        file.write('\n')
        np.savetxt(file, m2, fmt='%0.8f', delimiter=' ')
        file.write('\n')
        np.savetxt(file, m3, fmt='%0.8f', delimiter=' ')
        file.write('\n')
elif(total_testing == 3):
    for i in range(0,num_test):
        s1 = random.randint(low, high)
        file.write(str(s1))
        file.write('\n')
        m1 = generate_random_matrices(s1,s1)
        P, L, U = lu(m1)
        np.savetxt(file, m1, fmt='%0.8f', delimiter=' ')
        file.write('\n')
        np.savetxt(file, P, fmt='%0.8f', delimiter=' ')
        file.write('\n')
        np.savetxt(file, L, fmt='%0.8f', delimiter=' ')
        file.write('\n')
        np.savetxt(file, U, fmt='%0.8f', delimiter=' ')
        file.write('\n')