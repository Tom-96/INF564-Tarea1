import numpy as np

#parametros

n = 500
m = 500
filename = "B" + str(n) + "x" + str(m) + ".txt"

a = []

for i in range(n):
    a.append([j for j in range(m)])

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