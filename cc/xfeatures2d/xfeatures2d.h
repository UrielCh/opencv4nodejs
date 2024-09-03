#include "macros.h"

#ifndef __FF_XFEATURES2D_H__
#define __FF_XFEATURES2D_H__

class XFeatures2d {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
};

#endif