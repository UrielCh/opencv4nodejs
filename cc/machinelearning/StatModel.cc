#include "opencv_modules.h"

#ifdef HAVE_OPENCV_ML

#include "Mat.h"
#include "StatModel.h"

Nan::Persistent<v8::FunctionTemplate> StatModel::constructor;

Napi::Object StatModel(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(StatModel::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("StatModel").ToLocalChecked());

  target.Set("StatModel", FF::getFunction(ctor));
};

void StatModel::New(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("StatModel::New");
  FF_ASSERT_CONSTRUCT_CALL();
  StatModel* self = new StatModel();

  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif
