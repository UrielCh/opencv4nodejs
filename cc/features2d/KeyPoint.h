#include "Point2.h"
#include "macros.h"
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>

#ifndef FF_KEYPOINT_H_
#define FF_KEYPOINT_H_

class KeyPoint : public FF::ObjectWrap<KeyPoint, cv::KeyPoint> {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor;

  static const char* getClassName() {
    return "KeyPoint";
  }

  int localId = -1;

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  FF_GETTER_CUSTOM(localId, FF::IntConverter, localId);
  FF_ACCESSORS(pt, Point2::Converter);
  FF_ACCESSORS(angle, FF::FloatConverter);
  FF_ACCESSORS(class_id, FF::IntConverter);
  FF_ACCESSORS(response, FF::FloatConverter);
  FF_ACCESSORS(size, FF::FloatConverter);
  FF_ACCESSORS(octave, FF::IntConverter);
};

#endif