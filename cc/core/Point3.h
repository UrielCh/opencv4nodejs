#include "NativeNodeUtils.h"
#include "coreUtils.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_POINT3_H__
#define __FF_POINT3_H__

class Point3 : public FF::ObjectWrap<Point3, cv::Point3d> {
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "Point3";
  }

  static void Init(Napi::FunctionReference ctor) {
    FF_PROTO_SET_ARITHMETIC_OPERATIONS(ctor);
  }

  static Napi::Value New(const Napi::CallbackInfo& info) {
    Point3* self = new Point3();
    self->Wrap(info.Holder());
    return info.Holder();
  };

  FF_ACCESSORS(x, FF::DoubleConverter);
  FF_ACCESSORS(y, FF::DoubleConverter);
  FF_ACCESSORS(z, FF::DoubleConverter);

  FF_INIT_ARITHMETIC_OPERATIONS(Point3);

  static Napi::Value Norm(const Napi::CallbackInfo& info) {
    return Napi::New(env, cv::norm(Point3::unwrapSelf(info)));
  }

  static Napi::Value At(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    FF::TryCatch tryCatch(env, "Point3::At");
    FF_ASSERT_INDEX_RANGE(info[0].ToInt32(Napi::GetCurrentContext())->Value(), 2, "Point3");
    cv::Point3d ptSelf = Point3::unwrapSelf(info);
    const double coords[] = {ptSelf.x, ptSelf.y, ptSelf.z};
    return coords[info[0].ToInt32(Napi::GetCurrentContext())->Value()];
  }
};

#endif