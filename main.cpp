// CPP program to implement Strassen’s Matrix  
// Multiplication Algorithm  
#include <bits/stdc++.h> 
#include <chrono>
#include <vector>

#include "Strassen.hpp"
#include "algorithm.hpp"
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

    lld** XY_strassen;
    lld** XY_winograd;
    lld** XY_trad;

    for (int i=0;i<reset;i++)
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        XY_strassen = Product(X, Y, leaf_size, n, l, m, "Strassen"); 
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration_strassen = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

        t1 = std::chrono::high_resolution_clock::now();
        XY_winograd = Product(X, Y, leaf_size, n, l, m, "Winograd"); 
        t2 = std::chrono::high_resolution_clock::now();
        auto duration_winograd = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

        t1 = std::chrono::high_resolution_clock::now();
        XY_trad = MatrixMultiply(X,Y,n,l,m);
        t2 = std::chrono::high_resolution_clock::now();
        auto duration_trad = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

        writeTime("Strassen",duration_strassen, k, n, leaf_size, "v1");
        writeTime("Winograd",duration_winograd, k, n, leaf_size, "v1");
        writeTime("Trad",duration_trad, k, n, leaf_size, "v1");
    }

    writeMatrix(XY_strassen,n,m,"Strassen");
    writeMatrix(XY_trad,n,m,"traditional");

    return 0; 
} 