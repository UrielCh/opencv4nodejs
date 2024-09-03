#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerCSRTParams.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 1)

Napi::FunctionReference TrackerCSRTParams::constructor;

Napi::Object TrackerCSRTParams(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(TrackerCSRTParams::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "TrackerCSRTParams"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString(env, "admm_iterations"), admm_iterations_getter, admm_iterations_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "background_ratio"), background_ratio_getter, background_ratio_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "cheb_attenuation"), cheb_attenuation_getter, cheb_attenuation_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "filter_lr"), filter_lr_getter, filter_lr_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "gsl_sigma"), gsl_sigma_getter, gsl_sigma_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "histogram_bins"), histogram_bins_getter, histogram_bins_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "histogram_lr"), histogram_lr_getter, histogram_lr_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "hog_clip"), hog_clip_getter, hog_clip_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "hog_orientations"), hog_orientations_getter, hog_orientations_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "kaiser_alpha"), kaiser_alpha_getter, kaiser_alpha_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "num_hog_channels_used"), num_hog_channels_used_getter, num_hog_channels_used_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "number_of_scales"), number_of_scales_getter, number_of_scales_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "padding"), padding_getter, padding_setter);
#if CV_VERSION_GREATER_EQUAL(3, 4, 4)
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "psr_threshold"), psr_threshold_getter, psr_threshold_setter);
#endif
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "scale_lr"), scale_lr_getter, scale_lr_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "scale_model_max_area"), scale_model_max_area_getter, scale_model_max_area_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "scale_sigma_factor"), scale_sigma_factor_getter, scale_sigma_factor_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "scale_step"), scale_step_getter, scale_step_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "template_size"), template_size_getter, template_size_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "use_channel_weights"), use_channel_weights_getter, use_channel_weights_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "use_color_names"), use_color_names_getter, use_color_names_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "use_gray"), use_gray_getter, use_gray_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "use_hog"), use_hog_getter, use_hog_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "use_rgb"), use_rgb_getter, use_rgb_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "use_segmentation"), use_segmentation_getter, use_segmentation_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "weights_lr"), weights_lr_getter, weights_lr_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "window_function"), window_function_getter, window_function_setter);

  Nan::Set(target, FF::newString(env, "TrackerCSRTParams"), FF::getFunction(ctor));
};

void TrackerCSRTParams::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "TrackerCSRTParams::New");
  FF_ASSERT_CONSTRUCT_CALL();
  TrackerCSRTParams* self = new TrackerCSRTParams();
  self->self = cv::TrackerCSRT::Params();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif

#endif
