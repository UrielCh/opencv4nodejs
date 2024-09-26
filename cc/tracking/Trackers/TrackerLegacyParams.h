#include "macros.h"
#include <opencv2/tracking.hpp>
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
#include <opencv2/tracking/tracking_legacy.hpp>
#endif

#ifndef __FF_TRACKERLEGACYPARAMS_H__
#define __FF_TRACKERLEGACYPARAMS_H__

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
class TrackerBoostingParams : public FF::ObjectWrap<TrackerBoostingParams, cv::legacy::TrackerBoosting::Params>
#else
class TrackerBoostingParams : public FF::ObjectWrap<TrackerBoostingParams, cv::TrackerBoosting::Params>
#endif
{
  public:
  static Nan::Persistent<v8::FunctionTemplate> constructor;

  static const char* getClassName() {
    return "TrackerBoostingParams";
  }

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  FF_ACCESSORS(numClassifiers, FF::IntConverter);
  FF_ACCESSORS(samplerOverlap, FF::FloatConverter);
  FF_ACCESSORS(samplerSearchFactor, FF::FloatConverter);
  FF_ACCESSORS(iterationInit, FF::IntConverter);
  FF_ACCESSORS(featureSetNumFeatures, FF::IntConverter);
};


#if CV_VERSION_GREATER_EQUAL(3, 4, 1)

class TrackerCSRTParams : public FF::ObjectWrap<TrackerCSRTParams, cv::TrackerCSRT::Params> {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor;

  static const char* getClassName() {
    return "TrackerBoostingParams";
  }

  FF_ACCESSORS(admm_iterations, FF::IntConverter);
  FF_ACCESSORS(background_ratio, FF::IntConverter);
  FF_ACCESSORS(histogram_bins, FF::IntConverter);
  FF_ACCESSORS(histogram_lr, FF::FloatConverter);
  FF_ACCESSORS(number_of_scales, FF::IntConverter);
  FF_ACCESSORS(scale_sigma_factor, FF::FloatConverter);
  FF_ACCESSORS(scale_model_max_area, FF::FloatConverter);
  FF_ACCESSORS(scale_lr, FF::FloatConverter);
  FF_ACCESSORS(cheb_attenuation, FF::FloatConverter);
  FF_ACCESSORS(kaiser_alpha, FF::FloatConverter);
  FF_ACCESSORS(filter_lr, FF::FloatConverter);
  FF_ACCESSORS(gsl_sigma, FF::FloatConverter);
  FF_ACCESSORS(hog_clip, FF::FloatConverter);
  FF_ACCESSORS(hog_orientations, FF::FloatConverter);
  FF_ACCESSORS(padding, FF::FloatConverter);
  FF_ACCESSORS(num_hog_channels_used, FF::IntConverter);
  FF_ACCESSORS(scale_step, FF::FloatConverter);
  FF_ACCESSORS(template_size, FF::FloatConverter);
  FF_ACCESSORS(use_channel_weights, FF::BoolConverter);
  FF_ACCESSORS(use_color_names, FF::BoolConverter);
  FF_ACCESSORS(use_gray, FF::BoolConverter);
  FF_ACCESSORS(use_hog, FF::BoolConverter);
  FF_ACCESSORS(use_rgb, FF::BoolConverter);
  FF_ACCESSORS(use_segmentation, FF::BoolConverter);
  FF_ACCESSORS(weights_lr, FF::FloatConverter);
  FF_ACCESSORS(window_function, FF::StringConverter);

#if CV_VERSION_GREATER_EQUAL(3, 4, 4)
  FF_ACCESSORS(psr_threshold, FF::FloatConverter);
#endif // CV_VERSION_GREATER_EQUAL(3, 4, 4)

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
};

#endif // CV_VERSION_GREATER_EQUAL(3, 4, 1)


#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

class TrackerKCFParams : public FF::ObjectWrap<TrackerKCFParams, cv::TrackerKCF::Params> {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor;

  static const char* getClassName() {
    return "TrackerKCFParams";
  }

  FF_ACCESSORS(sigma, FF::FloatConverter);
  FF_ACCESSORS(lambda, FF::FloatConverter);
  FF_ACCESSORS(interp_factor, FF::FloatConverter);
  FF_ACCESSORS(output_sigma_factor, FF::FloatConverter);
  FF_ACCESSORS(pca_learning_rate, FF::FloatConverter);
  FF_ACCESSORS(resize, FF::BoolConverter);
  FF_ACCESSORS(split_coeff, FF::BoolConverter);
  FF_ACCESSORS(wrap_kernel, FF::BoolConverter);
  FF_ACCESSORS(compress_feature, FF::BoolConverter);
  FF_ACCESSORS(max_patch_size, FF::IntConverter);
  FF_ACCESSORS(compressed_size, FF::IntConverter);
  FF_ACCESSORS(desc_pca, FF::UintConverter);
  FF_ACCESSORS(desc_npca, FF::UintConverter);

#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
  FF_ACCESSORS(detect_thresh, FF::FloatConverter);
#endif

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
};

#endif // CV_VERSION_GREATER_EQUAL(3, 1, 0)


class TrackerMILParams : public FF::ObjectWrap<TrackerMILParams, cv::TrackerMIL::Params> {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor;

  static const char* getClassName() {
    return "TrackerMILParams";
  }

  FF_ACCESSORS(samplerInitInRadius, FF::FloatConverter);
  FF_ACCESSORS(samplerSearchWinSize, FF::FloatConverter);
  FF_ACCESSORS(samplerTrackInRadius, FF::FloatConverter);
  FF_ACCESSORS(samplerInitMaxNegNum, FF::IntConverter);
  FF_ACCESSORS(samplerTrackMaxPosNum, FF::IntConverter);
  FF_ACCESSORS(samplerTrackMaxNegNum, FF::IntConverter);
  FF_ACCESSORS(featureSetNumFeatures, FF::IntConverter);

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
};


#endif // __FF_TRACKERLEGACYPARAMS_H__
