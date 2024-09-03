#include "RotatedRect.h"

Napi::FunctionReference RotatedRect::constructor;

Napi::Object RotatedRect(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, RotatedRect::New));
  RotatedRect::constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("RotatedRect").ToLocalChecked());
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "angle"), RotatedRect::angle_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "center"), RotatedRect::center_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "size"), RotatedRect::size_getter);

  Nan::SetPrototypeMethod(ctor, "boundingRect", RotatedRect::BoundingRect);

  target.Set("RotatedRect", FF::getFunction(ctor));
};

void RotatedRect::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "RotatedRect::New");
  FF_ASSERT_CONSTRUCT_CALL();
  RotatedRect* self = new RotatedRect();
  if (info.Length() == 0) {
    self->self = cv::RotatedRect();
  } else {
    if (info.Length() < 3) {
      return tryCatch.throwError("expected arguments center, size, angle");
    }
    if (!Point2::hasInstance(info[0])) {
      return tryCatch.throwError("expected arg0 to be an instance of Point2");
    }
    if (!Size::hasInstance(info[1])) {
      return tryCatch.throwError("expected arg1 to be an instance of Size");
    }
    double angle = info[2]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();

    self->self = cv::RotatedRect(
        Point2::Converter::unwrapUnchecked(info[0]),
        Size::Converter::unwrapUnchecked(info[1]),
        angle);
  }
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}
