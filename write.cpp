#include <iostream>
#include <fstream>

using namespace std;
typedef long long lld;

//funcion que guarda la matriz resultante C en la carpeta folder
void writeMatrix(lld** matrix, int n, int m, string folder) 
{
  ofstream myfile ("output_" + folder + "/C"+ to_string(n) + "x" + to_string(m) + ".txt");
  if (myfile.is_open())
  {
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            myfile << matrix[i][j] << " ";
        if (i < n-1)
            myfile << endl;
    }
    myfile.close();
  }
}

//funcion que guarda el tiempo de los algoritmos en un archivo
void writeTime(string method, float time_method, int k, int n, int leaf_size, string version) 
{
  ofstream myfile ("time" + method + version + ".txt", ios_base::app);
  if (myfile.is_open())
  {
    myfile << k << " " << n << " " << leaf_size << " " <<  time_method/1000000 << endl;
    myfile.close();
  }
}