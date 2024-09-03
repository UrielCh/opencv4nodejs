#include "opencv_modules.h"

#ifdef HAVE_OPENCV_IMGPROC

#include "Contour.h"
#include "ContourBindings.h"
#include "Mat.h"
#include "Moments.h"
#include "Point.h"
#include "Rect.h"
#include "RotatedRect.h"

Napi::FunctionReference Contour::constructor;

Napi::Object Contour(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, Contour::New));
  constructor.Reset(ctor);

  ctor->SetClassName(Napi::String::New(env, "Contour"));

  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "isConvex"), GetIsConvex);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "area"), GetArea);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "numPoints"), GetNumPoints);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "hierarchy"), GetHierarchy);

  InstanceMethod("getPoints", &GetPoints),
      InstanceMethod("approxPolyDP", &ApproxPolyDP),
      InstanceMethod("approxPolyDPAsync", &ApproxPolyDPAsync),
      InstanceMethod("approxPolyDPContour", &ApproxPolyDPContour),
      InstanceMethod("arcLength", &ArcLength),
      InstanceMethod("boundingRect", &BoundingRect),
      InstanceMethod("convexHull", &ConvexHull),
      InstanceMethod("convexHullIndices", &ConvexHullIndices),
      InstanceMethod("convexityDefects", &ConvexityDefects),
      InstanceMethod("minAreaRect", &MinAreaRect),
      InstanceMethod("minEnclosingCircle", &MinEnclosingCircle),
      InstanceMethod("minEnclosingTriangle", &MinEnclosingTriangle),
      InstanceMethod("pointPolygonTest", &PointPolygonTest),
      InstanceMethod("matchShapes", &MatchShapes),
      InstanceMethod("fitEllipse", &FitEllipse),
      InstanceMethod("moments", &_Moments),

      target.Set("Contour", FF::getFunction(ctor));
};

void Contour::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Contour::New");
  FF_ASSERT_CONSTRUCT_CALL();
  if (info.Length() > 1) {
    return tryCatch.throwError("expected one or zero argument");
  }
  if (info.Length() == 1 && !info[0].IsArray()) {
    return tryCatch.throwError("expected arg0 to be an array");
  }

  Contour* self = new Contour();
  if (info.Length() == 1) {
    Napi::Array jsPts = info[0].As<Napi::Array>();
    self->self.reserve(jsPts->Length());
    for (uint i = 0; i < jsPts->Length(); i++) {
      cv::Point2d cv_pt;
      auto jsPt = (jsPts).Get(i);
      if (jsPt->IsArray()) {
        Napi::Array jsObj = jsPt.As<Napi::Array>();
        if (jsObj->Length() != 2)
          return tryCatch.throwError("expected arg0 to consist of only Point2 or array of length 2");
        double x = FF::DoubleConverter::unwrapUnchecked((jsObj).Get(0));
        double y = FF::DoubleConverter::unwrapUnchecked((jsObj).Get(1));
        cv_pt = cv::Point2d(x, y);
      } else if (Point2::hasInstance(jsPt)) {
        cv_pt = Point2::Converter::unwrapUnchecked(jsPt);
      } else {
        return tryCatch.throwError("expected arg0 to consist of only Point2 or array of length 2");
      }
      self->self.emplace_back(cv::Point2i(cv_pt.x, cv_pt.y));
    }
  }
  self->hierarchy = cv::Vec4i(-1, -1, -1, -1);
  self->Wrap(info.Holder());
  return info.Holder();
}

void Contour::GetPoints(const Napi::CallbackInfo& info) {
  return Point2::ArrayWithCastConverter<cv::Point2i>::wrap(Contour::unwrapSelf(info));
}

void Contour::ApproxPolyDP(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<ContourBindings::ApproxPolyDPWorker>(Contour::unwrapSelf(info)),
      "Contour::ApproxPolyDP",
      info);
}

void Contour::ApproxPolyDPAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<ContourBindings::ApproxPolyDPWorker>(Contour::unwrapSelf(info)),
      "Contour::ApproxPolyDPAsync",
      info);
}

void Contour::ApproxPolyDPContour(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Contour::ApproxPolyDPContour");
  double epsilon;
  bool closed;
  if (
      FF::DoubleConverter::arg(0, &epsilon, info) || FF::BoolConverter::arg(1, &closed, info)) {
    return tryCatch.reThrow();
  }

  std::vector<cv::Point> curve;
  cv::approxPolyDP(Contour::unwrapSelf(info), curve, epsilon, closed);

  Napi::Object jsApprox = FF::newInstance(Napi::New(env, Contour::constructor));
  Contour* pContour = Contour::unwrapClassPtrUnchecked(jsApprox);
  pContour->setNativeObject(curve);
  pContour->hierarchy = cv::Vec4i(-1, -1, -1, -1);
  return jsApprox;
}

