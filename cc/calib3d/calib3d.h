#include "calib3dBindings.h"

#ifndef __FF_CALIB3D_H__
#define __FF_CALIB3D_H__

class Calib3d {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static void FindHomography(const Napi::CallbackInfo& info);
  static void FindHomographyAsync(const Napi::CallbackInfo& info);
  static void ComposeRT(const Napi::CallbackInfo& info);
  static void ComposeRTAsync(const Napi::CallbackInfo& info);
  static void SolvePnP(const Napi::CallbackInfo& info);
  static void SolvePnPAsync(const Napi::CallbackInfo& info);
  static void SolvePnPRansac(const Napi::CallbackInfo& info);
  static void SolvePnPRansacAsync(const Napi::CallbackInfo& info);
  static void ProjectPoints(const Napi::CallbackInfo& info);
  static void ProjectPointsAsync(const Napi::CallbackInfo& info);
  static void InitCameraMatrix2D(const Napi::CallbackInfo& info);
  static void InitCameraMatrix2DAsync(const Napi::CallbackInfo& info);
  static void StereoCalibrate(const Napi::CallbackInfo& info);
  static void StereoCalibrateAsync(const Napi::CallbackInfo& info);
  static void StereoRectifyUncalibrated(const Napi::CallbackInfo& info);
  static void StereoRectifyUncalibratedAsync(const Napi::CallbackInfo& info);
  static void FindFundamentalMat(const Napi::CallbackInfo& info);
  static void FindFundamentalMatAsync(const Napi::CallbackInfo& info);
  static void FindEssentialMat(const Napi::CallbackInfo& info);
  static void FindEssentialMatAsync(const Napi::CallbackInfo& info);
  static void RecoverPose(const Napi::CallbackInfo& info);
  static void RecoverPoseAsync(const Napi::CallbackInfo& info);
  static void ComputeCorrespondEpilines(const Napi::CallbackInfo& info);
  static void ComputeCorrespondEpilinesAsync(const Napi::CallbackInfo& info);
  static void GetValidDisparityROI(const Napi::CallbackInfo& info);
  static void GetValidDisparityROIAsync(const Napi::CallbackInfo& info);
  static void EstimateAffine3D(const Napi::CallbackInfo& info);
  static void EstimateAffine3DAsync(const Napi::CallbackInfo& info);
#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
  static void SampsonDistance(const Napi::CallbackInfo& info);
  static void SampsonDistanceAsync(const Napi::CallbackInfo& info);
  static void CalibrateCamera(const Napi::CallbackInfo& info);
  static void CalibrateCameraAsync(const Napi::CallbackInfo& info);
#endif
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  static void CalibrateCameraExtended(const Napi::CallbackInfo& info);
  static void CalibrateCameraExtendedAsync(const Napi::CallbackInfo& info);
  static void EstimateAffine2D(const Napi::CallbackInfo& info);
  static void EstimateAffine2DAsync(const Napi::CallbackInfo& info);
  static void EstimateAffinePartial2D(const Napi::CallbackInfo& info);
  static void EstimateAffinePartial2DAsync(const Napi::CallbackInfo& info);
#endif
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
  static void SolveP3P(const Napi::CallbackInfo& info);
  static void SolveP3PAsync(const Napi::CallbackInfo& info);
#endif
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  static void UndistortPoints(const Napi::CallbackInfo& info);
  static void UndistortPointsAsync(const Napi::CallbackInfo& info);
#endif
};

#endif