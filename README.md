## Algoritmo  de Strassen

## Requerimientos
- Python 3
- numpy, matplotlib

## Comandos para ejecutar Algoritmo

$ make  


$ ./exev1 k n leaf_size reset

- k y n corresponden a los parametros del problema 
- leaf_size es el tamaño hasta donde se aplica Strassen
- reset corresponde a la cantidad de ejecuciones del algoritmo

## Comando para generar matrices
$ python gen_matrix.py M n m

- M corresponde a la matriz que se quiere generar (A o B)
- n a la cantidad de filas
- m a la cantidad de columnas

## Consideraciones:
- Las matrices generadas por gen_matrix.py quedan en matrixes/
- Los graficos generadas en plot.py se guardan en images/
- Las matrices resultantes de cada implementacion del algoritmo se guardan en output_Strassen, output_Winograd y output_traditional
- Los tiempos de cada algoritmo se guardan en distintos archivos con el siguiente formato: "k n leaf_size time"
- Se intento crear una segunda version del algoritmo de winograd (tercera algoritmo del informe) que no asignara memoria para tener un mejor desempeño pero no se logro buenos resultados con la implementacion. Es por esto, que los archivos que se utilizan para este trabajo son los v1, los que terminan en v2 son esta version que no esta completa

