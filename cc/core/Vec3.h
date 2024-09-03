#include "NativeNodeUtils.h"
#include "coreUtils.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_VEC3_H__
#define __FF_VEC3_H__

class Vec3 : public FF::ObjectWrap<Vec3, cv::Vec3d> {
public:
  static Napi::FunctionReference constructor;;

  static const char* getClassName() {
    return "Vec3";
  }

  static NAN_METHOD(New) {
    Vec3* self = new Vec3();
    self->Wrap(info.Holder());
    info.GetReturnValue().Set(info.Holder());
  }

  static void Init(Napi::FunctionReference ctor) {
    FF_PROTO_SET_MATRIX_OPERATIONS(ctor);
  }

  FF_GETTER_CUSTOM(x, FF::DoubleConverter, self[0]);
  FF_GETTER_CUSTOM(y, FF::DoubleConverter, self[1]);
  FF_GETTER_CUSTOM(z, FF::DoubleConverter, self[2]);

  FF_INIT_VEC3_OPERATIONS();

  static NAN_METHOD(Dot) {
    FF_OPERATOR_RET_SCALAR(&cv::Vec3d::dot, FF_APPLY_CLASS_FUNC, Vec3, "Dot");
  }

  static NAN_METHOD(Cross) {
    FF_OPERATOR(&cv::Vec3d::cross, FF_APPLY_CLASS_FUNC, Vec3, "Cross");
  }

  static NAN_METHOD(Norm) {
    info.GetReturnValue().Set(Nan::New(cv::norm(Vec3::unwrapSelf(info))));
  }

  static NAN_METHOD(At) {
    Napi::Env env = info.Env();  
    FF::TryCatch tryCatch(env, "Vec3::At");
    FF_ASSERT_INDEX_RANGE(info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value(), 2, "Vec3");
    cv::Vec3d vecSelf = Vec3::unwrapSelf(info);
    info.GetReturnValue().Set(vecSelf[info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value()]);
  }
};

#endif