import numpy as np
import sys


#parametros

#matrix corresponde a la matriz, puede tomar 2 valores, A o B
matrix = sys.argv[1]

#n y m corresponden a las dimensiones de matrix
n = int(sys.argv[2])
m = int(sys.argv[3])

filename = "matrixes/" + matrix + str(n) + "x" + str(m) + ".txt"

a = []

for i in range(n):
    if matrix == "A":
        a.append([np.sqrt(5)*(i+j-1) for j in range(m)])
    if matrix == "B":
        a.append([np.sqrt(3)*(n-i-1) for j in range(m)])

#funcion que genera la matriz con los parametros definidos anteriormente
def write_matrix_to_textfile(a_matrix, file_to_write):

    def compile_row_string(a_row):
        return str(a_row).strip(']').strip('[').replace(',','')

    with open(file_to_write, 'w') as f:
        for idx, row in enumerate(a_matrix):
            if idx < len(a_matrix) - 1:
                f.write(compile_row_string(row)+' \n')
            else:
                f.write(compile_row_string(row) + ' ')

    return True

write_matrix_to_textfile(a,filename)