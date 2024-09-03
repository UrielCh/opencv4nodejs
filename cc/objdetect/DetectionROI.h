#include "NativeNodeUtils.h"
#include "Point.h"
#include "macros.h"
#include <opencv2/objdetect.hpp>

#ifndef __FF_DETECTIONROI_H__
#define __FF_DETECTIONROI_H__

class DetectionROI : public FF::ObjectWrap<DetectionROI, cv::DetectionROI> {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor;

  static const char* getClassName() {
    return "DetectionROI";
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  FF_ACCESSORS(scale, FF::DoubleConverter);
  FF_ACCESSORS(locations, Point2::ArrayWithCastConverter<cv::Point2i>);
  FF_ACCESSORS(confidences, FF::DoubleArrayConverter);
};

#endif