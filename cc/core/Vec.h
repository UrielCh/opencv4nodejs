#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Vec6.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_VEC_H__
#define __FF_VEC_H__

class Vec : public Napi::ObjectWrap<Vec> {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);
  static void NewVec2(const Napi::CallbackInfo& info);
  static void NewVec3(const Napi::CallbackInfo& info);
  static void NewVec4(const Napi::CallbackInfo& info);
  static void NewVec6(const Napi::CallbackInfo& info);

  static Napi::FunctionReference constructor;;
};

#endif
