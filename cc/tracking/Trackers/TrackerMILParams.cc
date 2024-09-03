#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerMILParams.h"

Nan::Persistent<v8::FunctionTemplate> TrackerMILParams::constructor;

Napi::Object TrackerMILParams(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(TrackerMILParams::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "TrackerMILParams"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString(env, "samplerInitInRadius"), samplerInitInRadius_getter, samplerInitInRadius_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "samplerSearchWinSize"), samplerSearchWinSize_getter, samplerSearchWinSize_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "samplerTrackInRadius"), samplerTrackInRadius_getter, samplerTrackInRadius_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "samplerInitMaxNegNum"), samplerInitMaxNegNum_getter, samplerInitMaxNegNum_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "samplerTrackMaxPosNum"), samplerTrackMaxPosNum_getter, samplerTrackMaxPosNum_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "samplerTrackMaxNegNum"), samplerTrackMaxNegNum_getter, samplerTrackMaxNegNum_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "featureSetNumFeatures"), featureSetNumFeatures_getter, featureSetNumFeatures_setter);

  Nan::Set(target, FF::newString(env, "TrackerMILParams"), FF::getFunction(ctor));
};

void TrackerMILParams::New(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("TrackerMILParams::New");
  FF_ASSERT_CONSTRUCT_CALL();
  TrackerMILParams* self = new TrackerMILParams();
  self->self = cv::TrackerMIL::Params();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif
