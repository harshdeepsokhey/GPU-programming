/* Example 1: Add 2 vectors*/

#include "cuda_test.cuh"

__global__
void cudaAddVectorKernel(const float *a, const float *b, float *c, const uint size){
    uint idx = blockIdx.x * blockDim.x + threadIdx.x;

    while(idx < size){
        c[idx] = a[idx]+ b[idx]
        idx += blockDim.x * gridDim.x;
    }
}

void cudaCallAddVectorKernel( const uint block_count, const uint per_block_thread_count, const float *a, const float *b, float *c, const uint size){
    cudaAddVectorKernel<<<block_count, per_block_thread_count>>>(a,b,c,size);
}

