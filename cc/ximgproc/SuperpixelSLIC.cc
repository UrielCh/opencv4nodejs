#include "opencv_modules.h"

#ifdef HAVE_OPENCV_XIMGPROC

#include "SuperpixelSLIC.h"

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

Napi::FunctionReference SuperpixelSLIC::constructor;

Napi::Object SuperpixelSLIC(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, SuperpixelSLIC::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();
  constructor.Reset(ctor);

  ctor->SetClassName(Napi::String::New(env, "SuperpixelSLIC"));

  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "image"), image_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "labels"), labels_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "labelContourMask"), labelContourMask_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "numCalculatedSuperpixels"), numCalculatedSuperpixels_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "algorithm"), algorithm_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "region_size"), region_size_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "ruler"), ruler_getter);

  Napi::SetPrototypeMethod(ctor, "iterate", SuperpixelSLIC::Iterate);

  target.Set("SuperpixelSLIC", FF::getFunction(ctor));
};

void SuperpixelSLIC::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "SuperpixelSLIC::New");
  FF_ASSERT_CONSTRUCT_CALL();
  SuperpixelSLIC::NewWorker worker;

  if (worker.applyUnwrappers(info)) {
    return tryCatch.reThrow();
  }

  SuperpixelSLIC* self = new SuperpixelSLIC();
  self->image = worker.image;
  self->algorithm = worker.algorithm;
  self->region_size = worker.region_size;
  self->ruler = worker.ruler;
  self->superpixelSlic = cv::ximgproc::createSuperpixelSLIC(
      worker.image,
      worker.algorithm,
      worker.region_size,
      worker.ruler);
  self->Wrap(info.Holder());
  return info.Holder();
}

void SuperpixelSLIC::Iterate(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "SuperpixelSLIC::Iterate");

  uint iterations = 10;
  if (FF::UintConverter::optArg(0, &iterations, info)) {
    return tryCatch.reThrow();
  }

  SuperpixelSLIC* self = this;
  self->superpixelSlic->iterate((int)iterations);
  self->superpixelSlic->getLabels(self->labels);
  self->numCalculatedSuperpixels = self->superpixelSlic->getNumberOfSuperpixels();
  self->superpixelSlic->getLabelContourMask(self->labelContourMask, false);
}

#endif

#endif // HAVE_OPENCV_XIMGPROC
