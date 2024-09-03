#include "../Tracker.h"

#ifndef __FF_TRACKERMIL_H__
#define __FF_TRACKERMIL_H__

class TrackerMIL : public Tracker {
public:
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::TrackerMIL> tracker;
#else
  cv::Ptr<cv::TrackerMIL> tracker;
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
