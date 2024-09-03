#include "CatchCvExceptionWorker.h"
#include "Mat.h"
#include "NativeNodeUtils.h"
#include "Net.h"
#include "opencv2/dnn.hpp"

#ifndef __FF_DNN_H__
#define __FF_DNN_H__

class Dnn {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static void ReadNetFromTensorflow(const Napi::CallbackInfo& info);
  static void ReadNetFromTensorflowAsync(const Napi::CallbackInfo& info);
  static void ReadNetFromCaffe(const Napi::CallbackInfo& info);
  static void ReadNetFromCaffeAsync(const Napi::CallbackInfo& info);
  static void BlobFromImage(const Napi::CallbackInfo& info);
  static void BlobFromImageAsync(const Napi::CallbackInfo& info);
  static void BlobFromImages(const Napi::CallbackInfo& info);
  static void BlobFromImagesAsync(const Napi::CallbackInfo& info);
#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
  static void ReadNetFromDarknet(const Napi::CallbackInfo& info);
  static void ReadNetFromDarknetAsync(const Napi::CallbackInfo& info);
  static void NMSBoxes(const Napi::CallbackInfo& info);
#endif
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  static void ReadNetFromONNX(const Napi::CallbackInfo& info);
  static void ReadNetFromONNXAsync(const Napi::CallbackInfo& info);
#endif
#if CV_VERSION_GREATER_EQUAL(3, 4, 2)
  static void ReadNet(const Napi::CallbackInfo& info);
  static void ReadNetAsync(const Napi::CallbackInfo& info);
#endif
};

#endif
