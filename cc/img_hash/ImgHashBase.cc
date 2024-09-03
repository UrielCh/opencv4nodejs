#include "opencv_modules.h"

#ifdef HAVE_OPENCV_IMG_HASH

#include "ImgHashBase.h"
#include "ImgHashBaseBindings.h"

void ImgHashBase::Init(Napi::FunctionReference ctor) {
  InstanceMethod("compare", &Compare),
  InstanceMethod("compareAsync", &CompareAsync),
  InstanceMethod("compute", &Compute),
  InstanceMethod("computeAsync", &ComputeAsync),
};

void ImgHashBase::Compare(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<ImgHashBaseBindings::CompareWorker>(ImgHashBase::unwrapThis(info)->getImgHashBase()),
      "ImgHashBase::Compare",
      info);
}

void ImgHashBase::CompareAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<ImgHashBaseBindings::CompareWorker>(ImgHashBase::unwrapThis(info)->getImgHashBase()),
      "ImgHashBase::CompareAsync",
      info);
}

void ImgHashBase::Compute(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<ImgHashBaseBindings::ComputeWorker>(ImgHashBase::unwrapThis(info)->getImgHashBase()),
      "ImgHashBase::Compute",
      info);
}

void ImgHashBase::ComputeAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<ImgHashBaseBindings::ComputeWorker>(ImgHashBase::unwrapThis(info)->getImgHashBase()),
      "ImgHashBase::ComputeAsync",
      info);
}

#endif
