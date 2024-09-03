#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "DescriptorMatch.h"

Napi::FunctionReference DescriptorMatch::constructor;

Napi::Object DescriptorMatch(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, DescriptorMatch::New));
  constructor.Reset(ctor);

  ctor->SetClassName(Napi::String::New(env, "DescriptorMatch"));

  Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "queryIdx"), queryIdx_getter, queryIdx_setter);
  Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "trainIdx"), trainIdx_getter, trainIdx_setter);
  Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "distance"), distance_getter, distance_setter);

  target.Set("DescriptorMatch", FF::getFunction(ctor));
};

void DescriptorMatch::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "DescriptorMatch::New");
  FF_ASSERT_CONSTRUCT_CALL();
  DescriptorMatch* self = new DescriptorMatch();
  if (info.Length() > 0) {
    int queryIdx, trainIdx;
    double distance;
    if (
        FF::IntConverter::arg(0, &queryIdx, info) || FF::IntConverter::arg(1, &trainIdx, info) || FF::DoubleConverter::arg(2, &distance, info)) {
      return tryCatch.reThrow();
    }
    self->self = cv::DMatch(queryIdx, trainIdx, distance);
  }
  self->Wrap(info.Holder());
  return info.Holder();
}

#endif
