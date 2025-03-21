#pragma once
 
 #include <c10/core/impl/DeviceGuardImplInterface.h>
 #include <c10/macros/Macros.h>
 
 namespace at {
 namespace detail {
 
 struct ZCGuardImpl final : public c10::impl::DeviceGuardImplInterface {
   ZCGuardImpl() {}
   DeviceType type() const override {
     return DeviceType::ZC;
   }
   Device exchangeDevice(Device) const override {
     // no-op
     return Device(DeviceType::ZC);
 
   }
   Device getDevice() const override {
     return Device(DeviceType::ZC);
   }
   void setDevice(Device) const override {
     // no-op
   }
   void uncheckedSetDevice(Device d) const noexcept override {
     // no-op
   }
   Stream getStream(Device d) const noexcept override {
     // no-op
     return Stream(Stream::DEFAULT, Device(DeviceType::ZC));
   }
   // NB: These do NOT set the current device
   Stream exchangeStream(Stream s) const noexcept override {
     // no-op
     return Stream(Stream::DEFAULT, Device(DeviceType::ZC));
   }
   DeviceIndex deviceCount() const noexcept override {
     return 1;
   }
 
   // Event-related functions
   void record(void** event,
     const Stream& stream,
     const DeviceIndex device_index,
     const EventFlag flag) const override {
     TORCH_CHECK(false, "ZC backend doesn't support events.");
   }
   void block(
     void* event,
     const Stream& stream) const override {
     TORCH_CHECK(false, "ZC backend doesn't support events.")
   }
   bool queryEvent(void* event) const override {
     TORCH_CHECK(false, "ZC backend doesn't support events.")
   }
   void destroyEvent(
     void* event,
     const DeviceIndex device_index) const noexcept override { }
 };
 
 }} // namespace at::detail