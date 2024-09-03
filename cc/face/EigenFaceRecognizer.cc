#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "EigenFaceRecognizer.h"
#include "FaceRecognizerBindings.h"

Napi::FunctionReference EigenFaceRecognizer::constructor;

Napi::Object EigenFaceRecognizer(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, EigenFaceRecognizer::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FaceRecognizer::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(Nan::New("EigenFaceRecognizer").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

  target.Set("EigenFaceRecognizer", FF::getFunction(ctor));
};

void EigenFaceRecognizer::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "EigenFaceRecognizer::New");
  FF_ASSERT_CONSTRUCT_CALL();
  FaceRecognizerBindings::NewWorker worker;

  if (worker.applyUnwrappers(info)) {
    return tryCatch.reThrow();
  }

  EigenFaceRecognizer* self = new EigenFaceRecognizer();
  self->Wrap(info.Holder());
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->faceRecognizer = cv::face::EigenFaceRecognizer::create(worker.num_components, worker.threshold);
#else
  self->faceRecognizer = cv::face::createEigenFaceRecognizer(worker.num_components, worker.threshold);
#endif
  info.GetReturnValue().Set(info.Holder());
};

#endif
