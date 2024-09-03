#include "Mat.h"
#include "macros.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/photo.hpp>

#ifndef __FF_PHOTO_H__
#define __FF_PHOTO_H__

class Photo {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void FastNlMeansDenoisingColored(const Napi::CallbackInfo& info);
  static void FastNlMeansDenoisingColoredAsync(const Napi::CallbackInfo& info);
  static void Inpaint(const Napi::CallbackInfo& info);
  static void InpaintAsync(const Napi::CallbackInfo& info);
  static void SeamlessClone(const Napi::CallbackInfo& info);
  static void SeamlessCloneAsync(const Napi::CallbackInfo& info);
};

#endif