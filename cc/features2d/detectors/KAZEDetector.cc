#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "KAZEDetector.h"

Napi::FunctionReference KAZEDetector::constructor;

Napi::Object KAZEDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, KAZEDetector::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FeatureDetector::Init(env, exports);
  constructor.Reset(ctor);
  ctor->SetClassName(Napi::String::New(env, "KAZEDetector"));


  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "extended"), extended_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "upright"), upright_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "threshold"), threshold_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "nOctaves"), nOctaves_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "nOctaveLayers"), nOctaveLayers_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "diffusivity"), diffusivity_getter);

  target.Set("KAZEDetector", FF::getFunction(ctor));
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  DiffusivityType::Init(env, exports);
#endif
};

void KAZEDetector::New(const Napi::CallbackInfo& info) {
  NewBinding().construct(info);
}

#endif