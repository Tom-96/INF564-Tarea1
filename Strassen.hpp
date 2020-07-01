#ifndef STRASSEN_H
#define STRASSEN_H

typedef long long lld;

lld** MatrixMultiply(lld** a, lld** b, int n, int l, int m);

lld** Strassen(lld** a, lld** b, int leaf_size, int n, int l, int m);

#endif