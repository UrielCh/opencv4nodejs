#include "opencv_modules.h"

#ifdef HAVE_OPENCV_XFEATURES2D

#include "SIFTDetector.h"

Napi::FunctionReference SIFTDetector::constructor;

Napi::Object SIFTDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, SIFTDetector::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FeatureDetector::Init(env, exports);
  constructor.Reset(ctor);

  ctor->SetClassName(Napi::String::New(env, "SIFTDetector"));

  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "nFeatures"), nFeatures_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "nOctaveLayers"), nOctaveLayers_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "contrastThreshold"), contrastThreshold_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "edgeThreshold"), edgeThreshold_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "sigma"), sigma_getter);

  target.Set("SIFTDetector", FF::getFunction(ctor));
};

void SIFTDetector::New(const Napi::CallbackInfo& info) {
  constructorBinding<Constructor>(info);
}

#endif // HAVE_OPENCV_XFEATURES2D
