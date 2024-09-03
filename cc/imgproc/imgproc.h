#include "Contour.h"
#include "HistAxes.h"
#include "Mat.h"
#include "Moments.h"
#include "Point.h"
#include "Size.h"
#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#ifndef __FF_IMGPROC_H__
#define __FF_IMGPROC_H__

class Imgproc {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static void GetStructuringElement(const Napi::CallbackInfo& info);
  static void GetRotationMatrix2D(const Napi::CallbackInfo& info);
  static void GetAffineTransform(const Napi::CallbackInfo& info);
  static void GetPerspectiveTransform(const Napi::CallbackInfo& info);
  static void Plot1DHist(const Napi::CallbackInfo& info);
  static void FitLine(const Napi::CallbackInfo& info);
  static void GetTextSize(const Napi::CallbackInfo& info);
  static void GetTextSizeAsync(const Napi::CallbackInfo& info);
  static void ApplyColorMap(const Napi::CallbackInfo& info);
  static void ApplyColorMapAsync(const Napi::CallbackInfo& info);
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  static void Canny(const Napi::CallbackInfo& info);
  static void CannyAsync(const Napi::CallbackInfo& info);
#endif
#if CV_VERSION_LOWER_THAN(4, 0, 0)
  static void UndistortPoints(const Napi::CallbackInfo& info);
  static void UndistortPointsAsync(const Napi::CallbackInfo& info);
#endif
  static void GoodFeaturesToTrack(const Napi::CallbackInfo& info);
  static void GoodFeaturesToTrackAsync(const Napi::CallbackInfo& info);
  static void Blur(const Napi::CallbackInfo& info);
  static void BlurAsync(const Napi::CallbackInfo& info);
  static void GaussianBlur(const Napi::CallbackInfo& info);
  static void GaussianBlurAsync(const Napi::CallbackInfo& info);
  static void MedianBlur(const Napi::CallbackInfo& info);
  static void MedianBlurAsync(const Napi::CallbackInfo& info);
  static void Accumulate(const Napi::CallbackInfo& info);
  static void AccumulateAsync(const Napi::CallbackInfo& info);
  static void AccumulateProduct(const Napi::CallbackInfo& info);
  static void AccumulateProductAsync(const Napi::CallbackInfo& info);
  static void AccumulateSquare(const Napi::CallbackInfo& info);
  static void AccumulateSquareAsync(const Napi::CallbackInfo& info);
  static void AccumulateWeighted(const Napi::CallbackInfo& info);
  static void AccumulateWeightedAsync(const Napi::CallbackInfo& info);
  static void CalcHist(const Napi::CallbackInfo& info);
  static void CalcHistAsync(const Napi::CallbackInfo& info);
};

#endif
