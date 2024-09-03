#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "KeyPointMatch.h"

Napi::FunctionReference KeyPointMatch::constructor;

Napi::Object KeyPointMatch(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, KeyPointMatch::New));
  constructor.Reset(ctor);

  ctor->SetClassName(Napi::String::New(env, "KeyPointMatch"));

  Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "kpFrom"), GetKpFrom);
  Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "kpTo"), GetKpTo);
  Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "distance"), GetDistance);

  target.Set("KeyPointMatch", FF::getFunction(ctor));
};

void KeyPointMatch::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "KeyPointMatch::New");
  FF_ASSERT_CONSTRUCT_CALL();
  if (info.Length() > 0) {
    // TODO check args
    KeyPointMatch* keyPointMatch = new KeyPointMatch();
    keyPointMatch->setNativeProps(
        Napi::ObjectWrap::Unwrap<KeyPoint>(info[0].ToObject(Napi::GetCurrentContext())),
        Napi::ObjectWrap::Unwrap<KeyPoint>(info[1].ToObject(Napi::GetCurrentContext())),
        (float)info[2].ToNumber(Napi::GetCurrentContext())->Value());
    keyPointMatch->Wrap(info.Holder());
  } else {
    (new KeyPointMatch())->Wrap(info.Holder());
  }

  return info.Holder();
}

Napi::Value KeyPointMatch::GetKpFrom(const Napi::CallbackInfo& info) {
  return Napi::New(env, info.This())->kpFrom).Unwrap<KeyPointMatch>(;
}

Napi::Value KeyPointMatch::GetKpTo(const Napi::CallbackInfo& info) {
  return Napi::New(env, info.This())->kpTo).Unwrap<KeyPointMatch>(;
}

Napi::Value KeyPointMatch::GetDistance(const Napi::CallbackInfo& info) {
  return info.This())->distance.Unwrap<KeyPointMatch>(;
}

void KeyPointMatch::setNativeProps(KeyPoint* kpFrom, KeyPoint* kpTo, float distance) {
  this->kpFrom.Reset(kpFrom->persistent());
  this->kpTo.Reset(kpTo->persistent());
  this->distance = distance;
}

#endif
