#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "KeyPoint.h"

Napi::FunctionReference KeyPoint::constructor;

Napi::Object KeyPoint(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, KeyPoint::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);

  ctor->SetClassName(Napi::String::New(env, "KeyPoint"));

  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "localId"), localId_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "pt"), pt_getter, pt_setter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "angle"), angle_getter, angle_setter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "class_id"), class_id_getter, class_id_setter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "response"), response_getter, response_setter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "size"), size_getter, size_setter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "octave"), octave_getter, octave_setter);

  target.Set("KeyPoint", FF::getFunction(ctor));
};

void KeyPoint::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "KeyPoint::New");
  FF_ASSERT_CONSTRUCT_CALL();
  KeyPoint* self = new KeyPoint();

  if (info.Length() > 0) {
    cv::Point2d pt;
    double size, angle, response;
    int octave, classId;
    if (
        Point2::Converter::arg(0, &pt, info) || FF::DoubleConverter::arg(1, &size, info) || FF::DoubleConverter::arg(2, &angle, info) || FF::DoubleConverter::arg(3, &response, info) || FF::IntConverter::arg(4, &octave, info) || FF::IntConverter::arg(5, &classId, info)) {
      return tryCatch.reThrow();
    }
    self->self = cv::KeyPoint(pt, size, angle, response, octave, classId);
  }

  self->Wrap(info.Holder());
  return info.Holder();
}

#endif
