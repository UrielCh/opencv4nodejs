#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "GFTTDetector.h"

Napi::FunctionReference GFTTDetector::constructor;

Napi::Object GFTTDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, GFTTDetector::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(Napi::String::New(env, "GFTTDetector"));


  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "maxFeatures"), maxFeatures_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "qualityLevel"), qualityLevel_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "minDistance"), minDistance_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "blockSize"), blockSize_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "harrisDetector"), harrisDetector_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "k"), k_getter);

  target.Set("GFTTDetector", FF::getFunction(ctor));
};

void GFTTDetector::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "GFTTDetector::New");
  FF_ASSERT_CONSTRUCT_CALL();
  GFTTDetector::NewWorker worker;

  if (worker.applyUnwrappers(info)) {
    return tryCatch.reThrow();
  }

  GFTTDetector* self = new GFTTDetector();
  self->self = cv::GFTTDetector::create(worker.maxFeatures, worker.qualityLevel, worker.minDistance, worker.blockSize, worker.harrisDetector, worker.k);
  self->Wrap(info.Holder());
  return info.Holder();
}

#endif
