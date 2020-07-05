// CPP program to implement Strassen’s Matrix  
// Multiplication Algorithm  
#include <bits/stdc++.h> 
#include <chrono>
#include <vector>

#include "Strassen2.hpp"
#include "algorithm2.hpp"
#include "read.hpp"
#include "write.hpp"

using namespace std;  

  
int main(int argc, char** argv)
{   

    int k = stoi(argv[1]), n = stoi(argv[2]), leaf_size = 20, reset = 1;

    if (argc > 3)
    {
        leaf_size = stoi(argv[3]);
        if (argc > 4)
            reset = stoi(argv[4]);
    }

    string file1 = "A" + to_string(k*n) + "x" + to_string(n) + ".txt", 
           file2 = "B" + to_string(n) + "x" + to_string(k*n) + ".txt";
    
    tuple<lld**,int,int> info_X = readMatrix(file1);
    tuple<lld**,int,int> info_Y = readMatrix(file2);

    n = get<1>(info_X);
    int  l = get<2>(info_X), m= get<2>(info_Y);

    if (n == -1 || m == -1)
        return 0;
    lld** X = get<0>(info_X); 
    lld** Y = get<0>(info_Y);

    lld** XY_strassen = new lld*[n];
    lld** XY_trad = new lld*[n];

    for (int i = 0; i < n; i++) 
    {
        XY_strassen[i] = new lld[m];
        XY_trad[i] = new lld[m];
    }

    for(unsigned int i=0; i<n; i++) 
        for (unsigned int j=0; j<m; j++)
        {
            XY_strassen[i][j] = 0;
            XY_trad[i][j] = 0;
        }

    for (int i=0;i<reset;i++)
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        XY_strassen = Product(X, Y, XY_strassen, leaf_size, n, l, m); 
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration_strassen = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

        t1 = std::chrono::high_resolution_clock::now();
        XY_trad = MatrixMultiply(X,Y,XY_trad,0,n,0,l,0,l,0,m,0,n,0,m);
        t2 = std::chrono::high_resolution_clock::now();
        auto duration_trad = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

        //writeTime(duration_strassen,duration_trad, k, n, leaf_size);
    }

    writeMatrix(XY_strassen,n,m,"Strassen");
    writeMatrix(XY_trad,n,m,"traditional");

    return 0; 
} 