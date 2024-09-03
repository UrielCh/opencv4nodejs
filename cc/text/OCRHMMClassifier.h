#include "CatchCvExceptionWorker.h"
#include "Mat.h"
#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/text.hpp>

#ifndef __FF_OCRHMMCLASSIFIER_H__
#define __FF_OCRHMMCLASSIFIER_H__

class OCRHMMClassifier : public FF::ObjectWrap<OCRHMMClassifier, cv::Ptr<cv::text::OCRHMMDecoder::ClassifierCallback>> {
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "OCRHMMClassifier";
  }

  static Napi::Value New(const Napi::CallbackInfo& info) {
    OCRHMMClassifier* self = new OCRHMMClassifier();
    self->Wrap(info.Holder());
    return info.Holder();
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static void Eval(const Napi::CallbackInfo& info);
  static void EvalAsync(const Napi::CallbackInfo& info);
};

#endif