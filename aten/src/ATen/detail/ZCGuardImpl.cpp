#include <ATen/detail/ZCGuardImpl.h>

namespace at {
namespace detail {

// constexpr DeviceType ZCGuardImpl::static_type;

C10_REGISTER_GUARD_IMPL(ZC, ZCGuardImpl);

} // namespace at
} // namespace detail
