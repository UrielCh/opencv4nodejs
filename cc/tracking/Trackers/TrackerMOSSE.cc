#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerMOSSE.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

Napi::FunctionReference TrackerMOSSE::constructor;

Napi::Object TrackerMOSSE(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, TrackerMOSSE::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  Tracker::Init(env, exports);

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "TrackerMOSSE"));


  (target).Set("TrackerMOSSE", FF::getFunction(ctor));
};

void TrackerMOSSE::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "TrackerMOSSE::New");
  FF_ASSERT_CONSTRUCT_CALL();

  TrackerMOSSE* self = new TrackerMOSSE();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->tracker = cv::legacy::TrackerMOSSE::create();
#else
  self->tracker = cv::TrackerMOSSE::create();
#endif
  self->Wrap(info.Holder());
  return info.Holder();
};

#endif

#endif
