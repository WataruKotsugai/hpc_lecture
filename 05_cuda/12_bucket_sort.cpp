#include <cstdio>
#include <cstdlib>
#include <vector>

__global__ void bucket_initizalize(int *bucket){
  int i = threadIdx.x;
  bucket[i] = 0;
}

__global__ void bucket_add(int *key, int *bucket){
  int i = threadIdx.x;
  int num = key[i];
  atomicAdd(&bucket[num], 1);
}

__global__ void bucket_sort(int *key, int num, int length){
  int i = threadIdx.x;
  key[i+length] = num;
}

int main() {
  int n = 50;
  int range = 5;
  int *key;
  cudaMallocManaged(&key, n*sizeof(int));
  for (int i=0; i<n; i++) {
    key[i] = rand() % range;
    printf("%d ",key[i]);
  }
  printf("\n");

  int *bucket;
  cudaMallocManaged(&bucket, range*sizeof(int));
  bucket_initialize<<<1, range>>>(bucket);
  cudaDeviceSynchronize();
  
  bucket_add<<<1, n>>>(key, bucket);
  cudaDeviceSynchronize();
  
  int length = 0;
  for (int i=0; i<range; i++) {
    bucket_sort<<<1, bucket[i]>>>(key, i, length);
    lenght += bucket[i];
  }
  cudaDeviceSynchronize();

  for (int i=0; i<n; i++) {
    printf("%d ",key[i]);
  }
  printf("\n");
}
