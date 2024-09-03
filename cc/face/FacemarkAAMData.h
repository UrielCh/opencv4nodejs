#include "NativeNodeUtils.h"
#include "Point2.h"
#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/face.hpp>

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

#ifndef __FF_FACEMARKAAMDATA_H__
#define __FF_FACEMARKAAMDATA_H__

class FacemarkAAMData : public FF::ObjectWrap<FacemarkAAMData, cv::face::FacemarkAAM::Data> {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor;

  static const char* getClassName() {
    return "FacemarkAAMData";
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  FF_ACCESSORS(s0, Point2::ArrayWithCastConverter<cv::Point2f>);
};

#endif

#endif
