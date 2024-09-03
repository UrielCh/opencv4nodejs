#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_TERMCRITERIA_H__
#define __FF_TERMCRITERIA_H__

class TermCriteria : public FF::ObjectWrap<TermCriteria, cv::TermCriteria> {
public:
  static Napi::FunctionReference constructor;;

  static const char* getClassName() {
    return "TermCriteria";
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  int type;     //!< the type of termination criteria: COUNT, EPS or COUNT + EPS
  int maxCount; //!< the maximum number of iterations/elements
  double epsilon;

  FF_ACCESSORS(type, FF::IntConverter);
  FF_ACCESSORS(maxCount, FF::IntConverter);
  FF_ACCESSORS(epsilon, FF::DoubleConverter);
};

#endif