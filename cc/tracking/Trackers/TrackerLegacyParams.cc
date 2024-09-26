#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerLegacyParams.h"

Nan::Persistent<v8::FunctionTemplate> TrackerBoostingParams::constructor;

NAN_MODULE_INIT(TrackerBoostingParams::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerBoostingParams::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("TrackerBoostingParams"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString("numClassifiers"), numClassifiers_getter, numClassifiers_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("samplerOverlap"), samplerOverlap_getter, samplerOverlap_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("samplerSearchFactor"), samplerSearchFactor_getter, samplerSearchFactor_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("iterationInit"), iterationInit_getter, iterationInit_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("featureSetNumFeatures"), featureSetNumFeatures_getter, featureSetNumFeatures_setter);

  Nan::Set(target, FF::newString("TrackerBoostingParams"), FF::getFunction(ctor));
};

NAN_METHOD(TrackerBoostingParams::New) {
  FF::TryCatch tryCatch("TrackerBoostingParams::New");
  FF_ASSERT_CONSTRUCT_CALL();
  TrackerBoostingParams* self = new TrackerBoostingParams();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->self = cv::legacy::TrackerBoosting::Params();
#else
  self->self = cv::TrackerBoosting::Params();
#endif
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};


#if CV_VERSION_GREATER_EQUAL(3, 4, 1)

Nan::Persistent<v8::FunctionTemplate> TrackerCSRTParams::constructor;

NAN_MODULE_INIT(TrackerCSRTParams::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerCSRTParams::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("TrackerCSRTParams"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString("admm_iterations"), admm_iterations_getter, admm_iterations_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("background_ratio"), background_ratio_getter, background_ratio_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("cheb_attenuation"), cheb_attenuation_getter, cheb_attenuation_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("filter_lr"), filter_lr_getter, filter_lr_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("gsl_sigma"), gsl_sigma_getter, gsl_sigma_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("histogram_bins"), histogram_bins_getter, histogram_bins_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("histogram_lr"), histogram_lr_getter, histogram_lr_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("hog_clip"), hog_clip_getter, hog_clip_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("hog_orientations"), hog_orientations_getter, hog_orientations_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("kaiser_alpha"), kaiser_alpha_getter, kaiser_alpha_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("num_hog_channels_used"), num_hog_channels_used_getter, num_hog_channels_used_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("number_of_scales"), number_of_scales_getter, number_of_scales_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("padding"), padding_getter, padding_setter);
#if CV_VERSION_GREATER_EQUAL(3, 4, 4)
  Nan::SetAccessor(instanceTemplate, FF::newString("psr_threshold"), psr_threshold_getter, psr_threshold_setter);
#endif // CV_VERSION_GREATER_EQUAL(3, 4, 4)
  Nan::SetAccessor(instanceTemplate, FF::newString("scale_lr"), scale_lr_getter, scale_lr_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("scale_model_max_area"), scale_model_max_area_getter, scale_model_max_area_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("scale_sigma_factor"), scale_sigma_factor_getter, scale_sigma_factor_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("scale_step"), scale_step_getter, scale_step_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("template_size"), template_size_getter, template_size_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("use_channel_weights"), use_channel_weights_getter, use_channel_weights_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("use_color_names"), use_color_names_getter, use_color_names_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("use_gray"), use_gray_getter, use_gray_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("use_hog"), use_hog_getter, use_hog_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("use_rgb"), use_rgb_getter, use_rgb_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("use_segmentation"), use_segmentation_getter, use_segmentation_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("weights_lr"), weights_lr_getter, weights_lr_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("window_function"), window_function_getter, window_function_setter);

  Nan::Set(target, FF::newString("TrackerCSRTParams"), FF::getFunction(ctor));
};

NAN_METHOD(TrackerCSRTParams::New) {
  FF::TryCatch tryCatch("TrackerCSRTParams::New");
  FF_ASSERT_CONSTRUCT_CALL();
  TrackerCSRTParams* self = new TrackerCSRTParams();
  self->self = cv::TrackerCSRT::Params();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif // CV_VERSION_GREATER_EQUAL(3, 4, 1)


#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

Nan::Persistent<v8::FunctionTemplate> TrackerKCFParams::constructor;

NAN_MODULE_INIT(TrackerKCFParams::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerKCFParams::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("TrackerKCFParams"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString("sigma"), sigma_getter, sigma_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("lambda"), lambda_getter, lambda_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("interp_factor"), interp_factor_getter, interp_factor_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("output_sigma_factor"), output_sigma_factor_getter, output_sigma_factor_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("pca_learning_rate"), pca_learning_rate_getter, pca_learning_rate_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("resize"), resize_getter, resize_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("split_coeff"), split_coeff_getter, split_coeff_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("wrap_kernel"), wrap_kernel_getter, wrap_kernel_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("compress_feature"), compress_feature_getter, compress_feature_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("max_patch_size"), max_patch_size_getter, max_patch_size_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("compressed_size"), compressed_size_getter, compressed_size_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("desc_pca"), desc_pca_getter, desc_pca_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("desc_npca"), desc_npca_getter, desc_npca_setter);
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
  Nan::SetAccessor(instanceTemplate, FF::newString("detect_thresh"), detect_thresh_getter, detect_thresh_setter);
#endif
  Nan::Set(target, FF::newString("TrackerKCFParams"), FF::getFunction(ctor));
};

NAN_METHOD(TrackerKCFParams::New) {
  FF::TryCatch tryCatch("TrackerKCFParams::New");
  FF_ASSERT_CONSTRUCT_CALL();
  TrackerKCFParams* self = new TrackerKCFParams();
  self->self = cv::TrackerKCF::Params();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif // CV_VERSION_GREATER_EQUAL(3, 1, 0)


Nan::Persistent<v8::FunctionTemplate> TrackerMILParams::constructor;

NAN_MODULE_INIT(TrackerMILParams::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerMILParams::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString("TrackerMILParams"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString("samplerInitInRadius"), samplerInitInRadius_getter, samplerInitInRadius_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("samplerSearchWinSize"), samplerSearchWinSize_getter, samplerSearchWinSize_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("samplerTrackInRadius"), samplerTrackInRadius_getter, samplerTrackInRadius_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("samplerInitMaxNegNum"), samplerInitMaxNegNum_getter, samplerInitMaxNegNum_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("samplerTrackMaxPosNum"), samplerTrackMaxPosNum_getter, samplerTrackMaxPosNum_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("samplerTrackMaxNegNum"), samplerTrackMaxNegNum_getter, samplerTrackMaxNegNum_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString("featureSetNumFeatures"), featureSetNumFeatures_getter, featureSetNumFeatures_setter);

  Nan::Set(target, FF::newString("TrackerMILParams"), FF::getFunction(ctor));
};

NAN_METHOD(TrackerMILParams::New) {
  FF::TryCatch tryCatch("TrackerMILParams::New");
  FF_ASSERT_CONSTRUCT_CALL();
  TrackerMILParams* self = new TrackerMILParams();
  self->self = cv::TrackerMIL::Params();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};


#endif // HAVE_OPENCV_TRACKING
