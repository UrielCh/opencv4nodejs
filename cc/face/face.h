#include "NativeNodeUtils.h"
#include "macros.h"
#include "opencv2/face.hpp"

#ifndef __FF_FACE_H__
#define __FF_FACE_H__

class Face {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
};

#endif