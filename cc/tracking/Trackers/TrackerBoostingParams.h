#include "macros.h"
#include <opencv2/tracking.hpp>
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
#include <opencv2/tracking/tracking_legacy.hpp>
#endif

#ifndef __FF_TRACKERBOOSTINGPARAMS_H__
#define __FF_TRACKERBOOSTINGPARAMS_H__

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
class TrackerBoostingParams : public FF::ObjectWrap<TrackerBoostingParams, cv::legacy::TrackerBoosting::Params> {
#else
class TrackerBoostingParams : public FF::ObjectWrap<TrackerBoostingParams, cv::TrackerBoosting::Params> {
#endif
public:
  static Napi::FunctionReference constructor;

  static const char* getClassName() {
    return "TrackerBoostingParams";
  }

static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  FF_ACCESSORS(numClassifiers, FF::IntConverter);
  FF_ACCESSORS(samplerOverlap, FF::FloatConverter);
  FF_ACCESSORS(samplerSearchFactor, FF::FloatConverter);
  FF_ACCESSORS(iterationInit, FF::IntConverter);
  FF_ACCESSORS(featureSetNumFeatures, FF::IntConverter);
};

#endif
