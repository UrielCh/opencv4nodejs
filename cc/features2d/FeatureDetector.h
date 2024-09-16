#include "CatchCvExceptionWorker.h"
#include "KeyPoint.h"
#include "Mat.h"
#include "NativeNodeUtils.h"
#include "macros.h"
#include <napi.h>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>

#ifndef FF_FEATUREDETECTOR_H_
#define FF_FEATUREDETECTOR_H_

class FeatureDetector : public FF::ObjectWrapBase<FeatureDetector>, public Napi::ObjectWrap<FeatureDetector> {
public:
  virtual cv::Ptr<cv::FeatureDetector> getDetector() = 0;

  //  static Napi::Object Init(Napi::FunctionReference);
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static Napi::Value Detect(const Napi::CallbackInfo& info);
  static Napi::Value DetectAsync(const Napi::CallbackInfo& info);
  static Napi::Value Compute(const Napi::CallbackInfo& info);
  static Napi::Value ComputeAsync(const Napi::CallbackInfo& info);
};

#endif