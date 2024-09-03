#include "KeyPoint.h"
#include "macros.h"
#include <opencv2/imgproc.hpp>

#ifndef FF_KEYPOINTMATCH_H_
#define FF_KEYPOINTMATCH_H_

class KeyPointMatch : public Napi::ObjectWrap<KeyPointMatch> {
public:
  Napi::Persistent<v8::Object> kpFrom;
  Napi::Persistent<v8::Object> kpTo;
  float distance;

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);
  Napi::Value GetKpFrom(const Napi::CallbackInfo& info);
  Napi::Value GetKpTo(const Napi::CallbackInfo& info);
  Napi::Value GetDistance(const Napi::CallbackInfo& info);

  static Napi::FunctionReference constructor;
  ;

  void setNativeProps(KeyPoint* kpFrom, KeyPoint* kpTo, float distance);

  KeyPoint* getKpFrom() {
    return Napi::New(env, this->kpFrom).Unwrap<KeyPoint>();
  }

  KeyPoint* getKpTo() {
    return Napi::New(env, this->kpTo).Unwrap<KeyPoint>();
  }
};

#endif