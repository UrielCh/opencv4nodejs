#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TEXT

#include "OCRHMMDecoder.h"
#include "OCRHMMDecoderBindings.h"

Napi::FunctionReference OCRHMMDecoder::constructor;

Napi::Object OCRHMMDecoder(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, OCRHMMDecoder::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "OCRHMMDecoder"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(ctor, "run", Run);
  Nan::SetPrototypeMethod(ctor, "runAsync", RunAsync);
  Nan::SetPrototypeMethod(ctor, "runWithInfo", RunWithInfo);
  Nan::SetPrototypeMethod(ctor, "runWithInfoAsync", RunWithInfoAsync);

  Nan::Set(target, FF::newString(env, "OCRHMMDecoder"), FF::getFunction(ctor));
};

void OCRHMMDecoder::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "OCRHMMDecoder::New");
  FF_ASSERT_CONSTRUCT_CALL();
  OCRHMMDecoderBindings::NewWorker worker;

  if (worker.applyUnwrappers(info)) {
    return tryCatch.reThrow();
  }

  OCRHMMDecoder* self = new OCRHMMDecoder();
  self->setNativeObject(cv::text::OCRHMMDecoder::create(
      worker.classifier,
      worker.vocabulary,
      worker.transition_probabilities_table,
      worker.emission_probabilities_table
#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
      ,
      worker.mode
#endif
      ));

  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

void OCRHMMDecoder::Run(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<OCRHMMDecoderBindings::RunWorker>(OCRHMMDecoder::unwrapSelf(info)),
      "OCRHMMDecoder::Run",
      info);
}

void OCRHMMDecoder::RunAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<OCRHMMDecoderBindings::RunWorker>(OCRHMMDecoder::unwrapSelf(info)),
      "OCRHMMDecoder::RunAsync",
      info);
}

void OCRHMMDecoder::RunWithInfo(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<OCRHMMDecoderBindings::RunWithInfoWorker>(OCRHMMDecoder::unwrapSelf(info)),
      "OCRHMMDecoder::RunWithInfo",
      info);
}

void OCRHMMDecoder::RunWithInfoAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<OCRHMMDecoderBindings::RunWithInfoWorker>(OCRHMMDecoder::unwrapSelf(info)),
      "OCRHMMDecoder::RunWithInfoAsync",
      info);
}

#endif
