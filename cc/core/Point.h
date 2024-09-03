#include "Point2.h"
#include "Point3.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_POINT_H__
#define __FF_POINT_H__

class Point : public Napi::ObjectWrap<Point> {
public:
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  static NAN_METHOD(NewPoint2);
  static NAN_METHOD(NewPoint3);
};

#endif
