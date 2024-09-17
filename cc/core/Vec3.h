#include "NativeNodeUtils.h"
#include "coreUtils.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_VEC3_H__
#define __FF_VEC3_H__

class Vec3 : public FF::ObjectWrap<Vec3, cv::Vec3d> {
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "Vec3";
  }

  static Napi::Value New(const Napi::CallbackInfo& info) {
    Vec3* self = new Vec3();
    self->Wrap(info.Holder());
    return info.Holder();
  }

  static void Init(Napi::FunctionReference ctor) {
    FF_PROTO_SET_MATRIX_OPERATIONS(ctor);
  }

  FF_GETTER_CUSTOM(x, FF::DoubleConverter, self[0]);
  FF_GETTER_CUSTOM(y, FF::DoubleConverter, self[1]);
  FF_GETTER_CUSTOM(z, FF::DoubleConverter, self[2]);

  FF_INIT_VEC3_OPERATIONS();

  static Napi::Value Dot(const Napi::CallbackInfo& info) {
    FF_OPERATOR_RET_SCALAR(&cv::Vec3d::dot, FF_APPLY_CLASS_FUNC, Vec3, "Dot");
  }

  static Napi::Value Cross(const Napi::CallbackInfo& info) {
    FF_OPERATOR(&cv::Vec3d::cross, FF_APPLY_CLASS_FUNC, Vec3, "Cross");
  }

  static Napi::Value Norm(const Napi::CallbackInfo& info) {
    return Napi::New(env, cv::norm(Vec3::unwrapSelf(info)));
  }

  static Napi::Value At(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    FF::TryCatch tryCatch(env, "Vec3::At");
    FF_ASSERT_INDEX_RANGE(info[0].As<Napi::Number>().Int32Value(), 2, "Vec3");
    cv::Vec3d vecSelf = Vec3::unwrapSelf(info);
    return vecSelf[info[0].As<Napi::Number>().Int32Value()];
  }
};

#endif