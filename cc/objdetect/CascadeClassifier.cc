#include "opencv_modules.h"

#ifdef HAVE_OPENCV_OBJDETECT

#include "CascadeClassifier.h"
#include "CascadeClassifierBindings.h"

Nan::Persistent<v8::FunctionTemplate> CascadeClassifier::constructor;

Napi::Object CascadeClassifier(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(CascadeClassifier::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "CascadeClassifier"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(ctor, "detectMultiScale", DetectMultiScale);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleAsync", DetectMultiScaleAsync);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleGpu", DetectMultiScaleGpu);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleWithRejectLevels", DetectMultiScaleWithRejectLevels);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleWithRejectLevelsAsync", DetectMultiScaleWithRejectLevelsAsync);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleWithRejectLevelsGpu", DetectMultiScaleWithRejectLevelsGpu);

  Nan::Set(target, FF::newString(env, "CascadeClassifier"), FF::getFunction(ctor));
};

void CascadeClassifier::New(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("CascadeClassifier::New");
  FF_ASSERT_CONSTRUCT_CALL();
  CascadeClassifierBindings::NewWorker worker;

  if (worker.applyUnwrappers(info)) {
    return tryCatch.reThrow();
  }

  CascadeClassifier* self = new CascadeClassifier();
  self->setNativeObject(cv::CascadeClassifier(worker.xmlFilePath));
  if (worker.applyUnwrappers(info)) {
    return tryCatch.throwError(std::string("failed to load cascade.xml file: " + worker.xmlFilePath));
  }
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

void CascadeClassifier::DetectMultiScale(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<CascadeClassifierBindings::DetectMultiScaleWorker>(CascadeClassifier::unwrapSelf(info)),
      "CascadeClassifier::DetectMultiScale",
      info);
}

void CascadeClassifier::DetectMultiScaleAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<CascadeClassifierBindings::DetectMultiScaleWorker>(CascadeClassifier::unwrapSelf(info)),
      "CascadeClassifier::DetectMultiScaleAsync",
      info);
}

void CascadeClassifier::DetectMultiScaleGpu(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<CascadeClassifierBindings::DetectMultiScaleWorker>(CascadeClassifier::unwrapSelf(info)),
      "CascadeClassifier::DetectMultiScaleGpu",
      info);
}

void CascadeClassifier::DetectMultiScaleWithRejectLevels(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<CascadeClassifierBindings::DetectMultiScaleWithRejectLevelsWorker>(CascadeClassifier::unwrapSelf(info)),
      "CascadeClassifier::DetectMultiScaleWithRejectLevels",
      info);
}

void CascadeClassifier::DetectMultiScaleWithRejectLevelsAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<CascadeClassifierBindings::DetectMultiScaleWithRejectLevelsWorker>(CascadeClassifier::unwrapSelf(info)),
      "CascadeClassifier::DetectMultiScaleWithRejectLevelsAsync",
      info);
}

void CascadeClassifier::DetectMultiScaleWithRejectLevelsGpu(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<CascadeClassifierBindings::DetectMultiScaleWithRejectLevelsWorker>(CascadeClassifier::unwrapSelf(info)),
      "CascadeClassifier::DetectMultiScaleWithRejectLevelsGpu",
      info);
}

#endif
