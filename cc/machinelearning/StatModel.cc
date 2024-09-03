#include "opencv_modules.h"

#ifdef HAVE_OPENCV_ML

#include "Mat.h"
#include "StatModel.h"

Napi::FunctionReference StatModel::constructor;

Napi::Object StatModel(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, StatModel::New));
  constructor.Reset(ctor);

  ctor->SetClassName(Napi::String::New(env, "StatModel"));

  target.Set("StatModel", FF::getFunction(ctor));
};

void StatModel::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "StatModel::New");
  FF_ASSERT_CONSTRUCT_CALL();
  StatModel* self = new StatModel();

  self->Wrap(info.Holder());
  return info.Holder();
};

#endif
