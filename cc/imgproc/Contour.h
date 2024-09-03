#include "Vec.h"
#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#ifndef __FF_CONTOUR_H__
#define __FF_CONTOUR_H__

class Contour : public FF::ObjectWrap<Contour, std::vector<cv::Point2i>> {
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "Contour";
  }

  cv::Vec4i hierarchy;

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  Napi::Value GetNumPoints(const Napi::CallbackInfo& info) {
    return Napi::New(env, (uint)Contour::unwrapSelf(info).size());
  }

  Napi::Value GetHierarchy(const Napi::CallbackInfo& info) {
    return Vec4::Converter::wrap(unwrapThis(info)->hierarchy);
  }

  Napi::Value GetArea(const Napi::CallbackInfo& info) {
    return Napi::New(env, cv::contourArea(Contour::unwrapSelf(info), false));
  }

  Napi::Value GetIsConvex(const Napi::CallbackInfo& info) {
    return Napi::New(env, cv::isContourConvex(Contour::unwrapSelf(info)));
  }

  static void GetPoints(const Napi::CallbackInfo& info);
  static void ApproxPolyDP(const Napi::CallbackInfo& info);
  static void ApproxPolyDPAsync(const Napi::CallbackInfo& info);
  static void ApproxPolyDPContour(const Napi::CallbackInfo& info);
  static void ArcLength(const Napi::CallbackInfo& info);
  static void BoundingRect(const Napi::CallbackInfo& info);
  static void ConvexHull(const Napi::CallbackInfo& info);
  static void ConvexHullAsync(const Napi::CallbackInfo& info);
  static void ConvexHullIndices(const Napi::CallbackInfo& info);
  static void ConvexHullIndicesAsync(const Napi::CallbackInfo& info);
  static void ConvexityDefects(const Napi::CallbackInfo& info);
  static void MinEnclosingCircle(const Napi::CallbackInfo& info);
  static void MinEnclosingTriangle(const Napi::CallbackInfo& info);
  static void PointPolygonTest(const Napi::CallbackInfo& info);
  static void MatchShapes(const Napi::CallbackInfo& info);
  static void FitEllipse(const Napi::CallbackInfo& info);
  static void MinAreaRect(const Napi::CallbackInfo& info);
  static Napi::Value _Moments(const Napi::CallbackInfo& info);
};

#endif
