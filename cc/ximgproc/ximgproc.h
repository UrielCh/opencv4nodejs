#include "macros.h"
#include <opencv2/ximgproc.hpp>

#ifndef __FF_XIMGPROC_H__
#define __FF_XIMGPROC_H__

class XImgproc {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
};

#endif