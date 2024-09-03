#include "Point.h"

Nan::Persistent<v8::FunctionTemplate> Point2::constructor;
Nan::Persistent<v8::FunctionTemplate> Point3::constructor;

Napi::Object Point(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference pt2Ctor = Nan::New<v8::FunctionTemplate>(Point2::New);
  Point2::constructor.Reset(pt2Ctor);
  pt2Ctor->InstanceTemplate()->SetInternalFieldCount(1);
  pt2Ctor->SetClassName(Nan::New("Point2").ToLocalChecked());
  Nan::SetAccessor(pt2Ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Point2::x_getter);
  Nan::SetAccessor(pt2Ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Point2::y_getter);
  Nan::SetPrototypeMethod(pt2Ctor, "norm", Point2::Norm);
  Nan::SetPrototypeMethod(pt2Ctor, "at", Point2::At);
  Point2::Init(pt2Ctor);

  Napi::FunctionReference pt3Ctor = Nan::New<v8::FunctionTemplate>(Point3::New);
  Point3::constructor.Reset(pt3Ctor);
  pt3Ctor->InstanceTemplate()->SetInternalFieldCount(1);
  pt3Ctor->SetClassName(Nan::New("Point3").ToLocalChecked());
  Nan::SetAccessor(pt3Ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Point3::x_getter);
  Nan::SetAccessor(pt3Ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Point3::y_getter);
  Nan::SetAccessor(pt3Ctor->InstanceTemplate(), Nan::New("z").ToLocalChecked(), Point3::z_getter);
  Nan::SetPrototypeMethod(pt3Ctor, "norm", Point3::Norm);
  Nan::SetPrototypeMethod(pt3Ctor, "at", Point3::At);
  Point3::Init(pt3Ctor);

  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(Point::New);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Point").ToLocalChecked());
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
  double x = info[0]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
  double y = info[1]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
  Napi::Value jsPoint;
  if (info.Length() == 3) {
    double z = info[2]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
    jsPoint = Point3::Converter::wrap(cv::Point3d(x, y, z));
  } else {
    jsPoint = Point2::Converter::wrap(cv::Point2d(x, y));
  }
  info.GetReturnValue().Set(jsPoint);
}
