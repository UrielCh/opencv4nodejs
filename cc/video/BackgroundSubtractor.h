#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>

#ifndef __FF_BACKGROUNDSUBTRACTOR_H__
#define __FF_BACKGROUNDSUBTRACTOR_H__

class BackgroundSubtractor : public FF::ObjectWrapBase<BackgroundSubtractor>, public Nan::ObjectWrap {
public:
  virtual cv::Ptr<cv::BackgroundSubtractor> getSubtractor() = 0;
  cv::Mat fgMask;

  static void Init(Napi::FunctionReference);
  static void SetBackgroundImage(const Napi::CallbackInfo& info);
  static void Apply(const Napi::CallbackInfo& info);
};

#endif