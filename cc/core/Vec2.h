#include "NativeNodeUtils.h"
#include "coreUtils.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_VEC2_H__
#define __FF_VEC2_H__

class Vec2 : public FF::ObjectWrap<Vec2, cv::Vec2d> {
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "Vec2";
  }

  static Napi::Value New(const Napi::CallbackInfo& info) {
    Vec2* self = new Vec2();
    self->Wrap(info.Holder());
    return info.Holder();
  }

  static void Init(Napi::FunctionReference ctor) {
    FF_PROTO_SET_MATRIX_OPERATIONS(ctor);
  }

  FF_GETTER_CUSTOM(x, FF::DoubleConverter, self[0]);
  FF_GETTER_CUSTOM(y, FF::DoubleConverter, self[1]);

  FF_INIT_VEC2_OPERATIONS();

  static Napi::Value Dot(const Napi::CallbackInfo& info) {
    FF_OPERATOR_RET_SCALAR(&cv::Vec2d::dot, FF_APPLY_CLASS_FUNC, Vec2, "Dot");
  }

  static Napi::Value Norm(const Napi::CallbackInfo& info) {
    return Napi::New(env, cv::norm(Vec2::unwrapSelf(info)));
  }

  static Napi::Value At(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    FF::TryCatch tryCatch(env, "Vec2::At");
    FF_ASSERT_INDEX_RANGE(info[0].As<Napi::Number>().Int32Value(), 1, "Vec2");
    cv::Vec2d vecSelf = Vec2::unwrapSelf(info);
    return vecSelf[info[0].ToUint32(Napi::GetCurrentContext())->Value()];
  }
};

#endif