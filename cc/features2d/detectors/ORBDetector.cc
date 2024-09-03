#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "ORBDetector.h"

Nan::Persistent<v8::FunctionTemplate> ORBDetector::constructor;

Napi::Object ORBDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(ORBDetector::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("ORBDetector").ToLocalChecked());

  Nan::SetAccessor(instanceTemplate, Nan::New("maxFeatures").ToLocalChecked(), maxFeatures_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("scaleFactor").ToLocalChecked(), scaleFactor_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("nLevels").ToLocalChecked(), nLevels_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("edgeThreshold").ToLocalChecked(), edgeThreshold_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("firstLevel").ToLocalChecked(), firstLevel_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("WTA_K").ToLocalChecked(), WTA_K_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("scoreType").ToLocalChecked(), scoreType_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("patchSize").ToLocalChecked(), patchSize_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("fastThreshold").ToLocalChecked(), fastThreshold_getter);

  target.Set("ORBDetector", FF::getFunction(ctor));
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  ScoreType::Init(env, exports);
#endif
};

void ORBDetector::New(const Napi::CallbackInfo& info) {
  NewBinding().construct(info);
}

#endif