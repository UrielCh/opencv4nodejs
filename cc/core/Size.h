#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_SIZE_H__
#define __FF_SIZE_H__

class Size : public FF::ObjectWrap<Size, cv::Size2d> {
public:
  static Napi::FunctionReference constructor;;

  static const char* getClassName() {
    return "Size";
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  FF_ACCESSORS(width, FF::DoubleConverter);
  FF_ACCESSORS(height, FF::DoubleConverter);
};

#endif