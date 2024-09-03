#include "opencv_modules.h"

#ifdef HAVE_OPENCV_XIMGPROC

#include "SuperpixelSEEDS.h"

Napi::FunctionReference SuperpixelSEEDS::constructor;

Napi::Object SuperpixelSEEDS(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, SuperpixelSEEDS::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();
  constructor.Reset(ctor);

  ctor->SetClassName(Napi::String::New(env, "SuperpixelSEEDS"));

  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "image"), image_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "labels"), labels_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "labelContourMask"), labelContourMask_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "num_superpixels"), num_superpixels_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "num_levels"), num_levels_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "prior"), prior_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "histogram_bins"), histogram_bins_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "double_step"), double_step_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "numCalculatedSuperpixels"), numCalculatedSuperpixels_getter);

  Napi::SetPrototypeMethod(ctor, "iterate", SuperpixelSEEDS::Iterate);

  target.Set("SuperpixelSEEDS", FF::getFunction(ctor));
};

void SuperpixelSEEDS::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "SuperpixelSEEDS::New");
  FF_ASSERT_CONSTRUCT_CALL();
  SuperpixelSEEDS::NewWorker worker;

  if (worker.applyUnwrappers(info)) {
    return tryCatch.reThrow();
  }

  SuperpixelSEEDS* self = new SuperpixelSEEDS();
  self->image = worker.img;
  self->num_superpixels = worker.num_superpixels;
  self->num_levels = worker.num_levels;
  self->prior = worker.prior;
  self->histogram_bins = worker.histogram_bins;
  self->double_step = worker.double_step;

  self->self = cv::ximgproc::createSuperpixelSEEDS(
      worker.img.cols,
      worker.img.rows,
      worker.img.channels(),
      worker.num_superpixels,
      worker.num_levels,
      worker.prior,
      worker.histogram_bins,
      worker.double_step);
  self->Wrap(info.Holder());
  return info.Holder();
}

void SuperpixelSEEDS::Iterate(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "SuperpixelSEEDS::Iterate");

  uint iterations = 4;
  if (FF::UintConverter::optArg(0, &iterations, info)) {
    return tryCatch.reThrow();
  }

  SuperpixelSEEDS* self = this;
  self->self->iterate(self->image, (int)iterations);
  self->self->getLabels(self->labels);
  self->numCalculatedSuperpixels = self->self->getNumberOfSuperpixels();
  self->self->getLabelContourMask(self->labelContourMask);
}

#endif // HAVE_OPENCV_XIMGPROC
