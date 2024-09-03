#include "../Tracker.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

#ifndef __FF_TRACKERMOSSE_H__
#define __FF_TRACKERMOSSE_H__

class TrackerMOSSE : public Tracker {
public:
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::TrackerMOSSE> tracker;
#else
  cv::Ptr<cv::TrackerMOSSE> tracker;
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

#endif
