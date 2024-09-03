#include "TermCriteria.h"

Napi::FunctionReference TermCriteria::constructor;

Napi::Object TermCriteria(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(TermCriteria::New);
  TermCriteria::constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(FF::newString(env, "TermCriteria"));
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "type"), type_getter, type_setter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "maxCount"), maxCount_getter, maxCount_setter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "epsilon"), epsilon_getter, epsilon_setter);

  Nan::Set(target, FF::newString(env, "TermCriteria"), FF::getFunction(ctor));
};

void TermCriteria::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "TermCriteria::New");
  FF_ASSERT_CONSTRUCT_CALL();
  TermCriteria* self = new TermCriteria();

  if (info.Length() > 0) {
    int type, maxCount;
    double epsilon;
    if (
        FF::IntConverter::arg(0, &type, info) || FF::IntConverter::arg(1, &maxCount, info) || FF::DoubleConverter::arg(2, &epsilon, info)) {
      return tryCatch.reThrow();
    }
    self->self = cv::TermCriteria(type, maxCount, epsilon);
  }
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}
