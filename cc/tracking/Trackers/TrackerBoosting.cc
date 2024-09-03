#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerBoosting.h"
#include "TrackerBoostingParams.h"

Napi::FunctionReference TrackerBoosting::constructor;

Napi::Object TrackerBoosting(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(TrackerBoosting::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  Tracker::Init(ctor);
  TrackerBoostingParams::Init(env, exports);

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "TrackerBoosting"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::Set(target, FF::newString(env, "TrackerBoosting"), FF::getFunction(ctor));
};

void TrackerBoosting::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "TrackerBoosting::New");
  FF_ASSERT_CONSTRUCT_CALL();

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::legacy::TrackerBoosting::Params params;
#else
  cv::TrackerBoosting::Params params;
#endif
  if (TrackerBoostingParams::Converter::optArg(0, &params, info)) {
    return tryCatch.reThrow();
  }

  TrackerBoosting* self = new TrackerBoosting();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->tracker = cv::legacy::TrackerBoosting::create(params);
#elif CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->tracker = cv::TrackerBoosting::create(params);
#else
  self->tracker = cv::TrackerBoosting::createTracker(params);
#endif
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif
