#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "AKAZEDetector.h"

Napi::FunctionReference AKAZEDetector::constructor;

Napi::Object AKAZEDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, AKAZEDetector::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FeatureDetector::Init(env, exports);
  constructor.Reset(ctor);
  ctor->SetClassName(Napi::String::New(env, "AKAZEDetector"));


  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "descriptorType"), descriptorType_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "descriptorSize"), descriptorSize_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "descriptorChannels"), descriptorChannels_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "threshold"), threshold_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "nOctaves"), nOctaves_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "nOctaveLayers"), nOctaveLayers_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "diffusivity"), diffusivity_getter);

  target.Set("AKAZEDetector", FF::getFunction(ctor));
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  DescriptorType::Init(env, exports);
#endif
};

void AKAZEDetector::New(const Napi::CallbackInfo& info) {
  NewBinding().construct(info);
}

#endif