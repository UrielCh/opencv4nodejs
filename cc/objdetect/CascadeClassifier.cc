#include "opencv_modules.h"

#ifdef HAVE_OPENCV_OBJDETECT

#include "CascadeClassifier.h"
#include "CascadeClassifierBindings.h"

Napi::FunctionReference CascadeClassifier::constructor;

Napi::Object CascadeClassifier(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, CascadeClassifier::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "CascadeClassifier"));

  InstanceMethod("detectMultiScale", &DetectMultiScale),
      InstanceMethod("detectMultiScaleAsync", &DetectMultiScaleAsync),
      InstanceMethod("detectMultiScaleGpu", &DetectMultiScaleGpu),
      InstanceMethod("detectMultiScaleWithRejectLevels", &DetectMultiScaleWithRejectLevels),
      InstanceMethod("detectMultiScaleWithRejectLevelsAsync", &DetectMultiScaleWithRejectLevelsAsync),
      InstanceMethod("detectMultiScaleWithRejectLevelsGpu", &DetectMultiScaleWithRejectLevelsGpu),

      (target).Set("CascadeClassifier", FF::getFunction(ctor));
};

void CascadeClassifier::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "CascadeClassifier::New");
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
  return info.Holder();
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
