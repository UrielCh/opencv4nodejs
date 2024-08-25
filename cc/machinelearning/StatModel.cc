#include "opencv_modules.h"

#ifdef HAVE_OPENCV_ML

#include "Mat.h"
#include "StatModel.h"

Nan::Persistent<v8::FunctionTemplate> StatModel::constructor;

NAN_MODULE_INIT(StatModel::Init) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(StatModel::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("StatModel").ToLocalChecked());

  Nan::Set(target, Nan::New("StatModel").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(StatModel::New) {
  FF::TryCatch tryCatch("StatModel::New");
  FF_ASSERT_CONSTRUCT_CALL();
  StatModel* self = new StatModel();

  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif
