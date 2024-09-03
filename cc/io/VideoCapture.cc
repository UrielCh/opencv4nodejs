#include "opencv_modules.h"

#ifdef HAVE_IO

#include "VideoCapture.h"
#include "VideoCaptureBindings.h"

Napi::FunctionReference VideoCapture::constructor;

Napi::Object VideoCapture(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, VideoCapture::New));
  constructor.Reset(ctor);

  ctor->SetClassName(FF::newString(env, "VideoCapture"));
  InstanceMethod("read", &Read),
  InstanceMethod("reset", &Reset),
  InstanceMethod("readAsync", &ReadAsync),
  InstanceMethod("get", &Get),
  InstanceMethod("getAsync", &GetAsync),
  InstanceMethod("set", &Set),
  InstanceMethod("setAsync", &SetAsync),
  InstanceMethod("release", &Release),
  (target).Set("VideoCapture", FF::getFunction(ctor));
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
    self->self.open(info[0].ToUint32(Napi::GetCurrentContext())->Value());
  } else {
    return tryCatch.throwError("expected arg 0 to be path or device port");
  }
  if (!self->self.isOpened()) {
    return tryCatch.throwError("failed to open capture");
  }

  self->Wrap(info.Holder());
  return info.Holder();
}

void VideoCapture::Reset(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "VideoCapture::Reset");
  VideoCapture* self = this;
  self->self.release();
  self->self.open(self->path);
  if (!self->self.isOpened()) {
    return tryCatch.throwError("failed to reset capture");
  }
}

void VideoCapture::Release(const Napi::CallbackInfo& info) {
  info.This())->self.release(.Unwrap<VideoCapture>();
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