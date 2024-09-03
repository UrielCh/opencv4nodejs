#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerBoostingParams.h"

Napi::FunctionReference TrackerBoostingParams::constructor;

Napi::Object TrackerBoostingParams(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, TrackerBoostingParams::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "TrackerBoostingParams"));


  Napi::SetAccessor(instanceTemplate, FF::newString(env, "numClassifiers"), numClassifiers_getter, numClassifiers_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "samplerOverlap"), samplerOverlap_getter, samplerOverlap_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "samplerSearchFactor"), samplerSearchFactor_getter, samplerSearchFactor_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "iterationInit"), iterationInit_getter, iterationInit_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "featureSetNumFeatures"), featureSetNumFeatures_getter, featureSetNumFeatures_setter);

  (target).Set("TrackerBoostingParams", FF::getFunction(ctor));
};

void TrackerBoostingParams::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "TrackerBoostingParams::New");
  FF_ASSERT_CONSTRUCT_CALL();
  TrackerBoostingParams* self = new TrackerBoostingParams();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->self = cv::legacy::TrackerBoosting::Params();
#else
  self->self = cv::TrackerBoosting::Params();
#endif
  self->Wrap(info.Holder());
  return info.Holder();
};

#endif
