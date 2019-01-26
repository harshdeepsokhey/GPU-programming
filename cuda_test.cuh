#ifndef _CUDA_TEST_HPP_
#define _CUDA_TEST_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#ifdef __CUDACC__
#define CUDA_CALLABLE __host__ __device__
#else
#define CUDA_CALLABLE
#endif

void cudaAddVectorKernel(const float *a, const float *b, float *c, const uint size);

#endif