// CPP program to implement Strassen’s Matrix  
// Multiplication Algorithm  
#include <bits/stdc++.h> 
#include <chrono>
#include <vector>

#include "Strassen.hpp"
#include "algorithm.hpp"
#include "read.hpp"

using namespace std;  

  
int main() 
{   
    tuple<lld**,int,int> info_X = getMatrix("matrixA.txt");
    tuple<lld**,int,int> info_Y = getMatrix("matrixB.txt");

    int n = get<1>(info_X), l = get<2>(info_X), m= get<2>(info_Y);

    lld** X = get<0>(info_X); 
    lld** Y = get<0>(info_Y);
    
    
    auto t1 = std::chrono::high_resolution_clock::now();
    lld** XY = Product(X, Y, n, l, m); 
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << duration << "\n";

    
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < m; j++) { 
            printf("%lld ", XY[i][j]); 
        } 
        printf("\n"); 
    } 

    t1 = std::chrono::high_resolution_clock::now();
    lld** mult = MatrixMultiply(X,Y,n,l,m);
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << duration << "\n";
    
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < m; j++) { 
            printf("%lld ", mult[i][j]); 
        } 
        printf("\n"); 
    } 

    return 0; 
} 