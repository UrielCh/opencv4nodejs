#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "BFMatcher.h"
#include "BFMatcherBindings.h"

Napi::FunctionReference BFMatcher::constructor;

Napi::Object BFMatcher(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(BFMatcher::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);

  ctor->SetClassName(Nan::New("BFMatcher").ToLocalChecked());

  Nan::SetAccessor(instanceTemplate, Nan::New("normType").ToLocalChecked(), normType_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("crossCheck").ToLocalChecked(), crossCheck_getter);

  Nan::SetPrototypeMethod(ctor, "match", match);
  Nan::SetPrototypeMethod(ctor, "matchAsync", matchAsync);
  Nan::SetPrototypeMethod(ctor, "knnMatch", knnMatch);
  Nan::SetPrototypeMethod(ctor, "knnMatchAsync", knnMatchAsync);

  target.Set("BFMatcher", FF::getFunction(ctor));
};

void BFMatcher::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "BFMatcher::New");
  FF_ASSERT_CONSTRUCT_CALL();
  BFMatcher::NewWorker worker;

  if (worker.applyUnwrappers(info)) {
    return tryCatch.reThrow();
  }

  BFMatcher* self = new BFMatcher();
  self->normType = worker.normType;
  self->crossCheck = worker.crossCheck;
  self->self = cv::BFMatcher(
      worker.normType,
      worker.crossCheck);
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

void BFMatcher::match(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<BFMatcherBindings::MatchWorker>(BFMatcher::unwrapSelf(info)),
      "BFMatcher::match",
      info);
}

void BFMatcher::matchAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<BFMatcherBindings::MatchWorker>(BFMatcher::unwrapSelf(info)),
      "BFMatcher::matchAsync",
      info);
}

void BFMatcher::knnMatch(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<BFMatcherBindings::MatchKnnWorker>(BFMatcher::unwrapSelf(info)),
      "BFMatcher::knnMatch",
      info);
}

void BFMatcher::knnMatchAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<BFMatcherBindings::MatchKnnWorker>(BFMatcher::unwrapSelf(info)),
      "BFMatcher::knnMatchAsync",
      info);
}

#endif