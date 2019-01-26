#include "test.hpp"

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <cmath>
#include <cuda_runtime.h>
#include "cuda_test.cuh"

using namespace std;


int main(int argc, char **argv){

    // block_size, max_block_count
    const uint PER_BLOCK_THREAD_COUNT = 1024;
    const uint MAX_BLOCK_COUNT = 65535;

    // setup host memory
    const uint ARRAY_SIZE = 10000000
    float *a = new float[ARRAY_SIZE];
    float *b = new float[ARRAY_SIZE];
    float *c = new float[ARRAY_SIZE];

    // initialize a,b;
    for(uint i=0; i < ARRAY_SIZE; i++){
        a[i] = i;
        b[i] = ARRAY_SIZE - i;
    }

    // setup device memory
    float *dev_a;
    float *dev_b;
    float *dev_c;

    cudaMalloc((void**)&dev_a, ARRAY_SIZE * sizeof(float));
    cudaMalloc((void**)&dev_b, ARRAY_SIZE * sizeof(float));
    cudaMalloc((void**)&dev_c, ARRAY_SIZE * sizeof(float));

    // copy a , b from host -> device

    cudaMemcpy(dev_a, a, ARRAY_SIZE * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, ARRAY_SIZE * sizeof(float), cudaMemcpyHostToDevice);

    // call the kernel to add the 2 arrays into dev_c
    uint block_count = min(MAX_BLOCK_COUNT, (uint)(ceil(ARRAY_SIZE/(float)(PER_BLOCK_THREAD_COUNT))))

    cudaCallAddVectorKernel(block_count,
                            PER_BLOCK_THREAD_COUNT,
                            dev_a,
                            dev_b,
                            dev_c,
                            ARRAY_SIZE);

    // copy dev_c back to c device->host
    cudaMemcpy(c, dev_c, ARRAY_SIZE * sizeof(float), cudaMemcpyDeviceToHost);

    for(uint i =0; i < ARRAY_SIZE; i++){
        assert(c[i] == ARRAY_SIZE)
    }

    // free memory from HOST
    delete[] a;
    delete[] b;
    delete[] c;

    // free memory from DEVICE
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);

    return 0;

}
