#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "FacemarkAAM.h"
#include "FacemarkAAMParams.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

Napi::FunctionReference FacemarkAAM::constructor;

Napi::Object FacemarkAAM(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor =
      Napi::Function::New(env, FacemarkAAM::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  Facemark::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(Napi::String::New(env, "FacemarkAAM"));


  target.Set("FacemarkAAM", FF::getFunction(ctor));
};

void FacemarkAAM::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "FacemarkAAM::New");
  FF_ASSERT_CONSTRUCT_CALL();

  cv::face::FacemarkAAM::Params params;
  if (FacemarkAAMParams::Converter::optArg(0, &params, info)) {
    return tryCatch.reThrow();
  }

  FacemarkAAM* self = new FacemarkAAM();
  self->Wrap(info.Holder());
  self->facemark = cv::face::FacemarkAAM::create(params);

  return info.Holder();
};

#endif

#endif
