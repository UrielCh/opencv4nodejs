#include "opencv_modules.h"

#ifdef HAVE_OPENCV_ML

#include "ParamGrid.h"

Napi::FunctionReference ParamGrid::constructor;

Napi::Object ParamGrid(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, ParamGrid::New));
  constructor.Reset(ctor);

  ctor->SetClassName(FF::newString(env, "ParamGrid"));

  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "minVal"), minVal_getter, minVal_setter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "maxVal"), maxVal_getter, maxVal_setter);
  Napi::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "logStep"), logStep_getter, logStep_setter);

  (target).Set("ParamGrid", FF::getFunction(ctor));
};

void ParamGrid::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "ParamGrid::New");
  FF_ASSERT_CONSTRUCT_CALL();
  ParamGrid* self = new ParamGrid();
  if (info.Length() > 0) {
    if (info.Length() == 1) {
      unsigned int paramId;
      if (FF::UintConverter::arg(0, &paramId, info)) {
        return tryCatch.reThrow();
      }
      self->self = cv::ml::SVM::getDefaultGrid(paramId);
    } else {
      double minVal, maxVal, logStep;
      if (
          FF::DoubleConverter::arg(0, &minVal, info) || FF::DoubleConverter::arg(1, &maxVal, info) || FF::DoubleConverter::arg(2, &logStep, info)) {
        return tryCatch.reThrow();
      }
      self->self = cv::ml::ParamGrid(minVal, maxVal, logStep);
    }
  }
  self->Wrap(info.Holder());
  return info.Holder();
};

#endif