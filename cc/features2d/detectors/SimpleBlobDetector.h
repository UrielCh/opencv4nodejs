#include "../FeatureDetector.h"
#include "NativeNodeUtils.h"
#include "macros.h"

#ifndef __FF_SIMPLEBLOBDETECTOR_H__
#define __FF_SIMPLEBLOBDETECTOR_H__

class SimpleBlobDetector : public FeatureDetector {
public:
  cv::Ptr<cv::SimpleBlobDetector> detector;

static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  static Napi::FunctionReference constructor;;

  cv::Ptr<cv::FeatureDetector> getDetector() {
    return detector;
  }
};

#endif