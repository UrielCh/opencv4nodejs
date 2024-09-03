#include "CatchCvExceptionWorker.h"
#include "Mat.h"
#include "NativeNodeUtils.h"
#include "OCRHMMClassifier.h"
#include "Rect.h"
#include "macros.h"
#include <opencv2/text.hpp>

#ifndef __FF_OCRHMMDECODER_H__
#define __FF_OCRHMMDECODER_H__

class OCRHMMDecoder : public FF::ObjectWrap<OCRHMMDecoder, cv::Ptr<cv::text::OCRHMMDecoder>> {
public:
  static Napi::FunctionReference constructor;;

  static const char* getClassName() {
    return "OCRHMMDecoder";
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static void New(const Napi::CallbackInfo& info);
  static void Run(const Napi::CallbackInfo& info);
  static void RunAsync(const Napi::CallbackInfo& info);
  static void RunWithInfo(const Napi::CallbackInfo& info);
  static void RunWithInfoAsync(const Napi::CallbackInfo& info);
};

#endif