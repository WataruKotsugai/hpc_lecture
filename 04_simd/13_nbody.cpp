#include <cstdio>
#include <cstdlib>
#include <cmath>

int main() {
  const int N = 8;
  float x[N], y[N], m[N], fx[N], fy[N];
  for(int i=0; i<N; i++) {
    x[i] = drand48();
    y[i] = drand48();
    m[i] = drand48();
    fx[i] = fy[i] = 0;
  }
  for(int i=0; i<N; i++) {
    __m256 xivec = _mm256_set1_ps(x[i]);
    __m256 yivec = _mm256_set1_ps(y[i]);
    __m256 xjvec = _mm256_load_ps(x);
    __m256 yjvec = _mm256_load_ps(y);
    __m256 rxvec = _mm256_sub_ps(xivec, xjvec); // rx = xi - xj
    __m256 ryvec = _mm256_sub_ps(yivec, yjvec); // ry = yi - yj
    __m256 r2vec = _mm256_add_ps(_mm256_mul_ps(rxvec, rxvec), _mm256_mul_ps(ryvec, ryvec)); // r2 = rx * rx + ry * ry
    
    __m256 zero = _mm256_setzero_ps();
    __m256 one = _mm256_set1_ps(1);
    __m256 mask = _mm256_cmp_ps(r2vec, zero, _CMP_GT_OQ);
    
    r2vec = _mm256_blendv_ps(one, r2vec, mask); // replace r2vec's element 0 with 1
    __m256 rvec = _mm256_rsqrt_ps(r2vec); // rvec = 1 / sqrt(r2)
    __m256 mvec = _mm256_load_ps(m);
    mvec = _mm256_blendv_ps(zero, mvec, mask);
    
    __m256 fxvec = _mm256_mul_ps(-rxvec, _mm256_mul_ps(mvec, _mm256_mul_ps(rvec, _mm256_mul_ps(rvec, rvec))));
    __m256 fyvec = _mm256_mul_ps(-ryvec, _mm256_mul_ps(mvec, _mm256_mul_ps(rvec, _mm256_mul_ps(rvec, rvec))));
    float fxj[N], fyj[N];
    _mm256_store_ps(fxj, fxvec);
    _mm256_store_ps(fyj, fyvec);
    for(int j=0; j<N; j++){
      fx[i] += fxj[j];
      fy[i] += fyj[j];
    }
    printf("%d %g %g\n",i,fx[i],fy[i]);
  }
}
