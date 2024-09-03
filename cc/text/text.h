#include "CatchCvExceptionWorker.h"
#include "Mat.h"
#include "NativeNodeUtils.h"
#include "OCRHMMClassifier.h"
#include "OCRHMMDecoder.h"
#include "macros.h"

#ifndef __FF_TEXT_H__
#define __FF_TEXT_H__

class Text {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static void LoadOCRHMMClassifierNM(const Napi::CallbackInfo& info);
  static void LoadOCRHMMClassifierNMAsync(const Napi::CallbackInfo& info);

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
  static void LoadOCRHMMClassifierCNN(const Napi::CallbackInfo& info);
  static void LoadOCRHMMClassifierCNNAsync(const Napi::CallbackInfo& info);

  static void CreateOCRHMMTransitionsTable(const Napi::CallbackInfo& info);
  static void CreateOCRHMMTransitionsTableAsync(const Napi::CallbackInfo& info);
#endif
};

#endif
