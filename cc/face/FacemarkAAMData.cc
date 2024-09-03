#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "FacemarkAAMData.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

Napi::FunctionReference FacemarkAAMData::constructor;

Napi::Object FacemarkAAMData(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor =
      Napi::Function::New(env, FacemarkAAMData::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "FacemarkAAMData"));


  Napi::SetAccessor(instanceTemplate, FF::newString(env, "s0"), s0_getter, s0_setter);

  (target).Set("FacemarkAAMData", FF::getFunction(ctor));
};

void FacemarkAAMData::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "FacemarkAAMData::New");
  FF_ASSERT_CONSTRUCT_CALL();
  FacemarkAAMData* self = new FacemarkAAMData();
  self->self = cv::face::FacemarkAAM::Data();
  self->Wrap(info.Holder());
  return info.Holder();
};

#endif

#endif
