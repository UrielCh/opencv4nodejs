#include "BackgroundSubtractor.h"
#include "CatchCvExceptionWorker.h"
#include "macros.h"

#ifndef __FF_BACKGROUNDSUBTRACTORMOG2_H__
#define __FF_BACKGROUNDSUBTRACTORMOG2_H__

class BackgroundSubtractorMOG2 : public BackgroundSubtractor, public FF::ObjectWrapTemplate<BackgroundSubtractorMOG2, cv::Ptr<cv::BackgroundSubtractorMOG2>> {
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "BackgroundSubtractorMOG2";
  }

  cv::Ptr<cv::BackgroundSubtractor> getSubtractor() {
    return self;
  }

  FF_GETTER_CUSTOM(history, FF::IntConverter, self->getHistory());
  FF_GETTER_CUSTOM(varThreshold, FF::DoubleConverter, self->getVarThreshold());
  FF_GETTER_CUSTOM(detectShadows, FF::BoolConverter, self->getDetectShadows());

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  struct NewWorker : CatchCvExceptionWorker {
  public:
    uint history = 500;
    double varThreshold = 16;
    bool detectShadows = true;

    bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
      return (
          FF::UintConverter::optArg(0, &history, info) || FF::DoubleConverter::optArg(1, &varThreshold, info) || FF::BoolConverter::optArg(2, &detectShadows, info));
    }

    bool hasOptArgsObject(const Napi::CallbackInfo& info) {
      return FF::isArgObject(info, 0);
    }

    bool unwrapOptionalArgsFromOpts(const Napi::CallbackInfo& info) {
      Napi::Object opts = info[0].As<Napi::Object>();
      return (
          FF::UintConverter::optProp(&history, "history", opts) || FF::DoubleConverter::optProp(&varThreshold, "varThreshold", opts) || FF::BoolConverter::optProp(&detectShadows, "detectShadows", opts));
    }

    std::string executeCatchCvExceptionWorker() {
      return "";
    }
  };
};

#endif