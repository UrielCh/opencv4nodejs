#include "CatchCvExceptionWorker.h"
#include "NativeNodeUtils.h"
#include "Size.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_RECT_H__
#define __FF_RECT_H__

class Rect : public FF::ObjectWrap<Rect, cv::Rect2d> {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor;

  static const char* getClassName() {
    return "Rect";
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  FF_ACCESSORS(x, FF::DoubleConverter);
  FF_ACCESSORS(y, FF::DoubleConverter);
  FF_ACCESSORS(width, FF::DoubleConverter);
  FF_ACCESSORS(height, FF::DoubleConverter);

  static void New(const Napi::CallbackInfo& info);
  static void And(const Napi::CallbackInfo& info);
  static void Or(const Napi::CallbackInfo& info);
  static void ToSquare(const Napi::CallbackInfo& info);
  static void ToSquareAsync(const Napi::CallbackInfo& info);
  static void Pad(const Napi::CallbackInfo& info);
  static void PadAsync(const Napi::CallbackInfo& info);
  static void Rescale(const Napi::CallbackInfo& info);
  static void RescaleAsync(const Napi::CallbackInfo& info);
};

#endif