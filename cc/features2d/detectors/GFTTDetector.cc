#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "GFTTDetector.h"

Napi::FunctionReference GFTTDetector::constructor;

Napi::Object GFTTDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, GFTTDetector::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(Nan::New("GFTTDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, Nan::New("maxFeatures").ToLocalChecked(), maxFeatures_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("qualityLevel").ToLocalChecked(), qualityLevel_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("minDistance").ToLocalChecked(), minDistance_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("blockSize").ToLocalChecked(), blockSize_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("harrisDetector").ToLocalChecked(), harrisDetector_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("k").ToLocalChecked(), k_getter);

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
  info.GetReturnValue().Set(info.Holder());
}

#endif
