#include "../Tracker.h"

#ifndef __FF_TRACKERMEDIANFLOW_H__
#define __FF_TRACKERMEDIANFLOW_H__

class TrackerMedianFlow : public Tracker {
public:
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::TrackerMedianFlow> tracker;
#else
  cv::Ptr<cv::TrackerMedianFlow> tracker;
#endif

static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  static Napi::FunctionReference constructor;;

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> getTracker(){
#else
  cv::Ptr<cv::Tracker> getTracker() {
#endif
      return tracker;
}
}
;

#endif
