#include <iostream>
#include <fstream>

using namespace std;
typedef long long lld;

void writeMatrix(lld** matrix, int n, int m, string folder) {

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

void writeTime(float time_strassen, float time_traditional, int k, int n, int leaf_size) {

  ofstream myfile ("times.txt", ios_base::app);
  if (myfile.is_open())
  {
    myfile << k << " " << n << " " << leaf_size << " " <<  time_strassen/1000 << " " << time_traditional/1000 << endl;
    myfile.close();
  }
  
}