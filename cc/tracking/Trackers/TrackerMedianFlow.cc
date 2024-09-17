#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerMedianFlow.h"

Napi::FunctionReference TrackerMedianFlow::constructor;

Napi::Object TrackerMedianFlow(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, TrackerMedianFlow::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  Tracker::Init(env, exports);

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "TrackerMedianFlow"));


  (target).Set("TrackerMedianFlow", FF::getFunction(ctor));
};

void TrackerMedianFlow::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "TrackerMedianFlow::New");
  FF_ASSERT_CONSTRUCT_CALL();

  TrackerMedianFlow* self = new TrackerMedianFlow();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::legacy::TrackerMedianFlow::Params params;
#else
  cv::TrackerMedianFlow::Params params;
#endif
  if (FF::hasArg(info, 0) && FF::IntConverterImpl::assertType(info[0])) {
    params.pointsInGrid = info[0].As<Napi::Number>().Int32Value();
  }

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->tracker = cv::legacy::TrackerMedianFlow::create(params);
#elif CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->tracker = cv::TrackerMedianFlow::create(params);
#else
  self->tracker = cv::TrackerMedianFlow::createTracker(params);
#endif

  self->Wrap(info.Holder());
  return info.Holder();
};

#endif
