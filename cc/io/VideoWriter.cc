#include "opencv_modules.h"

#ifdef HAVE_IO

#include "VideoWriter.h"
#include "VideoWriterBindings.h"

Napi::FunctionReference VideoWriter::constructor;

Napi::Object VideoWriter(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(VideoWriter::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(FF::newString(env, "VideoWriter"));
  Nan::SetMethod(ctor, "fourcc", Fourcc);
  Nan::SetPrototypeMethod(ctor, "write", Write);
  Nan::SetPrototypeMethod(ctor, "writeAsync", WriteAsync);
  Nan::SetPrototypeMethod(ctor, "get", Get);
  Nan::SetPrototypeMethod(ctor, "getAsync", GetAsync);
  Nan::SetPrototypeMethod(ctor, "set", Set);
  Nan::SetPrototypeMethod(ctor, "setAsync", SetAsync);
  Nan::SetPrototypeMethod(ctor, "release", Release);
  Nan::Set(target, FF::newString(env, "VideoWriter"), FF::getFunction(ctor));
};

void VideoWriter::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "VideoWriter::New");
  FF_ASSERT_CONSTRUCT_CALL();
  VideoWriterBindings::NewWorker worker;

  if (worker.applyUnwrappers(info)) {
    return tryCatch.reThrow();
  }

  VideoWriter* self = new VideoWriter();
  self->self.open(worker.fileName, worker.fourccCode, worker.fps, (cv::Size)worker.frameSize, worker.isColor);
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

void VideoWriter::Release(const Napi::CallbackInfo& info) {
  Nan::ObjectWrap::Unwrap<VideoWriter>(info.This())->self.release();
}

void VideoWriter::Get(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<VideoWriterBindings::GetWorker>(VideoWriter::unwrapSelf(info)),
      "VideoWriter::Get",
      info);
}

void VideoWriter::GetAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<VideoWriterBindings::GetWorker>(VideoWriter::unwrapSelf(info)),
      "VideoWriter::GetAsync",
      info);
}

void VideoWriter::Set(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<VideoWriterBindings::SetWorker>(VideoWriter::unwrapSelf(info)),
      "VideoCaptureVideoWriter::Set",
      info);
}

void VideoWriter::SetAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<VideoWriterBindings::SetWorker>(VideoWriter::unwrapSelf(info)),
      "VideoWriter::SetAsync",
      info);
}

void VideoWriter::Fourcc(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<VideoWriterBindings::FourccWorker>(),
      "VideoWriter::Fourcc",
      info);
}

void VideoWriter::Write(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<VideoWriterBindings::WriteWorker>(VideoWriter::unwrapSelf(info)),
      "VideoWriter::Write",
      info);
}

void VideoWriter::WriteAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<VideoWriterBindings::WriteWorker>(VideoWriter::unwrapSelf(info)),
      "VideoWriter::WriteAsync",
      info);
}

#endif