#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerNano.h"

// Ensure that this code is only compiled if OpenCV is 4.7.0 or greater
#if CV_VERSION_GREATER_EQUAL(4, 7, 0)

Nan::Persistent<v8::FunctionTemplate> TrackerNano::constructor;

NAN_MODULE_INIT(TrackerNano::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerNano::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  Nan::SetPrototypeMethod(ctor, "init", TrackerNano::Init);
  Nan::SetPrototypeMethod(ctor, "update", TrackerNano::Update);

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("TrackerNano"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::Set(target, FF::newString("TrackerNano"), FF::getFunction(ctor));
};


NAN_METHOD(TrackerNano::Init) {
  FF::TryCatch tryCatch("TrackerNano::Init");
  cv::Mat image;
  cv::Rect2d boundingBox;

  // Check if the arguments are correctly passed
  if (Mat::Converter::arg(0, &image, info) || Rect::Converter::arg(1, &boundingBox, info)) {
    return tryCatch.reThrow();
  }

  try {
    TrackerNano::unwrapThis(info)->getTracker()->init(image, boundingBox);
    
    // If no error is thrown, return true
    info.GetReturnValue().Set(Nan::True());
  } catch (const std::exception& e) {
    return tryCatch.throwError(e.what());
  }
}


NAN_METHOD(TrackerNano::Update) {
  FF::TryCatch tryCatch("TrackerNano::Update");
  cv::Mat image;
  if (Mat::Converter::arg(0, &image, info)) {
    return tryCatch.reThrow();
  }

  cv::Rect rect;
  bool ret = false;

  try {
    ret = TrackerNano::unwrapThis(info)->getTracker()->update(image, rect);
  } catch (std::exception& e) {
    return tryCatch.throwError(e.what());
  }

  if (ret) {
    info.GetReturnValue().Set(Rect::Converter::wrap(rect));
  } else {
    info.GetReturnValue().Set(Nan::Null());
  }
}

NAN_METHOD(TrackerNano::New) {
  FF::TryCatch tryCatch("TrackerNano::New");
  FF_ASSERT_CONSTRUCT_CALL();

  // Default model paths
  std::string backboneModelPath = "backbone.onnx";
  std::string neckheadModelPath = "neckhead.onnx";

  // Check if the user passed model paths as arguments
  if (info.Length() > 0) {
    if (FF::StringConverter::arg(0, &backboneModelPath, info)) {
      return tryCatch.reThrow();
    }
  }

  if (info.Length() > 1) {
    if (FF::StringConverter::arg(1, &neckheadModelPath, info)) {
      return tryCatch.reThrow();
    }
  }

  // Initialize TrackerNano with provided or default models
  TrackerNano* self = new TrackerNano();

  // Create tracker with provided ONNX models
  cv::TrackerNano::Params params;
  params.backbone = backboneModelPath;
  params.neckhead = neckheadModelPath;

  // Create the tracker instance with these parameters
  self->tracker = cv::TrackerNano::create(params);

  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

#endif

#endif
