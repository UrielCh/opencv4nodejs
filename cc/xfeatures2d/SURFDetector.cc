#include "opencv_modules.h"

#ifdef HAVE_OPENCV_XFEATURES2D

#include "SURFDetector.h"

Napi::FunctionReference SURFDetector::constructor;

Napi::Object SURFDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, SURFDetector::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FeatureDetector::Init(env, exports);
  constructor.Reset(ctor);

  ctor->SetClassName(Napi::String::New(env, "SURFDetector"));

  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "hessianThreshold"), hessianThreshold_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "nOctaves"), nOctaves_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "nOctaveLayers"), nOctaveLayers_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "extended"), extended_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "upright"), upright_getter);

  target.Set("SURFDetector", FF::getFunction(ctor));
};

void SURFDetector::New(const Napi::CallbackInfo& info) {
  constructorBinding<Constructor>(info);
}

#endif // HAVE_OPENCV_XFEATURES2D
