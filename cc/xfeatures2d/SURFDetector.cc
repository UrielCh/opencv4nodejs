#include "opencv_modules.h"

#ifdef HAVE_OPENCV_XFEATURES2D

#include "SURFDetector.h"

Napi::FunctionReference SURFDetector::constructor;

Napi::Object SURFDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(SURFDetector::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("SURFDetector").ToLocalChecked());

  Nan::SetAccessor(instanceTemplate, Nan::New("hessianThreshold").ToLocalChecked(), hessianThreshold_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("nOctaves").ToLocalChecked(), nOctaves_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("nOctaveLayers").ToLocalChecked(), nOctaveLayers_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("extended").ToLocalChecked(), extended_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("upright").ToLocalChecked(), upright_getter);

  target.Set("SURFDetector", FF::getFunction(ctor));
};

void SURFDetector::New(const Napi::CallbackInfo& info) {
  constructorBinding<Constructor>(info);
}

#endif // HAVE_OPENCV_XFEATURES2D
