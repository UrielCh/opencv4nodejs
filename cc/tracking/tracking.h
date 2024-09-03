#include "macros.h"
#include <opencv2/tracking.hpp>

#ifndef __FF_TRACKING_H__
#define __FF_TRACKING_H__

class Tracking {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
};

#endif