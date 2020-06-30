#include <cmath>
#include <algorithm> 
#include <bits/stdc++.h> 

#include "Strassen.hpp"

//funcion que rellena con zeros si las matrices a y b no son  del tipo 2^n x 2^n
//luego de rellenar, aplica el algoritmo de Strassen para llevar a cabo la multiplicacion

typedef long long lld;
using namespace std;  

unsigned int nextPowerOfTwo(int n) {
    return pow(2, int(ceil(log2(n))));
}

lld** Product(lld** a, lld** b, int n, int l, int m) 
{
    unsigned int k1 = nextPowerOfTwo(n), k2 = nextPowerOfTwo(l);

    int k = std::max(k1,k2);
    
    lld** AFilled = new lld*[k];
    lld** BFilled = new lld*[k];

    for (int i = 0; i < k; i++) 
    {
        AFilled[i] = new lld[k];
        BFilled[i] = new lld[k];
    }
        
    for(unsigned int i=0; i<n; i++) 
        for (unsigned int j=0; j<l; j++) 
            AFilled[i][j] = a[i][j];

    for(unsigned int i=0; i<l; i++) 
        for (unsigned int j=0; j<m; j++) 
            BFilled[i][j] = b[i][j];

    return Strassen(AFilled,BFilled,n,l,m);
}