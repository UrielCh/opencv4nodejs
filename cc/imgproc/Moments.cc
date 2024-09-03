#include "opencv_modules.h"

#ifdef HAVE_OPENCV_IMGPROC

#include "Moments.h"
#include <opencv2/imgproc.hpp>

Nan::Persistent<v8::FunctionTemplate> Moments::constructor;

Napi::Object Moments(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(Moments::New);
  Moments::constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Moments").ToLocalChecked());

  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m00"), m00_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m10"), m10_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m01"), m01_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m20"), m20_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m11"), m11_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m02"), m02_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m30"), m30_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m12"), m12_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "m03"), m03_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "mu20"), mu20_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "mu11"), mu11_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "mu02"), mu02_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "mu30"), mu30_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "mu21"), mu21_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "mu12"), mu12_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "mu03"), mu03_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "nu20"), nu20_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "nu11"), nu11_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "nu02"), nu02_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "nu30"), nu30_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "nu21"), nu21_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "nu12"), nu12_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "nu03"), nu03_getter);

  Nan::SetPrototypeMethod(ctor, "huMoments", HuMoments);

  target.Set("Moments", FF::getFunction(ctor));
};

void Moments::New(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("Moments::New");
  FF_ASSERT_CONSTRUCT_CALL();
  Moments* self = new Moments();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

void Moments::HuMoments(const Napi::CallbackInfo& info) {
  std::vector<double> huMoments;
  cv::HuMoments(Moments::unwrapThis(info)->self, huMoments);
  info.GetReturnValue().Set(FF::DoubleArrayConverter::wrap(huMoments));
}

#endif