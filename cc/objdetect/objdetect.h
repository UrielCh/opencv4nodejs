#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>

#ifndef __FF_OBJDETECT_H__
#define __FF_OBJDETECT_H__

class Objdetect {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
};

#endif