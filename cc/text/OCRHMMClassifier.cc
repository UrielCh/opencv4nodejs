#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TEXT

#include "OCRHMMClassifier.h"
#include "OCRHMMClassifierBindings.h"

Napi::FunctionReference OCRHMMClassifier::constructor;

Napi::Object OCRHMMClassifier(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, OCRHMMClassifier::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "OCRHMMClassifier"));


  InstanceMethod("eval", &Eval),
  InstanceMethod("evalAsync", &EvalAsync),

  (target).Set("OCRHMMClassifier", FF::getFunction(ctor));
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
