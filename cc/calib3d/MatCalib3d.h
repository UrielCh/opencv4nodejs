#include "Mat.h"
#include <opencv2/calib3d.hpp>

#ifndef __FF_MATCALIB3D_H__
#define __FF_MATCALIB3D_H__

class MatCalib3d : public Napi::ObjectWrap<MatCalib3d> {
public:
  static void Init(Napi::FunctionReference ctor);

  static void Rodrigues(const Napi::CallbackInfo& info);
  static void RodriguesAsync(const Napi::CallbackInfo& info);
  static void RQDecomp3x3(const Napi::CallbackInfo& info);
  static void RQDecomp3x3Async(const Napi::CallbackInfo& info);
  static void DecomposeProjectionMatrix(const Napi::CallbackInfo& info);
  static void DecomposeProjectionMatrixAsync(const Napi::CallbackInfo& info);
  static void MatMulDeriv(const Napi::CallbackInfo& info);
  static void MatMulDerivAsync(const Napi::CallbackInfo& info);
  static void FindChessboardCorners(const Napi::CallbackInfo& info);
  static void FindChessboardCornersAsync(const Napi::CallbackInfo& info);
  static void DrawChessboardCorners(const Napi::CallbackInfo& info);
  static void DrawChessboardCornersAsync(const Napi::CallbackInfo& info);
  static void Find4QuadCornerSubpix(const Napi::CallbackInfo& info);
  static void Find4QuadCornerSubpixAsync(const Napi::CallbackInfo& info);
  static void CalibrationMatrixValues(const Napi::CallbackInfo& info);
  static void CalibrationMatrixValuesAsync(const Napi::CallbackInfo& info);
  static void StereoRectify(const Napi::CallbackInfo& info);
  static void StereoRectifyAsync(const Napi::CallbackInfo& info);
  static void Rectify3Collinear(const Napi::CallbackInfo& info);
  static void Rectify3CollinearAsync(const Napi::CallbackInfo& info);
  static void GetOptimalNewCameraMatrix(const Napi::CallbackInfo& info);
  static void GetOptimalNewCameraMatrixAsync(const Napi::CallbackInfo& info);
  static void DecomposeEssentialMat(const Napi::CallbackInfo& info);
  static void DecomposeEssentialMatAsync(const Napi::CallbackInfo& info);
  static void TriangulatePoints(const Napi::CallbackInfo& info);
  static void TriangulatePointsAsync(const Napi::CallbackInfo& info);
  static void CorrectMatches(const Napi::CallbackInfo& info);
  static void CorrectMatchesAsync(const Napi::CallbackInfo& info);
  static void FilterSpeckles(const Napi::CallbackInfo& info);
  static void FilterSpecklesAsync(const Napi::CallbackInfo& info);
  static void ValidateDisparity(const Napi::CallbackInfo& info);
  static void ValidateDisparityAsync(const Napi::CallbackInfo& info);
  static void ReprojectImageTo3D(const Napi::CallbackInfo& info);
  static void ReprojectImageTo3DAsync(const Napi::CallbackInfo& info);
  static void DecomposeHomographyMat(const Napi::CallbackInfo& info);
  static void DecomposeHomographyMatAsync(const Napi::CallbackInfo& info);
#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
  static void FindEssentialMat(const Napi::CallbackInfo& info);
  static void FindEssentialMatAsync(const Napi::CallbackInfo& info);
  static void RecoverPose(const Napi::CallbackInfo& info);
  static void RecoverPoseAsync(const Napi::CallbackInfo& info);
#endif
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  static void Undistort(const Napi::CallbackInfo& info);
  static void UndistortAsync(const Napi::CallbackInfo& info);
#endif
};

#endif