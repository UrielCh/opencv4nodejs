#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "BFMatcher.h"
#include "BFMatcherBindings.h"

Napi::FunctionReference BFMatcher::constructor;

Napi::Object BFMatcher(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, BFMatcher::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);

  ctor->SetClassName(Napi::String::New(env, "BFMatcher"));

  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "normType"), normType_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "crossCheck"), crossCheck_getter);

  InstanceMethod("match", &match),
      InstanceMethod("matchAsync", &matchAsync),
      InstanceMethod("knnMatch", &knnMatch),
      InstanceMethod("knnMatchAsync", &knnMatchAsync),

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
  return info.Holder();
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