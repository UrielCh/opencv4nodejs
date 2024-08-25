#include "Mat.h"
#include <opencv2/ximgproc.hpp>

#ifndef __FF_MATXIMGPROC_H__
#define __FF_MATXIMGPROC_H__

class MatXimgproc {
public:
  static void Init(Napi::FunctionReference ctor);

  static NAN_METHOD(GuidedFilter);
  static NAN_METHOD(GuidedFilterAsync);
};

#endif