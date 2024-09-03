#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerMILParams.h"

Napi::FunctionReference TrackerMILParams::constructor;

Napi::Object TrackerMILParams(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, TrackerMILParams::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "TrackerMILParams"));


  Napi::SetAccessor(instanceTemplate, FF::newString(env, "samplerInitInRadius"), samplerInitInRadius_getter, samplerInitInRadius_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "samplerSearchWinSize"), samplerSearchWinSize_getter, samplerSearchWinSize_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "samplerTrackInRadius"), samplerTrackInRadius_getter, samplerTrackInRadius_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "samplerInitMaxNegNum"), samplerInitMaxNegNum_getter, samplerInitMaxNegNum_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "samplerTrackMaxPosNum"), samplerTrackMaxPosNum_getter, samplerTrackMaxPosNum_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "samplerTrackMaxNegNum"), samplerTrackMaxNegNum_getter, samplerTrackMaxNegNum_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "featureSetNumFeatures"), featureSetNumFeatures_getter, featureSetNumFeatures_setter);

  (target).Set("TrackerMILParams", FF::getFunction(ctor));
};

void TrackerMILParams::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "TrackerMILParams::New");
  FF_ASSERT_CONSTRUCT_CALL();
  TrackerMILParams* self = new TrackerMILParams();
  self->self = cv::TrackerMIL::Params();
  self->Wrap(info.Holder());
  return info.Holder();
};

#endif
