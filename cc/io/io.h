#include "CatchCvExceptionWorker.h"
#include "Mat.h"
#include "VideoCapture.h"
#include "VideoWriter.h"
#include "macros.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#ifndef __FF_IO_H_
#define __FF_IO_H_

class Io {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static void Imshow(const Napi::CallbackInfo& info);
  static void ImshowWait(const Napi::CallbackInfo& info);
  static void WaitKey(const Napi::CallbackInfo& info);
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  static void WaitKeyEx(const Napi::CallbackInfo& info);
#endif
  // static void MoveWindow(const Napi::CallbackInfo& info); moved to highgui
  static void DestroyWindow(const Napi::CallbackInfo& info);
  static void DestroyAllWindows(const Napi::CallbackInfo& info);
  static void Imread(const Napi::CallbackInfo& info);
  static void ImreadAsync(const Napi::CallbackInfo& info);
  static void Imwrite(const Napi::CallbackInfo& info);
  static void ImwriteAsync(const Napi::CallbackInfo& info);
  static void Imencode(const Napi::CallbackInfo& info);
  static void ImencodeAsync(const Napi::CallbackInfo& info);
  static void Imdecode(const Napi::CallbackInfo& info);
  static void ImdecodeAsync(const Napi::CallbackInfo& info);
};

#endif
