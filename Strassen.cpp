#include <bits/stdc++.h> 
/* Strassen's Algorithm for matrix multiplication 
   Complexity:    O(n^2.808) */
  
typedef long long lld;

using namespace std; 

//algoritmo tradicional para multiplicar matrices
lld** MatrixMultiply(lld** a, lld** b, int n, int l, int m) 
{ 
    lld** c = new lld*[n]; 
    for (int i = 0; i < n; i++) 
        c[i] = new lld[m]; 
  
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < m; j++) { 
            c[i][j] = 0; 
            for (int k = 0; k < l; k++) { 
                c[i][j] += a[i][k] * b[k][j]; 
            } 
        } 
    } 
    return c; 
} 

//primer algoritmo
//algoritmo de strassen como subrutina, guarda las matrices que se generan en memoria
lld** Strassen(lld** a, lld** b, int leaf_size, int n, int l, int m) 
{ 
    if (n <= leaf_size || l <= leaf_size || m <= leaf_size)
        return MatrixMultiply(a, b, n, l, m); 
  
    lld** c = new lld*[n]; 
    for (int i = 0; i < n; i++) 
        c[i] = new lld[m]; 
  
    int adjN = (n >> 1) + (n & 1); 
    int adjL = (l >> 1) + (l & 1); 
    int adjM = (m >> 1) + (m & 1); 
    
    //arreglo que guarda las submatrices de A
    lld**** As = new lld***[2]; 
    for (int x = 0; x < 2; x++) { 
        As[x] = new lld**[2]; 
        for (int y = 0; y < 2; y++) { 
            As[x][y] = new lld*[adjN]; 
            for (int i = 0; i < adjN; i++) { 
                As[x][y][i] = new lld[adjL]; 
                for (int j = 0; j < adjL; j++) { 
                    int I = i + (x & 1) * adjN; 
                    int J = j + (y & 1) * adjL; 
                    As[x][y][i][j] = (I < n && J < l) ? a[I][J] : 0; 
                } 
            } 
        } 
    } 
    
    //arreglo que guarda las submatrices de B
    lld**** Bs = new lld***[2]; 
    for (int x = 0; x < 2; x++) { 
        Bs[x] = new lld**[2]; 
        for (int y = 0; y < 2; y++) { 
            Bs[x][y] = new lld*[adjL]; 
            for (int i = 0; i < adjL; i++) { 
                Bs[x][y][i] = new lld[adjM]; 
                for (int j = 0; j < adjM; j++) { 
                    int I = i + (x & 1) * adjL; 
                    int J = j + (y & 1) * adjM; 
                    Bs[x][y][i][j] = (I < l && J < m) ? b[I][J] : 0; 
                } 
            } 
        } 
    } 
    
    //arreglo que guarda las sumas de Strassen
    lld*** s = new lld**[10]; 
    for (int i = 0; i < 10; i++) { 
        switch (i) { 
        case 0: 
            s[i] = new lld*[adjL]; 
            for (int j = 0; j < adjL; j++) { 
                s[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    s[i][j][k] = Bs[0][1][j][k] - Bs[1][1][j][k]; 
                } 
            } 
            break; 
        case 1: 
            s[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                s[i][j] = new lld[adjL]; 
                for (int k = 0; k < adjL; k++) { 
                    s[i][j][k] = As[0][0][j][k] + As[0][1][j][k]; 
                } 
            } 
            break; 
        case 2: 
            s[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                s[i][j] = new lld[adjL]; 
                for (int k = 0; k < adjL; k++) { 
                    s[i][j][k] = As[1][0][j][k] + As[1][1][j][k]; 
                } 
            } 
            break; 
        case 3: 
            s[i] = new lld*[adjL]; 
            for (int j = 0; j < adjL; j++) { 
                s[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    s[i][j][k] = Bs[1][0][j][k] - Bs[0][0][j][k]; 
                } 
            } 
            break; 
        case 4: 
            s[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                s[i][j] = new lld[adjL]; 
                for (int k = 0; k < adjL; k++) { 
                    s[i][j][k] = As[0][0][j][k] + As[1][1][j][k]; 
                } 
            } 
            break; 
        case 5: 
            s[i] = new lld*[adjL]; 
            for (int j = 0; j < adjL; j++) { 
                s[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    s[i][j][k] = Bs[0][0][j][k] + Bs[1][1][j][k]; 
                } 
            } 
            break; 
        case 6: 
            s[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                s[i][j] = new lld[adjL]; 
                for (int k = 0; k < adjL; k++) { 
                    s[i][j][k] = As[0][1][j][k] - As[1][1][j][k]; 
                } 
            } 
            break; 
        case 7: 
            s[i] = new lld*[adjL]; 
            for (int j = 0; j < adjL; j++) { 
                s[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    s[i][j][k] = Bs[1][0][j][k] + Bs[1][1][j][k]; 
                } 
            } 
            break; 
        case 8: 
            s[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                s[i][j] = new lld[adjL]; 
                for (int k = 0; k < adjL; k++) { 
                    s[i][j][k] = As[0][0][j][k] - As[1][0][j][k]; 
                } 
            } 
            break; 
        case 9: 
            s[i] = new lld*[adjL]; 
            for (int j = 0; j < adjL; j++) { 
                s[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    s[i][j][k] = Bs[0][0][j][k] + Bs[0][1][j][k]; 
                } 
            } 
            break; 
        } 
    } 
  
    //arreglo que guarda las multiplicaciones
    lld*** p = new lld**[7]; 
    p[0] = Strassen(As[0][0], s[0], leaf_size, adjN, adjL, adjM); 
    p[1] = Strassen(s[1], Bs[1][1], leaf_size, adjN, adjL, adjM); 
    p[2] = Strassen(s[2], Bs[0][0], leaf_size, adjN, adjL, adjM); 
    p[3] = Strassen(As[1][1], s[3], leaf_size, adjN, adjL, adjM); 
    p[4] = Strassen(s[4], s[5], leaf_size, adjN, adjL, adjM); 
    p[5] = Strassen(s[6], s[7], leaf_size, adjN, adjL, adjM); 
    p[6] = Strassen(s[8], s[9], leaf_size, adjN, adjL, adjM); 
  
    for (int i = 0; i < adjN; i++) { 
        for (int j = 0; j < adjM; j++) { 
            c[i][j] = p[4][i][j] + p[3][i][j] - p[1][i][j] + p[5][i][j]; 
            if (j + adjM < m) 
                c[i][j + adjM] = p[0][i][j] + p[1][i][j]; 
            if (i + adjN < n) 
                c[i + adjN][j] = p[2][i][j] + p[3][i][j]; 
            if (i + adjN < n && j + adjM < m) 
                c[i + adjN][j + adjM] = p[4][i][j] + p[0][i][j] - p[2][i][j] - p[6][i][j]; 
        } 
    } 
  
    for (int x = 0; x < 2; x++) { 
        for (int y = 0; y < 2; y++) { 
            for (int i = 0; i < adjN; i++) { 
                delete[] As[x][y][i]; 
            } 
            delete[] As[x][y]; 
        } 
        delete[] As[x]; 
    } 
    delete[] As; 
  
    for (int x = 0; x < 2; x++) { 
        for (int y = 0; y < 2; y++) { 
            for (int i = 0; i < adjL; i++) { 
                delete[] Bs[x][y][i]; 
            } 
            delete[] Bs[x][y]; 
        } 
        delete[] Bs[x]; 
    } 
    delete[] Bs; 
  
    for (int i = 0; i < 10; i++) { 
        switch (i) { 
        case 0: 
        case 3: 
        case 5: 
        case 7: 
        case 9: 
            for (int j = 0; j < adjL; j++) { 
                delete[] s[i][j]; 
            } 
            break; 
        case 1: 
        case 2: 
        case 4: 
        case 6: 
        case 8: 
            for (int j = 0; j < adjN; j++) { 
                delete[] s[i][j]; 
            } 
            break; 
        } 
        delete[] s[i]; 
    } 
    delete[] s; 
  
    for (int i = 0; i < 7; i++) { 
        for (int j = 0; j < (n >> 1); j++) { 
            delete[] p[i][j]; 
        } 
        delete[] p[i]; 
    } 
    delete[] p; 
  
    return c; 
} 

