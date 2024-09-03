#include "Mat.h"
#include <opencv2/ximgproc.hpp>

#ifndef __FF_MATXIMGPROC_H__
#define __FF_MATXIMGPROC_H__

class MatXimgproc {
public:
  static void Init(Napi::FunctionReference ctor);

  static void GuidedFilter(const Napi::CallbackInfo& info);
  static void GuidedFilterAsync(const Napi::CallbackInfo& info);
};

#endif