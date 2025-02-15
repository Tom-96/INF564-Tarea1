#include <cmath>
#include <algorithm> 
#include <bits/stdc++.h> 

#include "Strassen.hpp"
#include "write.hpp"

typedef long long lld;
using namespace std;  

//funcion que calcula la potencia  2^K mas cercana a n
unsigned int nextPowerOfTwo(int n) {
    return pow(2, int(ceil(log2(n))));
}

//funcion que calcula C = A B
//rellena con ceros A y B en caso de que no sean de la forma 2^nx2^n
lld** Product(lld** a, lld** b, int leaf_size, int n, int l, int m, string method) 
{
    unsigned int k1 = nextPowerOfTwo(n), k2 = nextPowerOfTwo(l);

    int k = std::max(k1,k2);
    
    lld** AFilled = new lld*[k];
    lld** BFilled = new lld*[k];
    lld** C = new lld*[n];

    for (int i = 0; i < k; i++) 
    {
        AFilled[i] = new lld[k];
        BFilled[i] = new lld[k];
        
        if (i < n)
            C[i] = new lld[n];

    }

        
    for(unsigned int i=0; i<k; i++) 
        for (unsigned int j=0; j<k; j++) 
            if (i < n && j < l)
                AFilled[i][j] = a[i][j];
            else
                AFilled[i][j] = 0;

    for(unsigned int i=0; i<k; i++) 
        for (unsigned int j=0; j<k; j++) 
            if (i < l && j < m)
                BFilled[i][j] = b[i][j];
            else
                BFilled[i][j] = 0;
    
    lld** CFilled;
    if (method == "Strassen")
        CFilled = Strassen(AFilled,BFilled,leaf_size,k,k,k);
    else
        CFilled = Winograd(AFilled,BFilled,leaf_size,k,k,k);

    for(unsigned int i=0; i<n; i++) 
        for (unsigned int j=0; j<m; j++) 
            C[i][j] = CFilled[i][j];

    return C;
}