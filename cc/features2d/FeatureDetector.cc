#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "FeatureDetector.h"
#include "FeatureDetectorBindings.h"

void FeatureDetector::Init(Napi::FunctionReference ctor) {
  Napi::SetPrototypeMethod(ctor, "detect", FeatureDetector::Detect);
  Napi::SetPrototypeMethod(ctor, "compute", FeatureDetector::Compute);
  Napi::SetPrototypeMethod(ctor, "detectAsync", FeatureDetector::DetectAsync);
  Napi::SetPrototypeMethod(ctor, "computeAsync", FeatureDetector::ComputeAsync);
};

void FeatureDetector::Detect(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<FeatureDetectorBindings::DetectWorker>(FeatureDetector::unwrapThis(info)->getDetector()),
      "FeatureDetector::Detect",
      info);
}

void FeatureDetector::DetectAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<FeatureDetectorBindings::DetectWorker>(FeatureDetector::unwrapThis(info)->getDetector()),
      "FeatureDetector::DetectAsync",
      info);
}

void FeatureDetector::Compute(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<FeatureDetectorBindings::ComputeWorker>(FeatureDetector::unwrapThis(info)->getDetector()),
      "FeatureDetector::Compute",
      info);
}

void FeatureDetector::ComputeAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<FeatureDetectorBindings::ComputeWorker>(FeatureDetector::unwrapThis(info)->getDetector()),
      "FeatureDetector::ComputeAsync",
      info);
}

#endif
