#include "opencv_modules.h"

#ifdef HAVE_OPENCV_ML

#include "Mat.h"
#include "TrainData.h"

Napi::FunctionReference TrainData::constructor;

Napi::Object TrainData(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, TrainData::New));
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(FF::newString(env, "TrainData"));

  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "layout"), layout_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "samples"), samples_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "responses"), responses_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "varIdx"), varIdx_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "sampleWeights"), sampleWeights_getter);
  Nan::SetAccessor(ctor->InstanceTemplate(), FF::newString(env, "varType"), varType_getter);

  Nan::Set(target, FF::newString(env, "TrainData"), FF::getFunction(ctor));
};

void TrainData::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "TrainData::New");
  FF_ASSERT_CONSTRUCT_CALL();
  TrainData::NewWorker worker;

  if (worker.applyUnwrappers(info)) {
    return tryCatch.reThrow();
  }

  // TODO: uchar / char converter
  std::vector<uchar> varType;
  for (auto val : worker.varType) {
    varType.push_back(val);
  }
  TrainData* self = new TrainData();
  self->self = cv::ml::TrainData::create(
      worker.samples, worker.layout, worker.responses, worker.varIdx, worker.sampleIdx, worker.sampleWeights, varType);
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif
