#include "Point.h"

Napi::FunctionReference Point2::constructor;
Napi::FunctionReference Point3::constructor;

Napi::Object Point(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference pt2Ctor = Napi::Function::New(env, Point2::New);
  Point2::constructor.Reset(pt2Ctor);

  pt2Ctor->SetClassName(Napi::String::New(env, "Point2"));
  Napi::SetAccessor(pt2Ctor->InstanceTemplate(), Napi::String::New(env, "x"), Point2::x_getter);
  Napi::SetAccessor(pt2Ctor->InstanceTemplate(), Napi::String::New(env, "y"), Point2::y_getter);
  Napi::SetPrototypeMethod(pt2Ctor, "norm", Point2::Norm);
  Napi::SetPrototypeMethod(pt2Ctor, "at", Point2::At);
  Point2::Init(pt2Ctor);

  Napi::FunctionReference pt3Ctor = Napi::Function::New(env, Point3::New);
  Point3::constructor.Reset(pt3Ctor);

  pt3Ctor->SetClassName(Napi::String::New(env, "Point3"));
  Napi::SetAccessor(pt3Ctor->InstanceTemplate(), Napi::String::New(env, "x"), Point3::x_getter);
  Napi::SetAccessor(pt3Ctor->InstanceTemplate(), Napi::String::New(env, "y"), Point3::y_getter);
  Napi::SetAccessor(pt3Ctor->InstanceTemplate(), Napi::String::New(env, "z"), Point3::z_getter);
  Napi::SetPrototypeMethod(pt3Ctor, "norm", Point3::Norm);
  Napi::SetPrototypeMethod(pt3Ctor, "at", Point3::At);
  Point3::Init(pt3Ctor);

  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, Point::New));

  ctor->SetClassName(Napi::String::New(env, "Point"));
  target.Set("Point", FF::getFunction(ctor));
  target.Set("Point2", FF::getFunction(ctor));
  target.Set("Point3", FF::getFunction(ctor));
};

void Point::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Point::New");
  FF_ASSERT_CONSTRUCT_CALL();
  if (info.Length() < 2) {
    return tryCatch.throwError("expected arguments x, y, (z)");
  }
  double x = info[0].ToNumber(Napi::GetCurrentContext())->Value();
  double y = info[1].ToNumber(Napi::GetCurrentContext())->Value();
  Napi::Value jsPoint;
  if (info.Length() == 3) {
    double z = info[2].ToNumber(Napi::GetCurrentContext())->Value();
    jsPoint = Point3::Converter::wrap(cv::Point3d(x, y, z));
  } else {
    jsPoint = Point2::Converter::wrap(cv::Point2d(x, y));
  }
  return jsPoint;
}
