#include "Rect.h"
#include "RectBindings.h"

Napi::FunctionReference Rect::constructor;

Napi::Object Rect(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, Rect::New));
  Rect::constructor.Reset(ctor);

  ctor->SetClassName(Napi::String::New(env, "Rect"));
  Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "x"), Rect::x_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "y"), Rect::y_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "width"), Rect::width_getter);
  Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "height"), Rect::height_getter);

  InstanceMethod("and", &And),
  InstanceMethod("or", &Or),
  InstanceMethod("toSquare", &ToSquare),
  InstanceMethod("toSquareAsync", &ToSquareAsync),
  InstanceMethod("pad", &Pad),
  InstanceMethod("padAsync", &PadAsync),
  InstanceMethod("rescale", &Rescale),
  InstanceMethod("rescaleAsync", &RescaleAsync),

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
    double x = info[0].ToNumber(Napi::GetCurrentContext())->Value();
    double y = info[1].ToNumber(Napi::GetCurrentContext())->Value();
    double width = info[2].ToNumber(Napi::GetCurrentContext())->Value();
    double height = info[3].ToNumber(Napi::GetCurrentContext())->Value();
    self->self = cv::Rect2d(x, y, width, height);
  }
  self->Wrap(info.Holder());
  return info.Holder();
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
