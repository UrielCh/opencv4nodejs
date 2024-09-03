#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "FASTDetector.h"

Napi::FunctionReference FASTDetector::constructor;

Napi::Object FASTDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, FASTDetector::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(Napi::String::New(env, "FASTDetector"));


  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "threshold"), threshold_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "nonmaxSuppression"), nonmaxSuppression_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "type"), type_getter);

  target.Set("FASTDetector", FF::getFunction(ctor));
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  DetectorType::Init(env, exports);
#endif
};

void FASTDetector::New(const Napi::CallbackInfo& info) {
  NewBinding().construct(info);
}

#endif