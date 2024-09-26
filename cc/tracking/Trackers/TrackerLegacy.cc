#include "opencv_modules.h"

/**
 * @brief merge legacy tracker classes into one file
 * - TrackerCSRT
 * - TrackerKCF
 * - TrackerMedianFlow
 * - TrackerMIL
 * - TrackerMOSSE
 * - TrackerTLD
 * 
 * those classes will not evove in the future, so they are considered legacy
 */

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerLegacy.h"
#include "TrackerLegacyParams.h"

Nan::Persistent<v8::FunctionTemplate> TrackerBoosting::constructor;

NAN_MODULE_INIT(TrackerBoosting::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerBoosting::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();
  Tracker::Init(ctor);
  TrackerBoostingParams::Init(target);
  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("TrackerBoosting"));
  instanceTemplate->SetInternalFieldCount(1);
  Nan::Set(target, FF::newString("TrackerBoosting"), FF::getFunction(ctor));
};

NAN_METHOD(TrackerBoosting::New) {
  FF::TryCatch tryCatch("TrackerBoosting::New");
  FF_ASSERT_CONSTRUCT_CALL();

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::legacy::TrackerBoosting::Params params;
#else // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::TrackerBoosting::Params params;
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  if (TrackerBoostingParams::Converter::optArg(0, &params, info)) {
    return tryCatch.reThrow();
  }

  TrackerBoosting* self = new TrackerBoosting();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->tracker = cv::legacy::TrackerBoosting::create(params);
#elif CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->tracker = cv::TrackerBoosting::create(params);
#else // CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->tracker = cv::TrackerBoosting::createTracker(params);
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};


#if CV_VERSION_GREATER_EQUAL(3, 4, 1)
Nan::Persistent<v8::FunctionTemplate> TrackerCSRT::constructor;

NAN_MODULE_INIT(TrackerCSRT::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerCSRT::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();
  Tracker::Init(ctor);
  TrackerCSRTParams::Init(target);
  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("TrackerCSRT"));
  instanceTemplate->SetInternalFieldCount(1);
  Nan::Set(target, FF::newString("TrackerCSRT"), FF::getFunction(ctor));
};

NAN_METHOD(TrackerCSRT::New) {
  FF::TryCatch tryCatch("TrackerCSRT::New");
  FF_ASSERT_CONSTRUCT_CALL();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::legacy::TrackerCSRT::Params params;
#else // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::TrackerCSRT::Params params;
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  if (TrackerCSRTParams::Converter::optArg(0, &params, info)) {
    return tryCatch.reThrow();
  }
  TrackerCSRT* self = new TrackerCSRT();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->tracker = cv::legacy::TrackerCSRT::create(params);
#else // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->tracker = cv::TrackerCSRT::create(params);
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};
#endif // CV_VERSION_GREATER_EQUAL(3, 4, 1)

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
Nan::Persistent<v8::FunctionTemplate> TrackerKCF::constructor;

NAN_MODULE_INIT(TrackerKCF::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerKCF::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();
  Tracker::Init(ctor);
  TrackerKCFParams::Init(target);
  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("TrackerKCF"));
  instanceTemplate->SetInternalFieldCount(1);
  Nan::Set(target, FF::newString("TrackerKCF"), FF::getFunction(ctor));
};

NAN_METHOD(TrackerKCF::New) {
  FF::TryCatch tryCatch("TrackerKCF::New");
  FF_ASSERT_CONSTRUCT_CALL();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::legacy::TrackerKCF::Params params;
#else // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::TrackerKCF::Params params;
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  if (TrackerKCFParams::Converter::optArg(0, &params, info)) {
    return tryCatch.reThrow();
  }

  TrackerKCF* self = new TrackerKCF();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->tracker = cv::legacy::TrackerKCF::create(params);
#elif CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->tracker = cv::TrackerKCF::create(params);
#else // CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->tracker = cv::TrackerKCF::createTracker(params);
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};
#endif // CV_VERSION_GREATER_EQUAL(3, 1, 0)

Nan::Persistent<v8::FunctionTemplate> TrackerMedianFlow::constructor;
NAN_MODULE_INIT(TrackerMedianFlow::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerMedianFlow::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();
  Tracker::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("TrackerMedianFlow"));
  instanceTemplate->SetInternalFieldCount(1);
  Nan::Set(target, FF::newString("TrackerMedianFlow"), FF::getFunction(ctor));
};

NAN_METHOD(TrackerMedianFlow::New) {
  FF::TryCatch tryCatch("TrackerMedianFlow::New");
  FF_ASSERT_CONSTRUCT_CALL();

  TrackerMedianFlow* self = new TrackerMedianFlow();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::legacy::TrackerMedianFlow::Params params;
#else // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::TrackerMedianFlow::Params params;
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  if (FF::hasArg(info, 0) && FF::IntConverterImpl::assertType(info[0])) {
    params.pointsInGrid = info[0]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value();
  }

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->tracker = cv::legacy::TrackerMedianFlow::create(params);
#elif CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->tracker = cv::TrackerMedianFlow::create(params);
#else // CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->tracker = cv::TrackerMedianFlow::createTracker(params);
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

Nan::Persistent<v8::FunctionTemplate> TrackerMIL::constructor;

NAN_MODULE_INIT(TrackerMIL::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerMIL::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();
  Tracker::Init(ctor);
  TrackerMILParams::Init(target);
  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("TrackerMIL"));
  instanceTemplate->SetInternalFieldCount(1);
  Nan::Set(target, FF::newString("TrackerMIL"), FF::getFunction(ctor));
};

NAN_METHOD(TrackerMIL::New) {
  FF::TryCatch tryCatch("TrackerMIL::New");
  FF_ASSERT_CONSTRUCT_CALL();

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::legacy::TrackerMIL::Params params;
#else // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::TrackerMIL::Params params;
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
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

// Ensure that this code is only compiled if OpenCV is 3.4.0 or greater
#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
Nan::Persistent<v8::FunctionTemplate> TrackerMOSSE::constructor;
NAN_MODULE_INIT(TrackerMOSSE::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerMOSSE::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();
  Tracker::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("TrackerMOSSE"));
  instanceTemplate->SetInternalFieldCount(1);
  Nan::Set(target, FF::newString("TrackerMOSSE"), FF::getFunction(ctor));
};

NAN_METHOD(TrackerMOSSE::New) {
  FF::TryCatch tryCatch("TrackerMOSSE::New");
  FF_ASSERT_CONSTRUCT_CALL();
  TrackerMOSSE* self = new TrackerMOSSE();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->tracker = cv::legacy::TrackerMOSSE::create();
#else // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->tracker = cv::TrackerMOSSE::create();
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};
#endif // CV_VERSION_GREATER_EQUAL(3, 4, 0)

Nan::Persistent<v8::FunctionTemplate> TrackerTLD::constructor;

NAN_MODULE_INIT(TrackerTLD::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerTLD::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();
  Tracker::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("TrackerTLD"));
  instanceTemplate->SetInternalFieldCount(1);
  Nan::Set(target, FF::newString("TrackerTLD"), FF::getFunction(ctor));
};

NAN_METHOD(TrackerTLD::New) {
  FF::TryCatch tryCatch("TrackerTLD::New");
  FF_ASSERT_CONSTRUCT_CALL();
  TrackerTLD* self = new TrackerTLD();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->tracker = cv::legacy::TrackerTLD::create();
#elif CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->tracker = cv::TrackerTLD::create();
#else // CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->tracker = cv::TrackerTLD::createTracker();
#endif // CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif // HAVE_OPENCV_TRACKING
