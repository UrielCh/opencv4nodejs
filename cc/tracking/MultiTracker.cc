#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "MultiTracker.h"

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

Napi::FunctionReference MultiTracker::constructor;

Napi::Object MultiTracker(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(MultiTracker::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "MultiTracker"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(ctor, "addMIL", MultiTracker::AddMIL);
  Nan::SetPrototypeMethod(ctor, "addBOOSTING", MultiTracker::AddBOOSTING);
  Nan::SetPrototypeMethod(ctor, "addMEDIANFLOW", MultiTracker::AddMEDIANFLOW);
  Nan::SetPrototypeMethod(ctor, "addTLD", MultiTracker::AddTLD);
  Nan::SetPrototypeMethod(ctor, "addKCF", MultiTracker::AddKCF);
#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
  Nan::SetPrototypeMethod(ctor, "addMOSSE", MultiTracker::AddTLD);
#endif
#if CV_VERSION_GREATER_EQUAL(3, 4, 1)
  Nan::SetPrototypeMethod(ctor, "addCSRT", MultiTracker::AddKCF);
#endif
  Nan::SetPrototypeMethod(ctor, "update", MultiTracker::Update);

  Nan::Set(target, FF::newString(env, "MultiTracker"), FF::getFunction(ctor));
};

void MultiTracker::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "MultiTracker::New");
  FF_ASSERT_CONSTRUCT_CALL();
  MultiTracker* self = new MultiTracker();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->setNativeObject(cv::makePtr<cv::legacy::MultiTracker>());
#else
  self->setNativeObject(cv::makePtr<cv::MultiTracker>());
#endif
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

void MultiTracker::AddMIL(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "MultiTracker::AddMIL");
  cv::Mat image;
  cv::Rect2d boundingBox;
  if (
      Mat::Converter::arg(0, &image, info) || Rect::Converter::arg(1, &boundingBox, info)) {
    return tryCatch.reThrow();
  }
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> type = cv::legacy::TrackerMIL::create();
#elif CV_VERSION_GREATER_EQUAL(3, 3, 0)
  cv::Ptr<cv::Tracker> type = cv::TrackerMIL::create();
#else
  const std::string type("MIL");
#endif
  bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
  info.GetReturnValue().Set(Nan::New(ret));
}

void MultiTracker::AddBOOSTING(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "MultiTracker::AddBOOSTING");
  cv::Mat image;
  cv::Rect2d boundingBox;
  if (
      Mat::Converter::arg(0, &image, info) || Rect::Converter::arg(1, &boundingBox, info)) {
    return tryCatch.reThrow();
  }
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> type = cv::legacy::TrackerBoosting::create();
#elif CV_VERSION_GREATER_EQUAL(3, 3, 0)
  cv::Ptr<cv::Tracker> type = cv::TrackerBoosting::create();
#else
  const std::string type("BOOSTING");
#endif
  bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
  info.GetReturnValue().Set(Nan::New(ret));
}

void MultiTracker::AddMEDIANFLOW(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "MultiTracker::AddMEDIANFLOW");
  cv::Mat image;
  cv::Rect2d boundingBox;
  if (
      Mat::Converter::arg(0, &image, info) || Rect::Converter::arg(1, &boundingBox, info)) {
    return tryCatch.reThrow();
  }
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> type = cv::legacy::TrackerMedianFlow::create();
#elif CV_VERSION_GREATER_EQUAL(3, 3, 0)
  cv::Ptr<cv::Tracker> type = cv::TrackerMedianFlow::create();
#else
  const std::string type("MEDIANFLOW");
#endif
  bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
  info.GetReturnValue().Set(Nan::New(ret));
}

void MultiTracker::AddTLD(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "MultiTracker::AddTLD");
  cv::Mat image;
  cv::Rect2d boundingBox;
  if (
      Mat::Converter::arg(0, &image, info) || Rect::Converter::arg(1, &boundingBox, info)) {
    return tryCatch.reThrow();
  }
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> type = cv::legacy::TrackerTLD::create();
#elif CV_VERSION_GREATER_EQUAL(3, 3, 0)
  cv::Ptr<cv::Tracker> type = cv::TrackerTLD::create();
#else
  const std::string type("TLD");
#endif
  bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
  info.GetReturnValue().Set(Nan::New(ret));
}

void MultiTracker::AddKCF(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "MultiTracker::AddKCF");
  cv::Mat image;
  cv::Rect2d boundingBox;
  if (
      Mat::Converter::arg(0, &image, info) || Rect::Converter::arg(1, &boundingBox, info)) {
    return tryCatch.reThrow();
  }
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> type = cv::legacy::TrackerKCF::create();
#elif CV_VERSION_GREATER_EQUAL(3, 3, 0)
  cv::Ptr<cv::Tracker> type = cv::TrackerKCF::create();
#else
  const std::string type("KCF");
#endif
  bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
  info.GetReturnValue().Set(Nan::New(ret));
}

void MultiTracker::Update(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "MultiTracker::Update");
  cv::Mat image;
  if (Mat::Converter::arg(0, &image, info)) {
    return tryCatch.reThrow();
  }

  std::vector<cv::Rect2d> rects;
  MultiTracker::unwrapSelf(info)->update(image, rects);
  info.GetReturnValue().Set(Rect::ArrayConverter::wrap(rects));
}
#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

void MultiTracker::AddMOSSE(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "MultiTracker::AddMOSSE");
  cv::Mat image;
  cv::Rect2d boundingBox;
  if (
      Mat::Converter::arg(0, &image, info) || Rect::Converter::arg(1, &boundingBox, info)) {
    return tryCatch.reThrow();
  }
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> type = cv::legacy::TrackerMOSSE::create();
#else
  cv::Ptr<cv::Tracker> type = cv::TrackerMOSSE::create();
#endif
  bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
  info.GetReturnValue().Set(Nan::New(ret));
}

#endif
#if CV_VERSION_GREATER_EQUAL(3, 4, 1)

void MultiTracker::AddCSRT(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "MultiTracker::AddCSRT");
  cv::Mat image;
  cv::Rect2d boundingBox;
  if (
      Mat::Converter::arg(0, &image, info) || Rect::Converter::arg(1, &boundingBox, info)) {
    return tryCatch.reThrow();
  }
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> type = cv::legacy::TrackerCSRT::create();
#else
  cv::Ptr<cv::Tracker> type = cv::TrackerCSRT::create();
#endif
  bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
  info.GetReturnValue().Set(Nan::New(ret));
}
#endif

#endif

#endif
