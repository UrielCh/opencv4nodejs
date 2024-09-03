#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TEXT

#include "OCRHMMClassifier.h"
#include "OCRHMMClassifierBindings.h"

Nan::Persistent<v8::FunctionTemplate> OCRHMMClassifier::constructor;

Napi::Object OCRHMMClassifier(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(OCRHMMClassifier::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "OCRHMMClassifier"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(ctor, "eval", Eval);
  Nan::SetPrototypeMethod(ctor, "evalAsync", EvalAsync);

  Nan::Set(target, FF::newString(env, "OCRHMMClassifier"), FF::getFunction(ctor));
};

void OCRHMMClassifier::Eval(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<OCRHMMClassifierBindings::EvalWorker>(OCRHMMClassifier::unwrapSelf(info)),
      "OCRHMMClassifier::Eval",
      info);
}

void OCRHMMClassifier::EvalAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<OCRHMMClassifierBindings::EvalWorker>(OCRHMMClassifier::unwrapSelf(info)),
      "OCRHMMClassifier::EvalAsync",
      info);
}

#endif
