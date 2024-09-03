#include "ImgHashBase.h"

#ifndef __FF_PHASH_H__
#define __FF_PHASH_H__

class PHash : public ImgHashBase {
public:
  cv::Ptr<cv::img_hash::ImgHashBase> imgHashBase;

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  static Napi::FunctionReference constructor;;

  cv::Ptr<cv::img_hash::ImgHashBase> getImgHashBase() {
    return imgHashBase;
  }
};

#endif
