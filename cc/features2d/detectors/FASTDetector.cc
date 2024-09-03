#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "FASTDetector.h"

Napi::FunctionReference FASTDetector::constructor;

Napi::Object FASTDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(FASTDetector::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(Nan::New("FASTDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, Nan::New("threshold").ToLocalChecked(), threshold_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("nonmaxSuppression").ToLocalChecked(), nonmaxSuppression_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("type").ToLocalChecked(), type_getter);

  target.Set("FASTDetector", FF::getFunction(ctor));
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  DetectorType::Init(env, exports);
#endif
};

void FASTDetector::New(const Napi::CallbackInfo& info) {
  NewBinding().construct(info);
}

#endif