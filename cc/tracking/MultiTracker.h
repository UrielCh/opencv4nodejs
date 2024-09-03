#include "macros.h"
#include <opencv2/tracking.hpp>
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
#include <opencv2/tracking/tracking_legacy.hpp>
#endif
#include "Mat.h"
#include "Rect.h"

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

#ifndef __FF_MULTITRACKER_H__
#define __FF_MULTITRACKER_H__

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
class MultiTracker : public FF::ObjectWrap<MultiTracker, cv::Ptr<cv::legacy::MultiTracker>> {
#else
class MultiTracker : public FF::ObjectWrap<MultiTracker, cv::Ptr<cv::MultiTracker>> {
#endif
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "MultiTracker";
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static Napi::Value New(const Napi::CallbackInfo& info);
  static Napi::Value AddMIL(const Napi::CallbackInfo& info);
  static Napi::Value AddBOOSTING(const Napi::CallbackInfo& info);
  static Napi::Value AddMEDIANFLOW(const Napi::CallbackInfo& info);
  static Napi::Value AddTLD(const Napi::CallbackInfo& info);
  static Napi::Value AddKCF(const Napi::CallbackInfo& info);
  static Napi::Value AddMOSSE(const Napi::CallbackInfo& info);
  static Napi::Value AddCSRT(const Napi::CallbackInfo& info);
  static Napi::Value Update(const Napi::CallbackInfo& info);
};

#endif

#endif
