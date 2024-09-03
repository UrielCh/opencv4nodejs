#include "Mat.h"
#include <opencv2/photo.hpp>

#ifndef __FF_MATPHOTO_H__
#define __FF_MATPHOTO_H__

class MatPhoto {
public:
  static void Init(Napi::FunctionReference ctor);

  static void SeamlessClone(const Napi::CallbackInfo& info);
  static void SeamlessCloneAsync(const Napi::CallbackInfo& info);
};

#endif