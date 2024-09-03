#include "CatchCvExceptionWorker.h"
#include "Mat.h"
#include "NativeNodeUtils.h"
#include "Rect.h"
#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>

#ifndef __FF_CASCADECLASSIFIER_H__
#define __FF_CASCADECLASSIFIER_H__

class CascadeClassifier : public FF::ObjectWrap<CascadeClassifier, cv::CascadeClassifier> {
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "CascadeClassifier";
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static void New(const Napi::CallbackInfo& info);
  static void DetectMultiScale(const Napi::CallbackInfo& info);
  static void DetectMultiScaleAsync(const Napi::CallbackInfo& info);
  static void DetectMultiScaleGpu(const Napi::CallbackInfo& info);
  static void DetectMultiScaleWithRejectLevels(const Napi::CallbackInfo& info);
  static void DetectMultiScaleWithRejectLevelsAsync(const Napi::CallbackInfo& info);
  static void DetectMultiScaleWithRejectLevelsGpu(const Napi::CallbackInfo& info);
};

#endif