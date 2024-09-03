#include "Size.h"

Napi::FunctionReference Size::constructor;

Napi::Object Size(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, Size::New));
  Size::constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Size").ToLocalChecked());
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("width").ToLocalChecked(), Size::width_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("height").ToLocalChecked(), Size::height_getter);

  target.Set("Size", FF::getFunction(ctor));
};

void Size::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Size::New");
  FF_ASSERT_CONSTRUCT_CALL();
  Size* self = new Size();
  if (info.Length() > 0) {
    if (info.Length() < 2) {
      return tryCatch.throwError("expected arguments width, height");
    }
    double width = info[0]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
    double height = info[1]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
    self->setNativeObject(cv::Size2d(width, height));
  }
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}
