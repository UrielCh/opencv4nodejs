#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerMIL.h"
#include "TrackerMILParams.h"

Napi::FunctionReference TrackerMIL::constructor;

Napi::Object TrackerMIL(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(TrackerMIL::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  Tracker::Init(ctor);
  TrackerMILParams::Init(env, exports);

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "TrackerMIL"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::Set(target, FF::newString(env, "TrackerMIL"), FF::getFunction(ctor));
};

void TrackerMIL::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "TrackerMIL::New");
  FF_ASSERT_CONSTRUCT_CALL();

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::legacy::TrackerMIL::Params params;
#else
  cv::TrackerMIL::Params params;
#endif
  if (TrackerMILParams::Converter::optArg(0, &params, info)) {
    return tryCatch.reThrow();
  }

  TrackerMIL* self = new TrackerMIL();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->tracker = cv::legacy::TrackerMIL::create(params);
#elif CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->tracker = cv::TrackerMIL::create(params);
#else
  self->tracker = cv::TrackerMIL::createTracker(params);
#endif
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif
