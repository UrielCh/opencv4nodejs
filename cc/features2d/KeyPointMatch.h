#include "KeyPoint.h"
#include "macros.h"
#include <opencv2/imgproc.hpp>

#ifndef FF_KEYPOINTMATCH_H_
#define FF_KEYPOINTMATCH_H_

class KeyPointMatch : public Napi::ObjectWrap<KeyPointMatch> {
public:
  Nan::Persistent<v8::Object> kpFrom;
  Nan::Persistent<v8::Object> kpTo;
  float distance;

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);
  static NAN_GETTER(GetKpFrom);
  static NAN_GETTER(GetKpTo);
  static NAN_GETTER(GetDistance);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

  void setNativeProps(KeyPoint* kpFrom, KeyPoint* kpTo, float distance);

  KeyPoint* getKpFrom() {
    return Nan::ObjectWrap::Unwrap<KeyPoint>(Nan::New(this->kpFrom));
  }

  KeyPoint* getKpTo() {
    return Nan::ObjectWrap::Unwrap<KeyPoint>(Nan::New(this->kpTo));
  }
};

#endif