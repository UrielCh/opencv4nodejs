#include "Point2.h"
#include "Point3.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_POINT_H__
#define __FF_POINT_H__

class Point : public Napi::ObjectWrap<Point> {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);
  static void NewPoint2(const Napi::CallbackInfo& info);
  static void NewPoint3(const Napi::CallbackInfo& info);
};

#endif
