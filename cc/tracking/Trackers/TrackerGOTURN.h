#include "../Tracker.h"

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)

#ifndef __FF_TRACKERGOTURN_H__
#define __FF_TRACKERGOTURN_H__

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
class TrackerGOTURN : public FF::ObjectWrapBase<TrackerGOTURN>, public Napi::ObjectWrap<TrackerGOTURN> {
#else
class TrackerGOTURN : public Tracker {
#endif
public:
  cv::Ptr<cv::TrackerGOTURN> tracker;

static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  static void Clear(const Napi::CallbackInfo& info);
  static void Init(const Napi::CallbackInfo& info);
  static void Update(const Napi::CallbackInfo& info);
  static void GetModel(const Napi::CallbackInfo& info);
#endif
  static Napi::FunctionReference constructor;;

  cv::Ptr<cv::Tracker> getTracker() {
    return tracker;
  }
};

#endif

#endif
