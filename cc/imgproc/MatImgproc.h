#include "Contour.h"
#include "Mat.h"
#include "Moments.h"
#include "TermCriteria.h"
#include <opencv2/imgproc.hpp>

#ifndef __FF_MATIMGPROC_H__
#define __FF_MATIMGPROC_H__

class MatImgproc {
public:
  static void Init(Napi::FunctionReference ctor);

  static void DrawContours(const Napi::CallbackInfo& info);
  static void DrawContoursAsync(const Napi::CallbackInfo& info);
  static void Rescale(const Napi::CallbackInfo& info);
  static void RescaleAsync(const Napi::CallbackInfo& info);
  static void Resize(const Napi::CallbackInfo& info);
  static void ResizeAsync(const Napi::CallbackInfo& info);
  static void ResizeToMax(const Napi::CallbackInfo& info);
  static void ResizeToMaxAsync(const Napi::CallbackInfo& info);
  static void Threshold(const Napi::CallbackInfo& info);
  static void ThresholdAsync(const Napi::CallbackInfo& info);
  static void AdaptiveThreshold(const Napi::CallbackInfo& info);
  static void AdaptiveThresholdAsync(const Napi::CallbackInfo& info);
  static void InRange(const Napi::CallbackInfo& info);
  static void InRangeAsync(const Napi::CallbackInfo& info);
  static void CvtColor(const Napi::CallbackInfo& info);
  static void CvtColorAsync(const Napi::CallbackInfo& info);
  static void BgrToGray(const Napi::CallbackInfo& info);
  static void BgrToGrayAsync(const Napi::CallbackInfo& info);
  static void WarpAffine(const Napi::CallbackInfo& info);
  static void WarpAffineAsync(const Napi::CallbackInfo& info);
  static void WarpPerspective(const Napi::CallbackInfo& info);
  static void WarpPerspectiveAsync(const Napi::CallbackInfo& info);
  static void Erode(const Napi::CallbackInfo& info);
  static void ErodeAsync(const Napi::CallbackInfo& info);
  static void Dilate(const Napi::CallbackInfo& info);
  static void DilateAsync(const Napi::CallbackInfo& info);
  static void MorphologyEx(const Napi::CallbackInfo& info);
  static void MorphologyExAsync(const Napi::CallbackInfo& info);
  static void DistanceTransform(const Napi::CallbackInfo& info);
  static void DistanceTransformAsync(const Napi::CallbackInfo& info);
  static void DistanceTransformWithLabels(const Napi::CallbackInfo& info);
  static void DistanceTransformWithLabelsAsync(const Napi::CallbackInfo& info);
  static void ConnectedComponents(const Napi::CallbackInfo& info);
  static void ConnectedComponentsAsync(const Napi::CallbackInfo& info);
  static void ConnectedComponentsWithStats(const Napi::CallbackInfo& info);
  static void ConnectedComponentsWithStatsAsync(const Napi::CallbackInfo& info);
  static void GrabCut(const Napi::CallbackInfo& info);
  static void GrabCutAsync(const Napi::CallbackInfo& info);
  static void Watershed(const Napi::CallbackInfo& info);
  static void WatershedAsync(const Napi::CallbackInfo& info);
  static Napi::Value _Moments(const Napi::CallbackInfo& info);
  static Napi::Value _MomentsAsync(const Napi::CallbackInfo& info);
  static void FindContours(const Napi::CallbackInfo& info);
  static void FindContoursAsync(const Napi::CallbackInfo& info);
  static void DrawLine(const Napi::CallbackInfo& info);
  static void DrawArrowedLine(const Napi::CallbackInfo& info);
  static void DrawRectangle(const Napi::CallbackInfo& info);
  static void DrawCircle(const Napi::CallbackInfo& info);
  static void DrawEllipse(const Napi::CallbackInfo& info);
  static void DrawPolylines(const Napi::CallbackInfo& info);
  static void DrawFillPoly(const Napi::CallbackInfo& info);
  static void DrawFillConvexPoly(const Napi::CallbackInfo& info);
  static void PutText(const Napi::CallbackInfo& info);
  static void PutTextAsync(const Napi::CallbackInfo& info);
  static void MatchTemplate(const Napi::CallbackInfo& info);
  static void MatchTemplateAsync(const Napi::CallbackInfo& info);
  static void Canny(const Napi::CallbackInfo& info);
  static void CannyAsync(const Napi::CallbackInfo& info);
  static void Sobel(const Napi::CallbackInfo& info);
  static void SobelAsync(const Napi::CallbackInfo& info);
  static void Scharr(const Napi::CallbackInfo& info);
  static void ScharrAsync(const Napi::CallbackInfo& info);
  static void Laplacian(const Napi::CallbackInfo& info);
  static void LaplacianAsync(const Napi::CallbackInfo& info);
  static void PyrDown(const Napi::CallbackInfo& info);
  static void PyrDownAsync(const Napi::CallbackInfo& info);
  static void PyrUp(const Napi::CallbackInfo& info);
  static void PyrUpAsync(const Napi::CallbackInfo& info);
  static void BuildPyramid(const Napi::CallbackInfo& info);
  static void BuildPyramidAsync(const Napi::CallbackInfo& info);
  static void HoughLines(const Napi::CallbackInfo& info);
  static void HoughLinesAsync(const Napi::CallbackInfo& info);
  static void HoughLinesP(const Napi::CallbackInfo& info);
  static void HoughLinesPAsync(const Napi::CallbackInfo& info);
  static void HoughCircles(const Napi::CallbackInfo& info);
  static void HoughCirclesAsync(const Napi::CallbackInfo& info);
  static void EqualizeHist(const Napi::CallbackInfo& info);
  static void EqualizeHistAsync(const Napi::CallbackInfo& info);
  static void CompareHist(const Napi::CallbackInfo& info);
  static void CompareHistAsync(const Napi::CallbackInfo& info);
  static void FloodFill(const Napi::CallbackInfo& info);
  static void FloodFillAsync(const Napi::CallbackInfo& info);
  static void BilateralFilter(const Napi::CallbackInfo& info);
  static void BilateralFilterAsync(const Napi::CallbackInfo& info);
  static void BoxFilter(const Napi::CallbackInfo& info);
  static void BoxFilterAsync(const Napi::CallbackInfo& info);
  static void SqrBoxFilter(const Napi::CallbackInfo& info);
  static void SqrBoxFilterAsync(const Napi::CallbackInfo& info);
  static void Filter2D(const Napi::CallbackInfo& info);
  static void Filter2DAsync(const Napi::CallbackInfo& info);
  static void SepFilter2D(const Napi::CallbackInfo& info);
  static void SepFilter2DAsync(const Napi::CallbackInfo& info);
  static void CornerHarris(const Napi::CallbackInfo& info);
  static void CornerHarrisAsync(const Napi::CallbackInfo& info);
  static void CornerSubPix(const Napi::CallbackInfo& info);
  static void CornerSubPixAsync(const Napi::CallbackInfo& info);
  static void CornerMinEigenVal(const Napi::CallbackInfo& info);
  static void CornerMinEigenValAsync(const Napi::CallbackInfo& info);
  static void CornerEigenValsAndVecs(const Napi::CallbackInfo& info);
  static void CornerEigenValsAndVecsAsync(const Napi::CallbackInfo& info);
  static void Integral(const Napi::CallbackInfo& info);
  static void IntegralAsync(const Napi::CallbackInfo& info);
#if CV_VERSION_LOWER_THAN(4, 0, 0)
  static void Undistort(const Napi::CallbackInfo& info);
  static void UndistortAsync(const Napi::CallbackInfo& info);
#endif
  static void GoodFeaturesToTrack(const Napi::CallbackInfo& info);
  static void GoodFeaturesToTrackAsync(const Napi::CallbackInfo& info);
  static void Blur(const Napi::CallbackInfo& info);
  static void BlurAsync(const Napi::CallbackInfo& info);
  static void GaussianBlur(const Napi::CallbackInfo& info);
  static void GaussianBlurAsync(const Napi::CallbackInfo& info);
  static void MedianBlur(const Napi::CallbackInfo& info);
  static void MedianBlurAsync(const Napi::CallbackInfo& info);
};

#endif