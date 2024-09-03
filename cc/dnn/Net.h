#include "CatchCvExceptionWorker.h"
#include "Mat.h"
#include "NativeNodeUtils.h"
#include "opencv2/dnn.hpp"

#ifndef __FF_NET_H__
#define __FF_NET_H__

class Net : public FF::ObjectWrap<Net, cv::dnn::Net> {
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "Net";
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static void New(const Napi::CallbackInfo& info);
  // setInput(blob: Mat, name?: string, scalefactor?: number, mean?: number): void;
  // setInput(blob: Mat, inputName?: string): void;
  static void SetInput(const Napi::CallbackInfo& info);
  static void SetInputAsync(const Napi::CallbackInfo& info);
  // forward(inputName?: string): Mat;
  static void Forward(const Napi::CallbackInfo& info);
  static void ForwardAsync(const Napi::CallbackInfo& info);
  // getLayerNames(): string[];
  static void GetLayerNames(const Napi::CallbackInfo& info);
  static void GetLayerNamesAsync(const Napi::CallbackInfo& info);
  // getUnconnectedOutLayers(): number[];
  static void GetUnconnectedOutLayers(const Napi::CallbackInfo& info);
  static void GetUnconnectedOutLayersAsync(const Napi::CallbackInfo& info);
  // dump(): string;
  static void Dump(const Napi::CallbackInfo& info);
  // setPreferableBackend(backendId: number): void;
  static void SetPreferableBackend(const Napi::CallbackInfo& info);
  // setPreferableTarget(targetId: number): void;
  static void SetPreferableTarget(const Napi::CallbackInfo& info);
  // getPerfProfile(): {	retval: number, timings: number[] };
  static void GetPerfProfile(const Napi::CallbackInfo& info);
};

#endif