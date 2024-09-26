#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "MultiTracker.h"

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

Nan::Persistent<v8::FunctionTemplate> MultiTracker::constructor;

NAN_MODULE_INIT(MultiTracker::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(MultiTracker::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("MultiTracker"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(ctor, "addMIL", MultiTracker::AddMIL);
  Nan::SetPrototypeMethod(ctor, "addBOOSTING", MultiTracker::AddBOOSTING);
  Nan::SetPrototypeMethod(ctor, "addMEDIANFLOW", MultiTracker::AddMEDIANFLOW);
  Nan::SetPrototypeMethod(ctor, "addTLD", MultiTracker::AddTLD);
  Nan::SetPrototypeMethod(ctor, "addKCF", MultiTracker::AddKCF);
#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
  Nan::SetPrototypeMethod(ctor, "addMOSSE", MultiTracker::AddTLD);
#endif // CV_VERSION_GREATER_EQUAL(3, 4, 0)
#if CV_VERSION_GREATER_EQUAL(3, 4, 1)
  Nan::SetPrototypeMethod(ctor, "addCSRT", MultiTracker::AddKCF);
#endif // CV_VERSION_GREATER_EQUAL(3, 4, 1)
  Nan::SetPrototypeMethod(ctor, "update", MultiTracker::Update);

  Nan::Set(target, FF::newString("MultiTracker"), FF::getFunction(ctor));
};

NAN_METHOD(MultiTracker::New) {
  FF::TryCatch tryCatch("MultiTracker::New");
  FF_ASSERT_CONSTRUCT_CALL();
  MultiTracker* self = new MultiTracker();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->setNativeObject(cv::makePtr<cv::legacy::MultiTracker>());
#else // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->setNativeObject(cv::makePtr<cv::MultiTracker>());
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

NAN_METHOD(MultiTracker::AddMIL) {
  FF::TryCatch tryCatch("MultiTracker::AddMIL");
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
#else // CV_VERSION_GREATER_EQUAL(3, 3, 0)
  const std::string type("MIL");
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
  info.GetReturnValue().Set(Nan::New(ret));
}

NAN_METHOD(MultiTracker::AddBOOSTING) {
  FF::TryCatch tryCatch("MultiTracker::AddBOOSTING");
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
#else // CV_VERSION_GREATER_EQUAL(3, 3, 0)
  const std::string type("BOOSTING");
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
  info.GetReturnValue().Set(Nan::New(ret));
}

NAN_METHOD(MultiTracker::AddMEDIANFLOW) {
  FF::TryCatch tryCatch("MultiTracker::AddMEDIANFLOW");
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
#else // CV_VERSION_GREATER_EQUAL(3, 3, 0)
  const std::string type("MEDIANFLOW");
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
  info.GetReturnValue().Set(Nan::New(ret));
}

NAN_METHOD(MultiTracker::AddTLD) {
  FF::TryCatch tryCatch("MultiTracker::AddTLD");
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
#else // CV_VERSION_GREATER_EQUAL(3, 3, 0)
  const std::string type("TLD");
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
  info.GetReturnValue().Set(Nan::New(ret));
}

NAN_METHOD(MultiTracker::AddKCF) {
  FF::TryCatch tryCatch("MultiTracker::AddKCF");
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
#else // CV_VERSION_GREATER_EQUAL(3, 3, 0)
  const std::string type("KCF");
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
  info.GetReturnValue().Set(Nan::New(ret));
}

NAN_METHOD(MultiTracker::Update) {
  FF::TryCatch tryCatch("MultiTracker::Update");
  cv::Mat image;
  if (Mat::Converter::arg(0, &image, info)) {
    return tryCatch.reThrow();
  }

  std::vector<cv::Rect2d> rects;
  MultiTracker::unwrapSelf(info)->update(image, rects);
  info.GetReturnValue().Set(Rect::ArrayConverter::wrap(rects));
}

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

NAN_METHOD(MultiTracker::AddMOSSE) {
  FF::TryCatch tryCatch("MultiTracker::AddMOSSE");
  cv::Mat image;
  cv::Rect2d boundingBox;
  if (
      Mat::Converter::arg(0, &image, info) || Rect::Converter::arg(1, &boundingBox, info)) {
    return tryCatch.reThrow();
  }
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> type = cv::legacy::TrackerMOSSE::create();
#else // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::Tracker> type = cv::TrackerMOSSE::create();
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
  info.GetReturnValue().Set(Nan::New(ret));
}
#endif // CV_VERSION_GREATER_EQUAL(3, 4, 0)

#if CV_VERSION_GREATER_EQUAL(3, 4, 1)

NAN_METHOD(MultiTracker::AddCSRT) {
  FF::TryCatch tryCatch("MultiTracker::AddCSRT");
  cv::Mat image;
  cv::Rect2d boundingBox;
  if (
      Mat::Converter::arg(0, &image, info) || Rect::Converter::arg(1, &boundingBox, info)) {
    return tryCatch.reThrow();
  }
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> type = cv::legacy::TrackerCSRT::create();
#else // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::Tracker> type = cv::TrackerCSRT::create();
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  bool ret = MultiTracker::unwrapSelf(info)->add(type, image, boundingBox);
  info.GetReturnValue().Set(Nan::New(ret));
}
#endif // CV_VERSION_GREATER_EQUAL(3, 4, 1)

#endif // CV_VERSION_GREATER_EQUAL(3, 1, 0)

#endif // HAVE_OPENCV_TRACKING
