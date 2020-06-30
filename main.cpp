// CPP program to implement Strassen’s Matrix  
// Multiplication Algorithm  
#include <bits/stdc++.h> 
#include <chrono>

#include "Strassen.hpp"
#include "algorithm.hpp"

using namespace std;  

  
int main() 
{ 
    int n = 260, k = 1;
    
    lld** X; 
    X = new lld*[k*n]; 
    for (int i = 0; i < k*n; i++) 
        X[i] = new lld[n]; 

    for (int i = 0; i < k*n; i++)
        for (int j=0;j<n;j++)
            X[i][j] = j+1;
  
    lld** Y; 
    Y = new lld*[n]; 
    for (int i = 0; i < n; i++) 
        Y[i] = new lld[k*n]; 
    
    for (int i = 0; i < k*n; i++)
        for (int j=0;j<n;j++)
            Y[i][j] = j+1;

    
    auto t1 = std::chrono::high_resolution_clock::now();
    lld** XY = Product(X, Y, k*n, n, k*n); 
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << duration << "\n";

    t1 = std::chrono::high_resolution_clock::now();
    XY = MatrixMultiply(X,Y,k*n,n,k*n);
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << duration << "\n";
    /*for (int i = 0; i < k*n; i++) { 
        for (int j = 0; j < k*n; j++) { 
            printf("%lld ", XY[i][j]); 
        } 
        printf("\n"); 
    } */
    return 0; 
} 