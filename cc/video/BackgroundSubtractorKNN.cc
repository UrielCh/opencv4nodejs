#include "opencv_modules.h"

#ifdef HAVE_OPENCV_VIDEO

#include "BackgroundSubtractorKNN.h"

Napi::FunctionReference BackgroundSubtractorKNN::constructor;

Napi::Object BackgroundSubtractorKNN(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, BackgroundSubtractorKNN::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  BackgroundSubtractor::Init(env, exports);
  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "BackgroundSubtractorKNN"));

  Napi::SetAccessor(instanceTemplate, FF::newString(env, "history"), history_getter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "dist2Threshold"), dist2Threshold_getter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "detectShadows"), detectShadows_getter);

  (target).Set("BackgroundSubtractorKNN", FF::getFunction(ctor));
};

void BackgroundSubtractorKNN::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "BackgroundSubtractor::New");
  FF_ASSERT_CONSTRUCT_CALL();
  BackgroundSubtractorKNN::NewWorker worker;

  if (worker.applyUnwrappers(info)) {
    return tryCatch.reThrow();
  }

  BackgroundSubtractorKNN* self = new BackgroundSubtractorKNN();
  self->self = cv::createBackgroundSubtractorKNN((int)worker.history, worker.dist2Threshold, worker.detectShadows);
  self->Wrap(info.Holder());
  return info.Holder();
}

#endif