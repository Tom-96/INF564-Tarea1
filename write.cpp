#include <iostream>
#include <fstream>

using namespace std;
typedef long long lld;

void writeMatrix(lld** matrix, int n, int m) {

  ofstream myfile ("C"+ to_string(n) + "x" + to_string(m) + ".txt");
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