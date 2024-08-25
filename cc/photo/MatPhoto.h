#include "Mat.h"
#include <opencv2/photo.hpp>

#ifndef __FF_MATPHOTO_H__
#define __FF_MATPHOTO_H__

class MatPhoto {
public:
  static void Init(Napi::FunctionReference ctor);

  static NAN_METHOD(SeamlessClone);
  static NAN_METHOD(SeamlessCloneAsync);
};

#endif