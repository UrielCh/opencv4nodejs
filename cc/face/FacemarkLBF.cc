#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "FacemarkLBF.h"
#include "FacemarkLBFParams.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

Napi::FunctionReference FacemarkLBF::constructor;

Napi::Object FacemarkLBF(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor =
      Nan::New<v8::FunctionTemplate>(FacemarkLBF::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  Facemark::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(Nan::New("FacemarkLBF").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

  target.Set("FacemarkLBF", FF::getFunction(ctor));
};

void FacemarkLBF::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "FacemarkLBF::New");
  FF_ASSERT_CONSTRUCT_CALL();

  cv::face::FacemarkLBF::Params params;
  if (FacemarkLBFParams::Converter::optArg(0, &params, info)) {
    return tryCatch.reThrow();
  }

  FacemarkLBF* self = new FacemarkLBF();
  self->Wrap(info.Holder());
  self->facemark = cv::face::FacemarkLBF::create(params);

  info.GetReturnValue().Set(info.Holder());
};

#endif

#endif
