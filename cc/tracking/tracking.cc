#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "./Trackers/TrackerBoosting.h"
#include "./Trackers/TrackerMIL.h"
#include "./Trackers/TrackerMedianFlow.h"
#include "./Trackers/TrackerTLD.h"
#include "tracking.h"

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
#include "./Trackers/TrackerKCF.h"
#include "MultiTracker.h"
#endif

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
#include "./Trackers/TrackerGOTURN.h"
#endif

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
#include "./Trackers/TrackerMOSSE.h"
#endif
#if CV_VERSION_GREATER_EQUAL(3, 4, 1)
#include "./Trackers/TrackerCSRT.h"
#endif

Napi::Object Tracking(Napi::Env env, Napi::Object exports) {
  TrackerBoosting::Init(env, exports);
  TrackerMedianFlow::Init(env, exports);
  TrackerMIL::Init(env, exports);
  TrackerTLD::Init(env, exports);

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
  TrackerKCF::Init(env, exports);
  MultiTracker::Init(env, exports);
  Napi::Object trackerKCFModes = Napi::Object::New(env);
  FF_SET_JS_PROP(trackerKCFModes, GRAY, Nan::New<v8::Integer>(cv::TrackerKCF::MODE::GRAY));
  FF_SET_JS_PROP(trackerKCFModes, CN, Nan::New<v8::Integer>(cv::TrackerKCF::MODE::CN));
  FF_SET_JS_PROP(trackerKCFModes, CUSTOM, Nan::New<v8::Integer>(cv::TrackerKCF::MODE::CUSTOM));
  Nan::Set(target, FF::newString(env, "trackerKCFModes"), trackerKCFModes);
#endif

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  TrackerGOTURN::Init(env, exports);
#endif

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
  TrackerMOSSE::Init(env, exports);
#endif
#if CV_VERSION_GREATER_EQUAL(3, 4, 1)
  TrackerCSRT::Init(env, exports);
#endif
};

#endif
