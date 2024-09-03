#include "CatchCvExceptionWorker.h"
#include "KeyPoint.h"
#include "Mat.h"
#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>

#ifndef __FF_BFMATCHER_H__
#define __FF_BFMATCHER_H__

class BFMatcher : public FF::ObjectWrap<BFMatcher, cv::BFMatcher> {
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "BFMatcher";
  }

  int normType;
  bool crossCheck;

  FF_GETTER_CUSTOM(normType, FF::IntConverter, normType);
  FF_GETTER_CUSTOM(crossCheck, FF::BoolConverter, crossCheck);

  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static void New(const Napi::CallbackInfo& info);
  static void match(const Napi::CallbackInfo& info);
  static void matchAsync(const Napi::CallbackInfo& info);
  static void knnMatch(const Napi::CallbackInfo& info);
  static void knnMatchAsync(const Napi::CallbackInfo& info);

  struct NewWorker : CatchCvExceptionWorker {
  public:
    int normType = cv::NORM_L2;
    bool crossCheck = false;

    bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
      return (
          FF::IntConverter::optArg(0, &normType, info) || FF::BoolConverter::optArg(1, &crossCheck, info));
    }

    bool hasOptArgsObject(const Napi::CallbackInfo& info) {
      return FF::isArgObject(info, 0);
    }

    bool unwrapOptionalArgsFromOpts(const Napi::CallbackInfo& info) {
      Napi::Object opts = info[0].As<Napi::Object>();
      return (
          FF::IntConverter::optProp(&normType, "history", opts) || FF::BoolConverter::optProp(&crossCheck, "crossCheck", opts));
    }

    std::string executeCatchCvExceptionWorker() {
      return "";
    }
  };
};

#endif
