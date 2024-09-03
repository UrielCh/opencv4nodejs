#include "NativeNodeUtils.h"
#include "coreUtils.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_VEC4_H__
#define __FF_VEC4_H__

class Vec4 : public FF::ObjectWrap<Vec4, cv::Vec4d> {
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "Vec4";
  }

  static Napi::Value New(const Napi::CallbackInfo& info) {
    Vec4* self = new Vec4();
    self->Wrap(info.Holder());
    return info.Holder();
  }

  static void Init(Napi::FunctionReference ctor) {
    FF_PROTO_SET_MATRIX_OPERATIONS(ctor);
  }

  FF_GETTER_CUSTOM(w, FF::DoubleConverter, self[0]);
  FF_GETTER_CUSTOM(x, FF::DoubleConverter, self[1]);
  FF_GETTER_CUSTOM(y, FF::DoubleConverter, self[2]);
  FF_GETTER_CUSTOM(z, FF::DoubleConverter, self[3]);

  FF_INIT_VEC4_OPERATIONS();

  static Napi::Value Dot(const Napi::CallbackInfo& info) {
    FF_OPERATOR_RET_SCALAR(&cv::Vec4d::dot, FF_APPLY_CLASS_FUNC, Vec4, "Dot");
  }

  static Napi::Value Norm(const Napi::CallbackInfo& info) {
    return Napi::New(env, cv::norm(Vec4::unwrapSelf(info)));
  }

  static Napi::Value At(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    FF::TryCatch tryCatch(env, "Vec4::At");
    FF_ASSERT_INDEX_RANGE(info[0].ToInt32(Napi::GetCurrentContext())->Value(), 3, "Vec4");
    cv::Vec4d vecSelf = Vec4::unwrapSelf(info);
    return vecSelf[info[0].ToInt32(Napi::GetCurrentContext())->Value()];
  }
};

#endif