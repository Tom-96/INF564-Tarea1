#include <bits/stdc++.h> 
#include <chrono>

typedef long long lld;
using namespace std;

void assign(lld** &a, lld** b, int an)
{

}

lld** MatrixMultiply(lld** &a, lld** &b, lld** &c, int an_s, int an_e, int am_s, int am_e, int bn_s, int bn_e, int bm_s, int bm_e, int cn_s, int cn_e, int cm_s, int cm_e) 
{ 
    int n = an_e - an_s, l = am_e - am_s, m = bm_e - bm_s;
    for (int i = 0; i <n; i++) { 
        for (int j = 0; j < m; j++) { 
            for (int k = 0; k < l; k++) { 
                c[cn_s+i][cm_s+j] += a[an_s+i][am_s+k] * b[bn_s+k][bm_s+j]; 
            } 
        } 
    } 
    return c; 
} 

lld** Strassen2(lld** &a, lld** &b, lld** &c, int leaf_size, int an_s, int an_e, int am_s, int am_e, int bn_s, int bn_e, int bm_s, int bm_e, int cn_s, int cn_e, int cm_s, int cm_e) 
{ 
    int n = an_e - an_s, l = am_e - am_s, m = bm_e - bm_s;

    if (n <= leaf_size || l <= leaf_size || m <= leaf_size)
        return MatrixMultiply(a, b, c, an_s, an_e, am_s, am_e, bn_s, bn_e, bm_s, bm_e, cn_s, cn_e, cm_s, cm_e); 
  
    int adjN = (n >> 1) + (n & 1); 
    int adjL = (l >> 1) + (l & 1); 
    int adjM = (m >> 1) + (m & 1); 

    for (int i=0;i < adjN;i++)
        for (int j=0;j<adjL;j++)
        {
            //S3 = A11 - A21, loc = C11
            //C11 = A11 - A21
            c[cn_s+i][cm_s+j] = a[an_s+i][am_s+j] - a[an_s+adjN+i][am_s+j];
        }
    
    for (int i=0;i < adjN;i++)
        for (int j=0;j<adjL;j++)
            //S1 = A21 + A22, loc = A21
            //A21 = A21 + A22
            a[an_s+adjN+i][am_s+j] = a[an_s+adjN+i][am_s+j] + a[an_s+adjN+i][am_s+adjL+j];
        

    for (int i=0;i < adjN;i++)
        for (int j=0;j<adjL;j++)
            //T1 = B12 - B11, loc = C22
            //C22 = B12 - B11
            c[an_s+adjN+i][am_s+adjM+j] = b[bn_s+i][bm_s+adjM+j] - b[bn_s+i][bm_s+j];
        
    
    for (int i=0;i < adjN;i++)
        for (int j=0;j<adjL;j++)
            //T3 = B22 - B12, loc = B12
            //B12 = B22 - B12
            b[bn_s+i][bm_s+adjL+j] = b[bn_s+adjL+i][bm_s+adjM+j] - b[bm_s+i][bm_s+adjM+j];
    
    //P7 = IP(S3T3), loc = C21
    //S3 -> loc = C11, T3 -> loc = B12
    //C21 = C11*B12
    Strassen2(c, b, c, leaf_size, cn_s, cn_s+adjN, cm_s, cm_s+adjM, bn_s, bn_s+adjL, bm_s+adjM, bm_e, cn_s+adjN, cn_e, cm_s, cm_s+adjM);

    for (int i=0;i < adjN;i++)
        for (int j=0;j<adjL;j++)
            //S2 = S1 - A11, loc = C12
            //S1 -> loc = A21
            //C12 = A21 - A11
            c[cn_s+i][cm_s+adjM+j] = a[an_s+adjN+i][am_s+j] - a[an_s+i][am_s+j];

    //P1 = IP(A11B11), loc = C11
    Strassen2(a, b, c, leaf_size, an_s, an_s+adjN, am_s, am_s+adjM, bn_s, bn_s+adjL, bm_s, bm_s+adjL, cn_s, cn_s+adjN, cm_s, cm_s+adjM);


    for (int i=0;i < adjN;i++)
        for (int j=0;j<adjL;j++)
            //T2 = B22 - T1, loc = B11
            //T1 -> loc = C22
            //B11 = B22 - C22
            b[cn_s+i][cm_s+j] = b[bn_s+adjL+i][bm_s+adjM+j] - c[cn_s+adjN+i][cm_s+adjM+j];
    
    //P5 = IP(S1T1), loc = A11
    //S1 -> loc = A21
    //T1 -> loc = C22
    //A11 = A21*C22
    Strassen2(a, c, a, leaf_size, an_s+adjN, an_e, am_s, am_s+adjM, cn_s+adjN, cn_e, cm_s+adjM, cm_e, an_s, an_s+adjN, am_s, am_s+adjM);


    for (int i=0;i < adjN;i++)
        for (int j=0;j<adjL;j++)
            //T4 = T2 - B21, loc = C22
            //T2 -> loc = B11
            //C22 = B11 - B21
            c[cn_s+adjN+i][cm_s+adjM+j] = b[bn_s+i][bm_s+j] - b[bn_s+adjL+i][bm_s+j];
    
    //P4 = IP(A22T4), loc = A21
    //T4 -> loc = C22
    //A21 = A22*C22
    Strassen2(a, c, a, leaf_size, an_s+adjN, an_e, am_s+adjL, am_e, cn_s+adjN, cn_e, cm_s+adjM, cm_e, an_s+adjN, an_e, am_s, am_s+adjL);

    for (int i=0;i < adjN;i++)
        for (int j=0;j<adjL;j++)
            //S4 = A12 - S2, loc = A22
            //S2 -> loc = C12
            //A22 = A12 - C12
            a[an_s+adjN+i][am_s+adjL+j] = a[an_s+i][am_s+adjL+j] - c[cn_s+i][cm_s+adjM+j];
        

    //P6 = IP(S2T2), loc = C22
    //S2 -> loc = C12
    //T2 -> loc = B11
    //C22 = C12*B11
    Strassen2(c, b, c, leaf_size, cn_s, cn_s+adjN, cm_s+adjM, cm_e, bn_s, bn_s+adjL, bm_s, bm_s+adjM, cn_s, cn_s+adjN, cm_s, cm_s+adjM);

    //U2 = P1 + P6, loc = C22
    //P1 -> loc = C11
    //P6 -> loc = C22
    //C22 = C11 + C22

    for (int i=0;i < adjN;i++)
        for (int j=0;j<adjL;j++)
            c[cn_s+adjN+i][cm_s+adjM+j] = c[cn_s+i][cm_s+j] + c[cn_s+adjN+i][cm_s+adjM+j];

    //P2 = IP(A12B21), loc = C12
    //C12 = A12*B21
    Strassen2(a, b, c, leaf_size, an_s, an_s+adjN, am_s+adjL, am_e, bn_s+adjL, bn_e, bm_s, bm_s+adjM, cn_s, cn_s+adjN, cm_s+adjM, cm_e);

    //U1 = P1 + P2, loc = C11
    //P1 -> loc = C11
    //P2 -> loc = C12
    //C11 = C11 + C12
    for (int i=0;i < adjN;i++)
        for (int j=0;j<adjL;j++)
            c[cn_s+i][cm_s+j] = c[cn_s+i][cm_s+j] + c[cn_s+i][cm_s+adjM+j];
    
    //U4 = U2 + P5, loc = C12
    //U2 -> loc = C22
    //P5 -> loc = A11
    //C12 = C22 + A11
    for (int i=0;i < adjN;i++)
        for (int j=0;j<adjL;j++)
            c[cn_s+i][cm_s+adjM+j] = c[cn_s+adjN+i][cm_s+adjM+j] + a[an_s+i][am_s+j];

    //U3 = U2 + P7, loc = C22
    //U2 -> loc = C22
    //P7 -> loc = C21
    //C22 = C22 + C21
    for (int i=0;i < adjN;i++)
        for (int j=0;j<adjL;j++)
            c[cn_s+adjN+i][cm_s+adjM+j] = c[cn_s+adjN+i][cm_s+adjM+j] + c[cn_s+adjN+i][cm_s+j];

    //U6 = U3 - P4, loc = C21
    //U3 -> loc = C22
    //P4 -> loc = A21
    for (int i=0;i < adjN;i++)
        for (int j=0;j<adjL;j++)
            c[cn_s+adjN+i][cm_s+j] = c[cn_s+adjN+i][cm_s+adjM+j] - a[an_s+adjN+i][am_s+j];

    //U7 = U3 + P5, loc = C22
    //U3 -> loc = C22
    //P5 -> loc = A11
    for (int i=0;i < adjN;i++)
        for (int j=0;j<adjL;j++)
            c[cn_s+adjN+i][cm_s+adjM+j] = c[cn_s+adjN+i][cm_s+adjM+j] + a[an_s+i][am_s+j];

    //P3 = IP(S4B22), loc = A12
    //S4 -> loc = A22
    Strassen2(a, b, a, leaf_size, an_s+adjN, an_e, am_s+adjL, am_e, bn_s+adjL, bn_e, bm_s+adjM, bm_e, an_s, an_s+adjN, am_s+adjL, am_e);

    //U5 = U4 + P3, loc = C12
    //U4 -> loc = C12
    //P3 -> loc = A12
    for (int i=0;i < adjN;i++)
        for (int j=0;j<adjL;j++)
            c[cn_s+i][cm_s+adjM+j] = c[cn_s+i][cm_s+adjM+j] + a[an_s+i][am_s+adjL+j];

    return c; 
} 

int main(int argc, char** argv)
{
    int k=2;
    lld** A = new lld*[2];
    lld** B = new lld*[2];
    lld** C = new lld*[2];

    for (int i = 0; i < 2; i++) 
    {
        A[i] = new lld[2];
        B[i] = new lld[2];
        C[i] = new lld[2];
    }
        
    for (int i=0;i < 2;i++)
        for (int j=0;j<2;j++)
        {
            A[i][j] = 1;
            B[i][j] = 1;
            C[i][j] = 0;
        }
    auto t1 = std::chrono::high_resolution_clock::now();

    Strassen2(A,B,C,1,0,k,0,k,0,k,0,k,0,k,0,k);
    //MatrixMultiply(A,B,C,0,k,0,k,0,k,0,k,0,k,0,k);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_strassen = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    cout << duration_strassen << endl;
    

    for (int i=0;i < k;i++)
        for (int j=0;j<k;j++)
        {
            cout << C[i][j] << endl;
        }
    return 1;  
}