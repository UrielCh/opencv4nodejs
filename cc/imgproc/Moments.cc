#include "opencv_modules.h"

#ifdef HAVE_OPENCV_IMGPROC

#include "Moments.h"
#include <opencv2/imgproc.hpp>

Napi::FunctionReference Moments::constructor;

Napi::Object Moments(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, Moments::New));
  Moments::constructor.Reset(ctor);

  ctor->SetClassName(Napi::String::New(env, "Moments"));

  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m00"), m00_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m10"), m10_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m01"), m01_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m20"), m20_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m11"), m11_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m02"), m02_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m30"), m30_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m12"), m12_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m03"), m03_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "mu20"), mu20_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "mu11"), mu11_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "mu02"), mu02_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "mu30"), mu30_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "mu21"), mu21_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "mu12"), mu12_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "mu03"), mu03_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "nu20"), nu20_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "nu11"), nu11_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "nu02"), nu02_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "nu30"), nu30_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "nu21"), nu21_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "nu12"), nu12_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "nu03"), nu03_getter);

  InstanceMethod("huMoments", &HuMoments),

      target.Set("Moments", FF::getFunction(ctor));
};

void Moments::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Moments::New");
  FF_ASSERT_CONSTRUCT_CALL();
  Moments* self = new Moments();
  self->Wrap(info.Holder());
  return info.Holder();
}

void Moments::HuMoments(const Napi::CallbackInfo& info) {
  std::vector<double> huMoments;
  cv::HuMoments(Moments::unwrapThis(info)->self, huMoments);
  return FF::DoubleArrayConverter::wrap(huMoments);
}

#endif