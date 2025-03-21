#pragma once

#include <c10/core/Allocator.h>
#include <ATen/cuda/ZCHostAllocator.h>

namespace at { namespace cuda {

inline TORCH_CUDA_CPP_API at::Allocator* getZeroCopyAllocator() {
  return getZCHostAllocator();
}
}} // namespace at::cuda