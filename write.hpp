#ifndef WRITE_H
#define WRITE_H


typedef long long lld;
using namespace std;

void writeMatrix(lld** matrix, int n, int m, string folder);

void writeTime(string method, float time_method, int k, int n, int leaf_size, string version);

#endif