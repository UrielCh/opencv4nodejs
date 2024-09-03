#include "opencv_modules.h"

#ifdef HAVE_IO

#include "VideoCapture.h"
#include "VideoCaptureBindings.h"

Napi::FunctionReference VideoCapture::constructor;

Napi::Object VideoCapture(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, VideoCapture::New));
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(FF::newString(env, "VideoCapture"));
  Nan::SetPrototypeMethod(ctor, "read", Read);
  Nan::SetPrototypeMethod(ctor, "reset", Reset);
  Nan::SetPrototypeMethod(ctor, "readAsync", ReadAsync);
  Nan::SetPrototypeMethod(ctor, "get", Get);
  Nan::SetPrototypeMethod(ctor, "getAsync", GetAsync);
  Nan::SetPrototypeMethod(ctor, "set", Set);
  Nan::SetPrototypeMethod(ctor, "setAsync", SetAsync);
  Nan::SetPrototypeMethod(ctor, "release", Release);
  Nan::Set(target, FF::newString(env, "VideoCapture"), FF::getFunction(ctor));
};

void VideoCapture::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "VideoCapture::New");
  FF_ASSERT_CONSTRUCT_CALL();
  VideoCapture* self = new VideoCapture();
  if (info[0].IsString()) {
    self->path = FF::StringConverter::unwrapUnchecked(info[0]);
    self->self.open(self->path);
  } else if (info[0].IsUint32()) {
    self->self.open(info[0]->ToUint32(Nan::GetCurrentContext()).ToLocalChecked()->Value());
  } else {
    return tryCatch.throwError("expected arg 0 to be path or device port");
  }
  if (!self->self.isOpened()) {
    return tryCatch.throwError("failed to open capture");
  }

  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

void VideoCapture::Reset(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "VideoCapture::Reset");
  VideoCapture* self = Nan::ObjectWrap::Unwrap<VideoCapture>(info.This());
  self->self.release();
  self->self.open(self->path);
  if (!self->self.isOpened()) {
    return tryCatch.throwError("failed to reset capture");
  }
}

void VideoCapture::Release(const Napi::CallbackInfo& info) {
  Nan::ObjectWrap::Unwrap<VideoCapture>(info.This())->self.release();
}

void VideoCapture::Get(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<VideoCaptureBindings::GetWorker>(VideoCapture::unwrapSelf(info)),
      "VideoCapture::Get",
      info);
}

void VideoCapture::GetAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<VideoCaptureBindings::GetWorker>(VideoCapture::unwrapSelf(info)),
      "VideoCapture::GetAsync",
      info);
}

void VideoCapture::Read(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<VideoCaptureBindings::ReadWorker>(VideoCapture::unwrapSelf(info)),
      "VideoCapture::Read",
      info);
}

void VideoCapture::ReadAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<VideoCaptureBindings::ReadWorker>(VideoCapture::unwrapSelf(info)),
      "VideoCapture::ReadAsync",
      info);
}

void VideoCapture::Set(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<VideoCaptureBindings::SetWorker>(VideoCapture::unwrapSelf(info)),
      "VideoCapture::Set",
      info);
}

void VideoCapture::SetAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<VideoCaptureBindings::SetWorker>(VideoCapture::unwrapSelf(info)),
      "VideoCapture::SetAsync",
      info);
}

#endif