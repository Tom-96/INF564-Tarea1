import numpy as np
import sys


#parametros

matrix = sys.argv[1]
n = int(sys.argv[2])
m = int(sys.argv[3])

filename = "matrixes/" + matrix + str(n) + "x" + str(m) + ".txt"

a = []

for i in range(n):
    a.append([j+1 for j in range(m)])

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