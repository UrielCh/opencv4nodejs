#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "FaceRecognizerBindings.h"
#include "FisherFaceRecognizer.h"

Napi::FunctionReference FisherFaceRecognizer::constructor;

Napi::Object FisherFaceRecognizer(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, FisherFaceRecognizer::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FaceRecognizer::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(Nan::New("FisherFaceRecognizer").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

  target.Set("FisherFaceRecognizer", FF::getFunction(ctor));
};

void FisherFaceRecognizer::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "FisherFaceRecognizer::New");
  FF_ASSERT_CONSTRUCT_CALL();
  FaceRecognizerBindings::NewWorker worker;

  if (worker.applyUnwrappers(info)) {
    return tryCatch.reThrow();
  }

  FisherFaceRecognizer* self = new FisherFaceRecognizer();
  self->Wrap(info.Holder());
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->faceRecognizer = cv::face::FisherFaceRecognizer::create(worker.num_components, worker.threshold);
#else
  self->faceRecognizer = cv::face::createFisherFaceRecognizer(worker.num_components, worker.threshold);
#endif
  info.GetReturnValue().Set(info.Holder());
};

#endif
