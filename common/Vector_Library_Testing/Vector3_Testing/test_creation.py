import numpy as np
import os
import random
from scipy.linalg import lu

def generate_random_vectors():
    return np.random.normal(size=3)

file = open("testing_in.txt", 'w')
num_test = 10
file.write(str(num_test))
file.write('\n')
file.write('\n')
for i in range(0,num_test):
    s1 = generate_random_vectors()
    s2 = generate_random_vectors()
    s3 = s1+s2
    s4 = s1-s2
    s5 = np.cross(s1,s2)
    s6 = np.dot(s1,s2)

    np.savetxt(file, s1, fmt='%0.8f', delimiter=' ')
    file.write('\n')
    np.savetxt(file, s2, fmt='%0.8f', delimiter=' ')
    file.write('\n')
    np.savetxt(file, s3, fmt='%0.8f', delimiter=' ')
    file.write('\n')
    np.savetxt(file, s4, fmt='%0.8f', delimiter=' ')
    file.write('\n')
    np.savetxt(file, s5, fmt='%0.8f', delimiter=' ')
    file.write('\n')
    file.write(str(s6))
    file.write('\n')
    file.write('\n')


'''
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
        file.write('\n')'''