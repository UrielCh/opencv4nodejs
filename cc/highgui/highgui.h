#include "CatchCvExceptionWorker.h"
#include "NativeNodeUtils.h"
#include "opencv2/highgui.hpp"

#ifndef __FF_HIGHGUI_H__
#define __FF_HIGHGUI_H__

class Highgui {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static void setWindowProperty(const Napi::CallbackInfo& info);
  static void getWindowProperty(const Napi::CallbackInfo& info);
  static void setWindowTitle(const Napi::CallbackInfo& info);
  static void moveWindow(const Napi::CallbackInfo& info);
  static void namedWindow(const Napi::CallbackInfo& info);
  static void resizeWindow(const Napi::CallbackInfo& info);
  static void startWindowThread(const Napi::CallbackInfo& info);
};

#endif
