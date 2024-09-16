#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "BRISKDetector.h"

Napi::FunctionReference BRISKDetector::constructor;

Napi::Object BRISKDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, BRISKDetector::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FeatureDetector::Init(env, exports);
  constructor.Reset(ctor);
  ctor->SetClassName(Napi::String::New(env, "BRISKDetector"));


  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "thresh"), thresh_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "octaves"), octaves_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "patternScale"), patternScale_getter);

  target.Set("BRISKDetector", FF::getFunction(ctor));
};

void BRISKDetector::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "BRISKDetector::New");
  FF_ASSERT_CONSTRUCT_CALL();
  BRISKDetector::NewWorker worker;

  if (worker.applyUnwrappers(info)) {
    return tryCatch.reThrow();
  }

  BRISKDetector* self = new BRISKDetector();
  self->thresh = worker.thresh;
  self->octaves = worker.octaves;
  self->patternScale = worker.patternScale;
  self->self = cv::BRISK::create(self->thresh, self->octaves, (float)self->patternScale);
  self->Wrap(info.Holder());
  return info.Holder();
}

#endif