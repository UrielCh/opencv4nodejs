#include "macros.h"

#ifndef __FF_FEATURES2D_H__
#define __FF_FEATURES2D_H__

class Features2d {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void DrawKeyPoints(const Napi::CallbackInfo& info);
  static void DrawMatches(const Napi::CallbackInfo& info);
};

#endif