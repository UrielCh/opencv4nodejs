#include "../Tracker.h"

/**
 * @brief merge legacy tracker classes into one file
 * - TrackerCSRT
 * - TrackerKCF
 * - TrackerMedianFlow
 * - TrackerMIL
 * - TrackerMOSSE
 * - TrackerTLD
 * 
 * those classes will not evove in the future, so they are considered legacy
 */

#ifndef __FF_TRACKERLEGACY_H__
#define __FF_TRACKERLEGACY_H__


class TrackerBoosting : public Tracker {
public:
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::TrackerBoosting> tracker;
#else
  cv::Ptr<cv::TrackerBoosting> tracker;
#endif
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  static Nan::Persistent<v8::FunctionTemplate> constructor;
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> getTracker()
#else
  cv::Ptr<cv::Tracker> getTracker() 
#endif
  { return tracker; }
};

#if CV_VERSION_GREATER_EQUAL(3, 4, 1)
class TrackerCSRT : public Tracker {
public:
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::TrackerCSRT> tracker;
#else
  cv::Ptr<cv::TrackerCSRT> tracker;
#endif
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  static Nan::Persistent<v8::FunctionTemplate> constructor;
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> getTracker()
#else
  cv::Ptr<cv::Tracker> getTracker()
#endif
  { return tracker; }
};
#endif

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
class TrackerKCF : public Tracker {
public:
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::TrackerKCF> tracker;
#else
  cv::Ptr<cv::TrackerKCF> tracker;
#endif

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> getTracker()
#else
  cv::Ptr<cv::Tracker> getTracker()
#endif
  { return tracker; }
};
#endif


class TrackerMedianFlow : public Tracker {
public:
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::TrackerMedianFlow> tracker;
#else
  cv::Ptr<cv::TrackerMedianFlow> tracker;
#endif
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  static Nan::Persistent<v8::FunctionTemplate> constructor;
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> getTracker()
#else
  cv::Ptr<cv::Tracker> getTracker()
#endif
  { return tracker;}
};


class TrackerMIL : public Tracker {
public:
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::TrackerMIL> tracker;
#else
  cv::Ptr<cv::TrackerMIL> tracker;
#endif

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> getTracker()
#else
  cv::Ptr<cv::Tracker> getTracker()
#endif
 { return tracker; }
};


// Ensure that TrackerNano is only defined for OpenCV 3.4.0 or greater
#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

class TrackerMOSSE : public Tracker {
public:
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::TrackerMOSSE> tracker;
#else // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::TrackerMOSSE> tracker;
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> getTracker() 
#else
  cv::Ptr<cv::Tracker> getTracker()
#endif
  { return tracker; }
};

#endif // CV_VERSION_GREATER_EQUAL(3, 4, 0)


class TrackerTLD : public Tracker {
public:
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::TrackerTLD> tracker;
#else // CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::TrackerTLD> tracker;
#endif // CV_VERSION_GREATER_EQUAL(4, 5, 2)

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::Ptr<cv::legacy::Tracker> getTracker()
#else
  cv::Ptr<cv::Tracker> getTracker()
#endif
  { return tracker; }
};

#endif
