#pragma once

#include <c10/core/Allocator.h>
#include <c10/cuda/CUDAStream.h>

namespace at {
namespace cuda {

//
// A caching allocator for CUDA host allocations (pinned memory).
//
// This provides a drop-in replacement for THCudaHostAllocator, which re-uses
// freed pinned (page-locked) memory allocations. This avoids device
// synchronizations due to cudaFreeHost calls.
//
// To ensure correct behavior, THCCachingHostAllocator_recordEvent must be
// called anytime a pointer from this allocator is used in a cudaMemcpyAsync
// call between host and device, and passed the corresponding context from the
// allocation. This is currently invoked by at::native::copy_kernel_cuda.
//
// Note that this allocator does not split larger allocations into smaller
// blocks, unlike the caching device allocator.
//
TORCH_CUDA_CPP_API c10::Allocator* getZCHostAllocator();

// Records an event in the specified stream. The allocation corresponding to the
// input `ptr`/`ctx` will not be re-used until the event has occurred.
TORCH_CUDA_CPP_API bool
ZCHostAllocator_recordEvent(void* ptr, void* ctx, c10::cuda::CUDAStream stream);

// Releases cached pinned memory allocations via cudaHostFree
TORCH_CUDA_CPP_API void ZCHostAllocator_emptyCache();

inline TORCH_CUDA_CPP_API at::DataPtr HostAlloc_ZC(size_t size) {
  return getZCHostAllocator()->allocate(size);
}

} // namespace cuda
} // namespace at
