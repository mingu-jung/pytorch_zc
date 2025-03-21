#include <ATen/cuda/ZeroCopyAllocator.h>
#include <ATen/Context.h>
#include <ATen/Config.h>
#include <ATen/TensorUtils.h>
#include <c10/core/Storage.h>
#include <ATen/ATen.h>
#include <ATen/CPUFunctions.h>

namespace at {

namespace native {

bool is_pinned_zc(const Tensor& self, c10::optional<Device> device) {
  TORCH_INTERNAL_ASSERT_DEBUG_ONLY(!device.has_value() || device->is_zc());
  // TODO: unhook this
  return detail::getCUDAHooks().isPinnedPtr(self.storage().data());
}

Tensor _pin_memory_zc(const Tensor& self, c10::optional<Device> device) {
  TORCH_INTERNAL_ASSERT_DEBUG_ONLY(!device.has_value() || device->is_zc());
  auto* allocator = at::cuda::getZeroCopyAllocator();
  auto storage = Storage(
      Storage::use_byte_size_t(),
      detail::computeStorageNbytes(
          self.sizes(), self.strides(), self.dtype().itemsize()),
      allocator,
      /*resizable=*/false);
  auto tensor = at::cpu::empty({0}, self.options()).set_(storage, 0, self.sizes(), self.strides());
  tensor.copy_(self);
  return tensor;
}


} // namespace native
} // namespace at
