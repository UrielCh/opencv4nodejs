#include "macros.h"
#include <opencv2/tracking.hpp>
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
#include <opencv2/tracking/tracking_legacy.hpp>
#endif
#include "Mat.h"
#include "Rect.h"

#ifndef __FF_TRACKER_H__
#define __FF_TRACKER_H__

class Tracker : public FF::ObjectWrapBase<Tracker>, public Napi::ObjectWrap {
public:
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  virtual cv::Ptr<cv::legacy::Tracker> getTracker() = 0;
#else
  virtual cv::Ptr<cv::Tracker> getTracker() = 0;
#endif

  static void Init(Napi::FunctionReference);

  static void Clear(const Napi::CallbackInfo& info);
  static void Init(const Napi::CallbackInfo& info);
  static void Update(const Napi::CallbackInfo& info);
  static void GetModel(const Napi::CallbackInfo& info);
};

#endif
