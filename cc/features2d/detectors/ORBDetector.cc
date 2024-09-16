#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "ORBDetector.h"

Napi::FunctionReference ORBDetector::constructor;

Napi::Object ORBDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, ORBDetector::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FeatureDetector::Init(env, exports);
  constructor.Reset(ctor);

  ctor->SetClassName(Napi::String::New(env, "ORBDetector"));

  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "maxFeatures"), maxFeatures_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "scaleFactor"), scaleFactor_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "nLevels"), nLevels_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "edgeThreshold"), edgeThreshold_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "firstLevel"), firstLevel_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "WTA_K"), WTA_K_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "scoreType"), scoreType_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "patchSize"), patchSize_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "fastThreshold"), fastThreshold_getter);

  target.Set("ORBDetector", FF::getFunction(ctor));
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  ScoreType::Init(env, exports);
#endif
};

void ORBDetector::New(const Napi::CallbackInfo& info) {
  NewBinding().construct(info);
}

#endif