void Contour::ArcLength(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Contour::ArcLength");
  bool closed = false;
  if (FF::BoolConverter::optArg(0, &closed, info)) {
    return tryCatch.reThrow();
  }

  double arcLength = cv::arcLength(Contour::unwrapSelf(info), closed);
  return Napi::New(env, arcLength);
}

void Contour::BoundingRect(const Napi::CallbackInfo& info) {
  return Rect::Converter::wrap(cv::boundingRect(Contour::unwrapSelf(info)));
}

void Contour::ConvexHull(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Contour::ConvexHull");
  bool clockwise = false;
  if (FF::BoolConverter::optArg(0, &clockwise, info)) {
    return tryCatch.reThrow();
  }

  std::vector<cv::Point> hullPoints;
  cv::convexHull(
      Contour::unwrapSelf(info),
      hullPoints,
      clockwise,
      true);
  Napi::Object jsHull = FF::newInstance(Napi::New(env, Contour::constructor));
  Contour* pContour = Contour::unwrapClassPtrUnchecked(jsHull);
  pContour->setNativeObject(hullPoints);
  pContour->hierarchy = cv::Vec4i(-1, -1, -1, -1);
  return jsHull;
}

void Contour::ConvexHullIndices(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Contour::ConvexHullIndices");
  bool clockwise = false;
  if (FF::BoolConverter::optArg(0, &clockwise, info)) {
    return tryCatch.reThrow();
  }

  std::vector<int> hullIndices;
  cv::convexHull(
      Contour::unwrapSelf(info),
      hullIndices,
      clockwise,
      false);
  return FF::IntArrayConverter::wrap(hullIndices);
}

void Contour::ConvexityDefects(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Contour::ConvexityDefects");
  std::vector<int> hull;
  if (FF::IntArrayConverter::arg(0, &hull, info)) {
    return tryCatch.reThrow();
  }

  std::vector<cv::Vec4d> defects;
  cv::convexityDefects(
      Contour::unwrapSelf(info),
      hull,
      defects);

  return Vec4::ArrayConverter::wrap(defects);
}

void Contour::MinEnclosingCircle(const Napi::CallbackInfo& info) {
  cv::Point2f center;
  float radius;
  cv::minEnclosingCircle(Contour::unwrapSelf(info), center, radius);

  Napi::Object jsCircle = Napi::Object::New(env);
  (jsCircle).Set("center", Point2::Converter::wrap(center));
  (jsCircle).Set("radius", Napi::New(env, (double)radius));
  return jsCircle;
}

void Contour::MinEnclosingTriangle(const Napi::CallbackInfo& info) {
  std::vector<cv::Point2f> triangle;
  cv::minEnclosingTriangle(
      Contour::unwrapSelf(info),
      triangle);
  return Point2::ArrayWithCastConverter<cv::Point2f>::wrap(triangle);
}

void Contour::PointPolygonTest(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Contour::PointPolygonTest");
  cv::Point2d point;
  if (Point2::Converter::arg(0, &point, info)) {
    return tryCatch.reThrow();
  }

  double dist = cv::pointPolygonTest(
      Contour::unwrapSelf(info),
      point,
      true);
  return Napi::New(env, dist);
}

void Contour::MatchShapes(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Contour::MatchShapes");
  std::vector<cv::Point> contour2;
  uint method;
  if (
      Contour::Converter::arg(0, &contour2, info) || FF::UintConverter::arg(1, &method, info)) {
    return tryCatch.reThrow();
  }

  // parameter not supported
  double parameter = 0.0;
  double cmp = cv::matchShapes(
      Contour::unwrapSelf(info),
      contour2,
      (int)method,
      parameter);
  return Napi::New(env, cmp);
}

void Contour::MinAreaRect(const Napi::CallbackInfo& info) {
  return RotatedRect::Converter::wrap(cv::minAreaRect(Contour::unwrapSelf(info)));
}

void Contour::FitEllipse(const Napi::CallbackInfo& info) {
  return RotatedRect::Converter::wrap(cv::fitEllipse(Contour::unwrapSelf(info)));
}

Napi::Value Contour::_Moments(const Napi::CallbackInfo& info) {
  return Moments::Converter::wrap(cv::moments(Contour::unwrapSelf(info)));
}

#endif
