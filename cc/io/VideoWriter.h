#include "CatchCvExceptionWorker.h"
#include "Mat.h"
#include "macros.h"
#include <opencv2/highgui.hpp>

#ifndef __FF_VIDEOWRITER_H__
#define __FF_VIDEOWRITER_H__

class VideoWriter : public FF::ObjectWrap<VideoWriter, cv::VideoWriter> {
public:
  static Napi::FunctionReference constructor;;

  static const char* getClassName() {
    return "VideoWriter";
  }

  std::string path;

  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static void New(const Napi::CallbackInfo& info);
  static void Fourcc(const Napi::CallbackInfo& info);
  static void Write(const Napi::CallbackInfo& info);
  static void WriteAsync(const Napi::CallbackInfo& info);
  static void Get(const Napi::CallbackInfo& info);
  static void GetAsync(const Napi::CallbackInfo& info);
  static void Set(const Napi::CallbackInfo& info);
  static void SetAsync(const Napi::CallbackInfo& info);
  static void Release(const Napi::CallbackInfo& info);
};

#endif