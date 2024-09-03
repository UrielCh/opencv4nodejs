#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "FacemarkAAMData.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

Nan::Persistent<v8::FunctionTemplate> FacemarkAAMData::constructor;

Napi::Object FacemarkAAMData(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor =
      Nan::New<v8::FunctionTemplate>(FacemarkAAMData::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "FacemarkAAMData"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString(env, "s0"), s0_getter, s0_setter);

  Nan::Set(target, FF::newString(env, "FacemarkAAMData"), FF::getFunction(ctor));
};

void FacemarkAAMData::New(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("FacemarkAAMData::New");
  FF_ASSERT_CONSTRUCT_CALL();
  FacemarkAAMData* self = new FacemarkAAMData();
  self->self = cv::face::FacemarkAAM::Data();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif

#endif
