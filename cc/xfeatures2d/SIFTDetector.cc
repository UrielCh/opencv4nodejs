#include "opencv_modules.h"

#ifdef HAVE_OPENCV_XFEATURES2D

#include "SIFTDetector.h"

Napi::FunctionReference SIFTDetector::constructor;

Napi::Object SIFTDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, SIFTDetector::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("SIFTDetector").ToLocalChecked());

  Nan::SetAccessor(instanceTemplate, Nan::New("nFeatures").ToLocalChecked(), nFeatures_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("nOctaveLayers").ToLocalChecked(), nOctaveLayers_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("contrastThreshold").ToLocalChecked(), contrastThreshold_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("edgeThreshold").ToLocalChecked(), edgeThreshold_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("sigma").ToLocalChecked(), sigma_getter);

  target.Set("SIFTDetector", FF::getFunction(ctor));
};

void SIFTDetector::New(const Napi::CallbackInfo& info) {
  constructorBinding<Constructor>(info);
}

#endif // HAVE_OPENCV_XFEATURES2D
