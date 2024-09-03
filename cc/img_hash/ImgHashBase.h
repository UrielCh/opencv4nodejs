#include "Mat.h"
#include "NativeNodeUtils.h"
#include "Point.h"
#include "Rect.h"
#include "macros.h"
#include <iostream>
#include <opencv2/img_hash.hpp>

#ifndef __FF_IMGHASHBASE_H__
#define __FF_IMGHASHBASE_H__

class ImgHashBase : public FF::ObjectWrapBase<ImgHashBase>, public Napi::ObjectWrap {
public:
  virtual cv::Ptr<cv::img_hash::ImgHashBase> getImgHashBase() = 0;

  static void Init(Napi::FunctionReference);

  static void Compare(const Napi::CallbackInfo& info);
  static void CompareAsync(const Napi::CallbackInfo& info);
  static void Compute(const Napi::CallbackInfo& info);
  static void ComputeAsync(const Napi::CallbackInfo& info);
};

#endif
