#include "opencv_modules.h"

#ifdef HAVE_OPENCV_ML

#include "Mat.h"
#include "TrainData.h"

Nan::Persistent<v8::FunctionTemplate> TrainData::constructor;

NAN_MODULE_INIT(TrainData::Init) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(TrainData::New);
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

NAN_METHOD(TrainData::New) {
  FF::TryCatch tryCatch("TrainData::New");
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
