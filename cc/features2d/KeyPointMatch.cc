#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "KeyPointMatch.h"

Nan::Persistent<v8::FunctionTemplate> KeyPointMatch::constructor;

Napi::Object KeyPointMatch(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(KeyPointMatch::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("KeyPointMatch").ToLocalChecked());

  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("kpFrom").ToLocalChecked(), GetKpFrom);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("kpTo").ToLocalChecked(), GetKpTo);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("distance").ToLocalChecked(), GetDistance);

  target.Set("KeyPointMatch", FF::getFunction(ctor));
};

void KeyPointMatch::New(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("KeyPointMatch::New");
  FF_ASSERT_CONSTRUCT_CALL();
  if (info.Length() > 0) {
    // TODO check args
    KeyPointMatch* keyPointMatch = new KeyPointMatch();
    keyPointMatch->setNativeProps(
        Nan::ObjectWrap::Unwrap<KeyPoint>(info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked()),
        Nan::ObjectWrap::Unwrap<KeyPoint>(info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked()),
        (float)info[2]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value());
    keyPointMatch->Wrap(info.Holder());
  } else {
    (new KeyPointMatch())->Wrap(info.Holder());
  }

  info.GetReturnValue().Set(info.Holder());
}

NAN_GETTER(KeyPointMatch::GetKpFrom) {
  info.GetReturnValue().Set(Nan::New(Nan::ObjectWrap::Unwrap<KeyPointMatch>(info.This())->kpFrom));
}

NAN_GETTER(KeyPointMatch::GetKpTo) {
  info.GetReturnValue().Set(Nan::New(Nan::ObjectWrap::Unwrap<KeyPointMatch>(info.This())->kpTo));
}

NAN_GETTER(KeyPointMatch::GetDistance) {
  info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<KeyPointMatch>(info.This())->distance);
}

void KeyPointMatch::setNativeProps(KeyPoint* kpFrom, KeyPoint* kpTo, float distance) {
  this->kpFrom.Reset(kpFrom->persistent());
  this->kpTo.Reset(kpTo->persistent());
  this->distance = distance;
}

#endif
