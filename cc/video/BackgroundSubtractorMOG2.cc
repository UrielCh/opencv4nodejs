#include "opencv_modules.h"

#ifdef HAVE_OPENCV_VIDEO

#include "BackgroundSubtractorMOG2.h"

Nan::Persistent<v8::FunctionTemplate> BackgroundSubtractorMOG2::constructor;

Napi::Object BackgroundSubtractorMOG2(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, BackgroundSubtractorMOG2::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  BackgroundSubtractor::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "BackgroundSubtractorMOG2"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString(env, "history"), history_getter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "varThreshold"), varThreshold_getter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "detectShadows"), detectShadows_getter);

  Nan::Set(target, FF::newString(env, "BackgroundSubtractorMOG2"), FF::getFunction(ctor));
};

void BackgroundSubtractorMOG2::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "BackgroundSubtractor::New");
  FF_ASSERT_CONSTRUCT_CALL();
  BackgroundSubtractorMOG2::NewWorker worker;

  if (worker.applyUnwrappers(info)) {
    return tryCatch.reThrow();
  }

  BackgroundSubtractorMOG2* self = new BackgroundSubtractorMOG2();
  self->self = cv::createBackgroundSubtractorMOG2((int)worker.history, worker.varThreshold, worker.detectShadows);
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

#endif