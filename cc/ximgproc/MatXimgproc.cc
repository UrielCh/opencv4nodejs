#include "opencv_modules.h"

#ifdef HAVE_OPENCV_XIMGPROC

#include "MatXimgproc.h"
#include "MatXimgprocBindings.h"

void MatXimgproc::Init(Napi::FunctionReference ctor) {
  InstanceMethod("guidedFilter", &GuidedFilter),
  InstanceMethod("guidedFilterAsync", &GuidedFilterAsync),
};

void MatXimgproc::GuidedFilter(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatXimgprocBindings::GuidedFilterWorker>(Mat::unwrapSelf(info)),
      "Mat::GuidedFilter",
      info);
}

void MatXimgproc::GuidedFilterAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatXimgprocBindings::GuidedFilterWorker>(Mat::unwrapSelf(info)),
      "Mat::GuidedFilterAsync",
      info);
}

#endif // HAVE_OPENCV_XIMGPROC
