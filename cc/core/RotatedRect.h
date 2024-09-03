#include "Point.h"
#include "Rect.h"
#include "Size.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_ROTATEDRECT_H__
#define __FF_ROTATEDRECT_H__

class RotatedRect : public FF::ObjectWrap<RotatedRect, cv::RotatedRect> {
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "RotatedRect";
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  FF_ACCESSORS(angle, FF::FloatConverter);
  FF_ACCESSORS(center, Point2::Converter);
  FF_ACCESSORS(size, Size::Converter);

  static Napi::Value BoundingRect(const Napi::CallbackInfo& info) {
    return Rect::Converter::wrap(unwrapSelf(info).boundingRect());
  }
};

#endif