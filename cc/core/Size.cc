#include "Size.h"

Napi::FunctionReference Size::constructor;

Napi::Object Size(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, Size::New));
  Size::constructor.Reset(ctor);

  ctor->SetClassName(Napi::String::New(env, "Size"));
  Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "width"), Size::width_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "height"), Size::height_getter);

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
    double width = info[0].ToNumber(Napi::GetCurrentContext())->Value();
    double height = info[1].ToNumber(Napi::GetCurrentContext())->Value();
    self->setNativeObject(cv::Size2d(width, height));
  }
  self->Wrap(info.Holder());
  return info.Holder();
}
