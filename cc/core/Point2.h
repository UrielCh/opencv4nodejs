#include "NativeNodeUtils.h"
#include "coreUtils.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_POINT2_H__
#define __FF_POINT2_H__

class Point2 : public FF::ObjectWrap<Point2, cv::Point2d> {
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "Point2";
  }

  static void Init(Napi::FunctionReference ctor) {
    FF_PROTO_SET_ARITHMETIC_OPERATIONS(ctor);
  }

  static Napi::Value New(const Napi::CallbackInfo& info) {
    Point2* self = new Point2();
    self->Wrap(info.Holder());
    return info.Holder();
  };

  FF_ACCESSORS(x, FF::DoubleConverter);
  FF_ACCESSORS(y, FF::DoubleConverter);

  FF_INIT_ARITHMETIC_OPERATIONS(Point2);

  static Napi::Value Norm(const Napi::CallbackInfo& info) {
    return Napi::New(env, cv::norm(Point2::unwrapSelf(info)));
  }

  static Napi::Value At(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    FF::TryCatch tryCatch(env, "Point2::At");
    FF_ASSERT_INDEX_RANGE(info[0].ToInt32(Napi::GetCurrentContext())->Value(), 1, "Point2");
    cv::Point2d ptSelf = Point2::unwrapSelf(info);
    const double coords[] = {ptSelf.x, ptSelf.y};
    return coords[info[0].ToUint32(Napi::GetCurrentContext())->Value()];
  }
};

#endif