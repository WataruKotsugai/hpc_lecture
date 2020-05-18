#include <cstdio>
#include <cstdlib>
#include <cmath>

int main() {
  const int N = 8;
  double x[N], y[N], m[N], fx[N], fy[N];
  for(int i=0; i<N; i++) {
    x[i] = drand48();
    y[i] = drand48();
    m[i] = drand48();
    fx[i] = fy[i] = 0;
  }
  for(int i=0; i<N; i++) {
    __m256 xjvec = _mm256_load_ps(x);
    __m256 yjvec = _mm256_load_ps(y);
    __m256 mvec = _mm256_load_ps(m);
    __m256 xivec = _mm256_set1_ps(x[i]);
    __m256 yivec = _mm256_set1_ps(y[i]);
    __m256 rvec = _mm256_rsqrt_ps();
    __m256 fxvec = _mm256_mul_ps(-rxvec, mvec, rvec);
    __m256 fyvec = _mm256_mul_ps(-ryvec, mvec, rvec);
    
    _mm256_store_pf(fx[i], fxvec);
    _mm256_store_pf(fy[i], fyvec);
    printf("%d %g %g\n",i,fx[i],fy[i]);
  }
}
