#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D
#include "FeatureDetector.h"
#include "FeatureDetectorBindings.h"

Napi::Object FeatureDetector::Init(Napi::Env env, Napi::Object exports) {
  Napi::Function ctor = DefineClass(env, "FeatureDetector", {// InstanceMethod("detect", &FeatureDetector::Detect),
                                                             InstanceMethod<&FeatureDetector::Detect>("detect"), InstanceMethod("compute", &FeatureDetector::Compute), InstanceMethod("detectAsync", &FeatureDetector::DetectAsync), InstanceMethod("computeAsync", &FeatureDetector::ComputeAsync)});

  exports.Set("FeatureDetector", ctor);
  return exports;
}

Napi::Value FeatureDetector::Detect(const Napi::CallbackInfo& info) {
  return FF::executeSyncBinding(
      std::make_shared<FeatureDetectorBindings::DetectWorker>(FeatureDetector::unwrapThis(info)->getDetector()),
      "FeatureDetector::Detect",
      info);
}

Napi::Value FeatureDetector::DetectAsync(const Napi::CallbackInfo& info) {
  return FF::executeAsyncBinding(
      std::make_shared<FeatureDetectorBindings::DetectWorker>(FeatureDetector::unwrapThis(info)->getDetector()),
      "FeatureDetector::DetectAsync",
      info);
}

Napi::Value FeatureDetector::Compute(const Napi::CallbackInfo& info) {
  return FF::executeSyncBinding(
      std::make_shared<FeatureDetectorBindings::ComputeWorker>(FeatureDetector::unwrapThis(info)->getDetector()),
      "FeatureDetector::Compute",
      info);
}

Napi::Value FeatureDetector::ComputeAsync(const Napi::CallbackInfo& info) {
  return FF::executeAsyncBinding(
      std::make_shared<FeatureDetectorBindings::ComputeWorker>(FeatureDetector::unwrapThis(info)->getDetector()),
      "FeatureDetector::ComputeAsync",
      info);
}

#endif
