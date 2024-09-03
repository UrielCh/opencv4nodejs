#include "CatchCvExceptionWorker.h"
#include "KeyPoint.h"
#include "Mat.h"
#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>

#ifndef FF_FEATUREDETECTOR_H_
#define FF_FEATUREDETECTOR_H_

class FeatureDetector : public FF::ObjectWrapBase<FeatureDetector>, public Napi::ObjectWrap {
public:
  virtual cv::Ptr<cv::FeatureDetector> getDetector() = 0;

  static void Init(Napi::FunctionReference);

  static void Detect(const Napi::CallbackInfo& info);
  static void DetectAsync(const Napi::CallbackInfo& info);
  static void Compute(const Napi::CallbackInfo& info);
  static void ComputeAsync(const Napi::CallbackInfo& info);
};

#endif