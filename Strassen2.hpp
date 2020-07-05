#ifndef STRASSEN2_H
#define STRASSEN2_H

typedef long long lld;

lld** MatrixMultiply(lld** &a, lld** &b, lld** &c, int an_s, int an_e, int am_s, int am_e, int bn_s, int bn_e, int bm_s, int bm_e, int cn_s, int cn_e, int cm_s, int cm_e);

lld** Strassen(lld** &a, lld** &b, lld** &c, int leaf_size, int an_s, int an_e, int am_s, int am_e, int bn_s, int bn_e, int bm_s, int bm_e, int cn_s, int cn_e, int cm_s, int cm_e);

#endif