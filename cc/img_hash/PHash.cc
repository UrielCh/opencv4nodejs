#include "opencv_modules.h"

#ifdef HAVE_OPENCV_IMG_HASH

#include "PHash.h"

Napi::FunctionReference PHash::constructor;

Napi::Object PHash(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, PHash::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  ImgHashBase::Init(env, exports);
  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "PHash"));

  (target).Set("PHash", FF::getFunction(ctor));
};

void PHash::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "PHash::New");
  FF_ASSERT_CONSTRUCT_CALL();

  PHash* self = new PHash();
  self->Wrap(info.Holder());
  self->imgHashBase = cv::img_hash::PHash::create();

  return info.Holder();
};

#endif
