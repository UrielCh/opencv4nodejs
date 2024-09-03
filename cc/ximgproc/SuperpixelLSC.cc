#include "opencv_modules.h"

#ifdef HAVE_OPENCV_XIMGPROC

#include "SuperpixelLSC.h"

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

Napi::FunctionReference SuperpixelLSC::constructor;

Napi::Object SuperpixelLSC(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, SuperpixelLSC::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();
  constructor.Reset(ctor);

  ctor->SetClassName(Napi::String::New(env, "SuperpixelLSC"));

  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "image"), image_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "labels"), labels_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "labelContourMask"), labelContourMask_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "region_size"), region_size_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "ratio"), ratio_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "numCalculatedSuperpixels"), numCalculatedSuperpixels_getter);

  Napi::SetPrototypeMethod(ctor, "iterate", SuperpixelLSC::Iterate);

  target.Set("SuperpixelLSC", FF::getFunction(ctor));
};

void SuperpixelLSC::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "SuperpixelLSC::New");
  FF_ASSERT_CONSTRUCT_CALL();
  SuperpixelLSC::NewWorker worker;

  if (worker.applyUnwrappers(info)) {
    return tryCatch.reThrow();
  }

  SuperpixelLSC* self = new SuperpixelLSC();
  self->image = worker.image;
  self->region_size = worker.region_size;
  self->ratio = worker.ratio;
  self->self = cv::ximgproc::createSuperpixelLSC(
      worker.image,
      worker.region_size,
      worker.ratio);
  self->Wrap(info.Holder());
  return info.Holder();
}

void SuperpixelLSC::Iterate(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "SuperpixelLSC::Iterate");

  uint iterations = 10;
  if (FF::UintConverter::optArg(0, &iterations, info)) {
    return tryCatch.reThrow();
  }

  SuperpixelLSC* self = this;
  self->self->iterate((int)iterations);
  self->self->getLabels(self->labels);
  self->numCalculatedSuperpixels = self->self->getNumberOfSuperpixels();
  self->self->getLabelContourMask(self->labelContourMask, false);
}

#endif

#endif // HAVE_OPENCV_XIMGPROC