lld** Winograd(lld** a, lld** b, int leaf_size, int n, int l, int m) 
{ 
    if (n <= leaf_size || l <= leaf_size || m <= leaf_size)
        return MatrixMultiply(a, b, n, l, m); 
  
    lld** c = new lld*[n]; 
    for (int i = 0; i < n; i++) 
        c[i] = new lld[m]; 
  
    int adjN = (n >> 1) + (n & 1); 
    int adjL = (l >> 1) + (l & 1); 
    int adjM = (m >> 1) + (m & 1); 
  
    lld**** As = new lld***[2]; 
    for (int x = 0; x < 2; x++) { 
        As[x] = new lld**[2]; 
        for (int y = 0; y < 2; y++) { 
            As[x][y] = new lld*[adjN]; 
            for (int i = 0; i < adjN; i++) { 
                As[x][y][i] = new lld[adjL]; 
                for (int j = 0; j < adjL; j++) { 
                    int I = i + (x & 1) * adjN; 
                    int J = j + (y & 1) * adjL; 
                    As[x][y][i][j] = (I < n && J < l) ? a[I][J] : 0; 
                } 
            } 
        } 
    } 
  
    lld**** Bs = new lld***[2]; 
    for (int x = 0; x < 2; x++) { 
        Bs[x] = new lld**[2]; 
        for (int y = 0; y < 2; y++) { 
            Bs[x][y] = new lld*[adjL]; 
            for (int i = 0; i < adjL; i++) { 
                Bs[x][y][i] = new lld[adjM]; 
                for (int j = 0; j < adjM; j++) { 
                    int I = i + (x & 1) * adjL; 
                    int J = j + (y & 1) * adjM; 
                    Bs[x][y][i][j] = (I < l && J < m) ? b[I][J] : 0; 
                } 
            } 
        } 
    } 
  
    lld*** s = new lld**[4]; 
    for (int i = 0; i < 4; i++) { 
        switch (i) { 
        case 0: 
            s[i] = new lld*[adjL]; 
            for (int j = 0; j < adjL; j++) { 
                s[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    //S1 = A21 + A22
                    s[i][j][k] = As[1][0][j][k] + As[1][1][j][k]; 
                } 
            } 
            break; 
        case 1: 
            s[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                s[i][j] = new lld[adjL]; 
                for (int k = 0; k < adjL; k++) { 
                    //S2 = S1 - A11
                    s[i][j][k] = s[0][j][k] - As[0][0][j][k]; 
                } 
            } 
            break; 
        case 2: 
            s[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                s[i][j] = new lld[adjL]; 
                for (int k = 0; k < adjL; k++) { 
                    //S3 = A11 - A21
                    s[i][j][k] = As[0][0][j][k] - As[1][0][j][k]; 
                } 
            } 
            break; 
        case 3: 
            s[i] = new lld*[adjL]; 
            for (int j = 0; j < adjL; j++) { 
                s[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    //S4 = A12 - S2
                    s[i][j][k] = As[0][1][j][k] - s[1][j][k]; 
                } 
            } 
            break; 
        } 
    } 

    lld*** t = new lld**[4]; 
    for (int i = 0; i < 4; i++) { 
        switch (i) { 
        case 0: 
            t[i] = new lld*[adjL]; 
            for (int j = 0; j < adjL; j++) { 
                t[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    //T1 = B12 - B11
                    t[i][j][k] = Bs[0][1][j][k] - Bs[0][0][j][k]; 
                } 
            } 
            break; 
        case 1: 
            t[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                t[i][j] = new lld[adjL]; 
                for (int k = 0; k < adjL; k++) { 
                    //T2 = B22 - T1
                    t[1][j][k] = Bs[1][1][j][k] - t[0][j][k]; 
                } 
            } 
            break; 
        case 2: 
            t[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                t[i][j] = new lld[adjL]; 
                for (int k = 0; k < adjL; k++) { 
                    //T3 = B22 - B12
                    t[i][j][k] = Bs[1][1][j][k] - Bs[0][1][j][k]; 
                } 
            } 
            break; 
        case 3: 
            t[i] = new lld*[adjL]; 
            for (int j = 0; j < adjL; j++) { 
                t[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    //T4 = T2 - B21
                    t[i][j][k] = t[1][j][k] - Bs[1][0][j][k]; 
                } 
            } 
            break; 
        } 
    }
  
    lld*** p = new lld**[7]; 
    p[0] = Strassen(As[0][0], Bs[0][0], leaf_size, adjN, adjL, adjM); 
    p[1] = Strassen(As[0][1], Bs[1][0], leaf_size, adjN, adjL, adjM); 
    p[2] = Strassen(s[3], Bs[1][1], leaf_size, adjN, adjL, adjM); 
    p[3] = Strassen(As[1][1], t[3], leaf_size, adjN, adjL, adjM); 
    p[4] = Strassen(s[0], t[0], leaf_size, adjN, adjL, adjM); 
    p[5] = Strassen(s[1], t[1], leaf_size, adjN, adjL, adjM); 
    p[6] = Strassen(s[2], t[2], leaf_size, adjN, adjL, adjM); 

    lld*** u = new lld**[7]; 
    for (int i = 0; i < 7; i++) { 
        switch (i) { 
        case 0: 
            u[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                u[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    //U1 = P1 + P2
                    u[i][j][k] = p[0][j][k] + p[1][j][k]; 
                } 
            } 
            break; 
        case 1: 
            u[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                u[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    //U2 = P1 + P6
                    u[i][j][k] = p[0][j][k] + p[5][j][k]; 
                } 
            } 
            break; 
        case 2: 
            u[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                u[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) {  
                    //U3 = U2 + P7
                    u[i][j][k] = u[1][j][k] + p[6][j][k];
                } 
            } 
            break; 
        case 3: 
            u[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                u[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    //U4 = U2 + P5
                    u[i][j][k] = u[1][j][k] + p[4][j][k];
                } 
            } 
            break; 
        case 4: 
            u[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                u[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    //U5 = U4 + P3
                    u[i][j][k] = u[3][j][k] + p[2][j][k]; 
                } 
            } 
            break; 
        case 5: 
            u[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                u[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    //U6 = U3 - P4
                    u[i][j][k] = u[2][j][k] - p[3][j][k]; 
                } 
            } 
            break; 
        case 6: 
            u[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                u[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    //U7 = U3 + P5
                    u[i][j][k] = u[2][j][k] + p[4][j][k]; 
                } 
            } 
            break; 
        }
    }
    
    for (int i = 0; i < adjN; i++) { 
        for (int j = 0; j < adjM; j++) { 
            //C11 = U1
            //U1 = P1 + P2
            c[i][j] = u[0][i][j];
            //C12 = U5
            //U5 = U4 + P3
            if (j + adjM < m) 
                c[i][j + adjM] = u[4][i][j];
            //C21 = U6
            //U6 = U3 - P4 
            if (i + adjN < n) 
                c[i + adjN][j] = u[5][i][j]; 
            //C22 = U7
            //U7 = U3 + P5
            if (i + adjN < n && j + adjM < m) 
                c[i + adjN][j + adjM] = u[6][i][j]; 
        } 
    } 
  
    for (int x = 0; x < 2; x++) { 
        for (int y = 0; y < 2; y++) { 
            for (int i = 0; i < adjN; i++) { 
                delete[] As[x][y][i]; 
            } 
            delete[] As[x][y]; 
        } 
        delete[] As[x]; 
    } 
    delete[] As; 
  
    for (int x = 0; x < 2; x++) { 
        for (int y = 0; y < 2; y++) { 
            for (int i = 0; i < adjL; i++) { 
                delete[] Bs[x][y][i]; 
            } 
            delete[] Bs[x][y]; 
        } 
        delete[] Bs[x]; 
    } 
    delete[] Bs; 
  
    for (int i = 0; i < 4; i++) { 
        switch (i) { 
        case 0: 
        case 1: 
        case 2: 
        case 3: 
            for (int j = 0; j < adjL; j++) { 
                delete[] s[i][j]; 
            } 
            break; 
        } 
        delete[] s[i]; 
    } 
    delete[] s; 

    for (int i = 0; i < 4; i++) { 
        switch (i) { 
        case 0: 
        case 1: 
        case 2: 
        case 3: 
            for (int j = 0; j < adjL; j++) { 
                delete[] t[i][j]; 
            } 
            break; 
        } 
        delete[] t[i]; 
    } 
    delete[] t; 
  
    for (int i = 0; i < 7; i++) { 
        for (int j = 0; j < (n >> 1); j++) { 
            delete[] p[i][j]; 
        } 
        delete[] p[i]; 
    } 
    delete[] p; 
  
    return c; 
} 