//
// Created by stefan on 11/4/19.
//

#include "HistAxes.h"
#include "napi.h"

Napi::FunctionReference HistAxes::constructor;

Napi::Object HistAxes(Napi::Env env, Napi::Object exports) {
  //   Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, HistAxes::New));
  //
  //   HistAxes::constructor.Reset(ctor);
  //
  //   ctor->SetClassName(Napi::String::New(env, "HistAxes"));
  //
  //   Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "bins"), HistAxes::bins_getter);
  //   Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "channel"), HistAxes::channel_getter);
  //   Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "ranges"), HistAxes::ranges_getter);

  Napi::Function ctor = DefineClass(env, "HistAxes", {InstanceAccessor<&HistAxes::bins_getter>("bins"), InstanceAccessor<&HistAxes::channel_getter>("channel"), InstanceAccessor<&HistAxes::ranges_getter>("ranges")});

  HistAxes::constructor = Napi::Persistent(ctor);
  HistAxes::constructor.SuppressDestruct();

  exports.Set("HistAxes", FF::getFunction(ctor));
  return exports;
}

void HistAxes::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "HistAxes::New");
  FF_ASSERT_CONSTRUCT_CALL();
  if (info.Length() != 1) {
    return tryCatch.throwError("expected one argument");
  }
  if (!info[0].IsObject()) {
    return tryCatch.throwError("expected arg0 to be an object");
  }

  HistAxes* self = new HistAxes();

  auto jsAxis = info[0].To<Napi::Object>();

  if (!FF::hasOwnProperty(jsAxis, "ranges")) {
    return tryCatch.throwError("expected object to have ranges");
  }
  if (!FF::hasOwnProperty(jsAxis, "bins")) {
    return tryCatch.throwError("expected object to have bins");
  }
  if (!FF::hasOwnProperty(jsAxis, "channel")) {
    return tryCatch.throwError("expected object to have channel");
  }

  Napi::Value jsRangesVal = (jsAxis).Get(Napi::String::New(env, "ranges"));
  Napi::Array jsRanges = jsRangesVal.As<Napi::Array>();

  if (
      jsRanges->Length() != 2 || !(jsRanges).Get(0).IsNumber() || !(jsRanges).Get(1).IsNumber()) {
    return tryCatch.throwError("expected ranges to be an array with 2 numbers");
  }

  FF::DoubleArrayConverter::unwrapTo(&self->self.range, jsRanges);

  FF::IntConverter::prop(&self->self.channel, "channel", jsAxis);
  FF::IntConverter::prop(&self->self.bins, "bins", jsAxis);

  self->Wrap(info.Holder());
  return info.Holder();
}