#include "opencv_modules.h"

#ifdef HAVE_IO

#include "VideoWriter.h"
#include "VideoWriterBindings.h"

Napi::FunctionReference VideoWriter::constructor;

Napi::Object VideoWriter(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, VideoWriter::New));
  constructor.Reset(ctor);

  ctor->SetClassName(FF::newString(env, "VideoWriter"));
  Napi::SetMethod(ctor, "fourcc", Fourcc);
  InstanceMethod("write", &Write),
      InstanceMethod("writeAsync", &WriteAsync),
      InstanceMethod("get", &Get),
      InstanceMethod("getAsync", &GetAsync),
      InstanceMethod("set", &Set),
      InstanceMethod("setAsync", &SetAsync),
      InstanceMethod("release", &Release),
      (target).Set("VideoWriter", FF::getFunction(ctor));
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
  return info.Holder();
}

void VideoWriter::Release(const Napi::CallbackInfo& info) {
  info.This())->self.release(.Unwrap<VideoWriter>();
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