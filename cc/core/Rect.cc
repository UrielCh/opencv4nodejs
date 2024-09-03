#include "Rect.h"
#include "RectBindings.h"

Napi::FunctionReference Rect::constructor;

Napi::Object Rect(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(Rect::New);
  Rect::constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Rect").ToLocalChecked());
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Rect::x_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Rect::y_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("width").ToLocalChecked(), Rect::width_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("height").ToLocalChecked(), Rect::height_getter);

  Nan::SetPrototypeMethod(ctor, "and", And);
  Nan::SetPrototypeMethod(ctor, "or", Or);
  Nan::SetPrototypeMethod(ctor, "toSquare", ToSquare);
  Nan::SetPrototypeMethod(ctor, "toSquareAsync", ToSquareAsync);
  Nan::SetPrototypeMethod(ctor, "pad", Pad);
  Nan::SetPrototypeMethod(ctor, "padAsync", PadAsync);
  Nan::SetPrototypeMethod(ctor, "rescale", Rescale);
  Nan::SetPrototypeMethod(ctor, "rescaleAsync", RescaleAsync);

  target.Set("Rect", FF::getFunction(ctor));
};

void Rect::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "Rect::New");
  FF_ASSERT_CONSTRUCT_CALL();
  Rect* self = new Rect();
  if (info.Length() == 0) {
    self->self = cv::Rect2d();
  } else {
    if (info.Length() < 4) {
      return tryCatch.throwError("expected arguments x, y, width, height");
    }
    double x = info[0]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
    double y = info[1]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
    double width = info[2]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
    double height = info[3]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
    self->self = cv::Rect2d(x, y, width, height);
  }
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

void Rect::And(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<RectBindings::AndWorker>(Rect::unwrapSelf(info)),
      "Rect::And",
      info);
}

void Rect::Or(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<RectBindings::OrWorker>(Rect::unwrapSelf(info)),
      "Rect::Or",
      info);
}

void Rect::ToSquare(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<RectBindings::ToSquareWorker>(Rect::unwrapSelf(info)),
      "Rect::ToSquare",
      info);
}

void Rect::ToSquareAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<RectBindings::ToSquareWorker>(Rect::unwrapSelf(info)),
      "Rect::ToSquareAsync",
      info);
}

void Rect::Pad(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<RectBindings::PadWorker>(Rect::unwrapSelf(info)),
      "Rect::Pad",
      info);
}

void Rect::PadAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<RectBindings::PadWorker>(Rect::unwrapSelf(info)),
      "Rect::PadAsync",
      info);
}

void Rect::Rescale(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<RectBindings::RescaleWorker>(Rect::unwrapSelf(info)),
      "Rect::Rescale",
      info);
}

void Rect::RescaleAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<RectBindings::RescaleWorker>(Rect::unwrapSelf(info)),
      "Rect::RescaleAsync",
      info);
}
