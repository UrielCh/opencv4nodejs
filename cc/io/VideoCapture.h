#include "CatchCvExceptionWorker.h"
#include "Mat.h"
#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/highgui.hpp>

#ifndef __FF_VIDEOCAPTURE_H__
#define __FF_VIDEOCAPTURE_H__

class VideoCapture : public FF::ObjectWrap<VideoCapture, cv::VideoCapture> {
public:
  static Napi::FunctionReference constructor;;

  static const char* getClassName() {
    return "VideoCapture";
  }

  std::string path;

  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static void New(const Napi::CallbackInfo& info);
  static void Read(const Napi::CallbackInfo& info);
  static void Reset(const Napi::CallbackInfo& info);
  static void ReadAsync(const Napi::CallbackInfo& info);
  static void Get(const Napi::CallbackInfo& info);
  static void GetAsync(const Napi::CallbackInfo& info);
  static void Set(const Napi::CallbackInfo& info);
  static void SetAsync(const Napi::CallbackInfo& info);
  static void Release(const Napi::CallbackInfo& info);
};

#endif