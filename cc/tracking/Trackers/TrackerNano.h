#include "../Tracker.h"

// Ensure that TrackerNano is only defined for OpenCV 4.7.0 or greater
#if CV_VERSION_GREATER_EQUAL(4, 7, 0)

#ifndef __FF_TRACKERNANO_H__
#define __FF_TRACKERNANO_H__

class TrackerNano : public FF::ObjectWrapBase<TrackerNano>, public Nan::ObjectWrap {
public:
  cv::Ptr<cv::TrackerNano> tracker;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  static NAN_METHOD(Init);
  static NAN_METHOD(Update);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

  cv::Ptr<cv::Tracker> getTracker() {
    return tracker;
  }
};
#endif

#endif
