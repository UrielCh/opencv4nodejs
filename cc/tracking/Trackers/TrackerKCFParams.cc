#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerKCFParams.h"

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

Napi::FunctionReference TrackerKCFParams::constructor;

Napi::Object TrackerKCFParams(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, TrackerKCFParams::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "TrackerKCFParams"));


  Napi::SetAccessor(instanceTemplate, FF::newString(env, "sigma"), sigma_getter, sigma_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "lambda"), lambda_getter, lambda_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "interp_factor"), interp_factor_getter, interp_factor_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "output_sigma_factor"), output_sigma_factor_getter, output_sigma_factor_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "pca_learning_rate"), pca_learning_rate_getter, pca_learning_rate_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "resize"), resize_getter, resize_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "split_coeff"), split_coeff_getter, split_coeff_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "wrap_kernel"), wrap_kernel_getter, wrap_kernel_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "compress_feature"), compress_feature_getter, compress_feature_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "max_patch_size"), max_patch_size_getter, max_patch_size_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "compressed_size"), compressed_size_getter, compressed_size_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "desc_pca"), desc_pca_getter, desc_pca_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "desc_npca"), desc_npca_getter, desc_npca_setter);
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "detect_thresh"), detect_thresh_getter, detect_thresh_setter);
#endif
  (target).Set("TrackerKCFParams", FF::getFunction(ctor));
};

void TrackerKCFParams::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "TrackerKCFParams::New");
  FF_ASSERT_CONSTRUCT_CALL();
  TrackerKCFParams* self = new TrackerKCFParams();
  self->self = cv::TrackerKCF::Params();
  self->Wrap(info.Holder());
  return info.Holder();
};

#endif

#endif
