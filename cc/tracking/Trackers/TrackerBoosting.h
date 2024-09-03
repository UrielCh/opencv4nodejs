#include "../Tracker.h"

#ifndef __FF_TRACKERBOOSTING_H__
#define __FF_TRACKERBOOSTING_H__

class TrackerBoosting : public Tracker {
public:
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::TrackerBoosting> tracker;
#else
  cv::Ptr<cv::TrackerBoosting> tracker;
#endif

static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

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
